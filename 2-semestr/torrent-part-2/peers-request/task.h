#pragma once

#include "peer.h"
#include "torrent_file.h"
#include <string>
#include <vector>
#include <openssl/sha.h>
#include <fstream>
#include <variant>
#include <list>
#include <map>
#include <sstream>
#include <cpr/cpr.h>
#include <iostream>

using BencodeInt = long long;
using BencodeString = std::string;

class BencodeValue;

using BencodeList = std::list<BencodeValue>;
using BencodeDict = std::map<BencodeString, BencodeValue>;
class BencodeValue : public std::variant<BencodeInt, BencodeString, BencodeList, BencodeDict>
{
public:
    BencodeValue() = default;
    BencodeValue(const BencodeValue &) = default;
    BencodeValue &operator=(const BencodeValue &) = default;

    BencodeValue(BencodeInt bi) : std::variant<BencodeInt, BencodeString, BencodeList, BencodeDict>(bi) {}
    BencodeValue(BencodeString bs) : std::variant<BencodeInt, BencodeString, BencodeList, BencodeDict>(bs) {}
    BencodeValue(BencodeList bl) : std::variant<BencodeInt, BencodeString, BencodeList, BencodeDict>(bl) {}
    BencodeValue(BencodeDict bd) : std::variant<BencodeInt, BencodeString, BencodeList, BencodeDict>(bd) {}

private:
};

BencodeValue ParseBencode(std::istream &is);

BencodeInt ParseInteger(std::istream &is)
{
    is.ignore(1);
    BencodeInt ans;
    is >> ans;
    is.ignore(1);
    return ans;
}

BencodeString ParseString(std::istream &is)
{
    size_t len;
    is >> len;
    is.ignore(1);
    BencodeString ans;
    for (size_t i = 0; i < len; ++i)
    {
        char c;
        is.get(c);
        ans.push_back(c);
    }
    return ans;
}
BencodeList ParseList(std::istream &is)
{
    is.ignore(1);
    BencodeList ans;
    while (is.peek() != 'e')
    {
        ans.push_back(ParseBencode(is));
    }
    is.ignore(1);
    return ans;
}

BencodeDict ParseDictionary(std::istream &is)
{
    is.ignore(1);
    BencodeDict ans;
    while (is.peek() != 'e')
    {
        BencodeString key = ParseString(is);
        BencodeValue value = ParseBencode(is);
        ans[key] = value;
    }
    is.ignore(1);
    return ans;
}

BencodeValue ParseBencode(std::istream &is)
{
    char c = is.peek();

    switch (c)
    {
    case 'i':
        return ParseInteger(is);
    case 'l':
        return ParseList(is);
    case 'd':
        return ParseDictionary(is);
    default:
        if (std::isdigit(c))
        {
            return ParseString(is);
        }
    }
}

class TorrentTracker
{
public:
    /*
     * url - адрес трекера, берется из поля announce в .torrent-файле
     */
    TorrentTracker(const std::string &url) : url_(url) {}

    /*
     * Получить список пиров у трекера и сохранить его для дальнейшей работы.
     * Запрос пиров происходит посредством HTTP GET запроса, данные передаются в формате bencode.
     * Такой же формат использовался в .torrent файле.
     * Подсказка: посмотрите, что было написано в main.cpp в домашнем задании torrent-file
     *
     * tf: структура с разобранными данными из .torrent файла из предыдущего домашнего задания.
     * peerId: id, под которым представляется наш клиент.
     * port: порт, на котором наш клиент будет слушать входящие соединения (пока что мы не слушаем и на этот порт никто
     *  не сможет подключиться).
     */
    void UpdatePeers(const TorrentFile &tf, std::string peerId, int port)
    {
        cpr::Response res = cpr::Get(
            cpr::Url{tf.announce},
            cpr::Parameters{
                {"info_hash", tf.infoHash},
                {"peer_id", peerId},
                {"port", std::to_string(port)},
                {"uploaded", std::to_string(0)},
                {"downloaded", std::to_string(0)},
                {"left", std::to_string(tf.length)},
                {"compact", std::to_string(1)}},
            cpr::Timeout{20000});

        std::istringstream text(res.text, std::ios::binary);
        BencodeValue ParsedText = ParseBencode(text);

        BencodeDict dict = std::get<BencodeDict>(ParsedText);

        BencodeString peers = std::get<BencodeString>(dict.at("peers"));
        for (size_t i = 0; i < peers.size(); i += 6)
        {
            Peer peer;

            peer.ip += std::to_string((unsigned char)(peers[i]));

            for (int j = 1; j < 4; ++j)
            {
                peer.ip += ".";
                peer.ip += std::to_string((unsigned char)(peers[i + j]));
            }

            uint16_t a1 = (unsigned char)(peers[i + 4]);
            uint16_t a2 = (unsigned char)(peers[i + 5]);

            peer.port = (a1 << 8) | a2;

            peers_.push_back(peer);

        }
    }

    /*
     * Отдает полученный ранее список пиров
     */
    const std::vector<Peer> &GetPeers() const
    {
        return peers_;
    }

private:
    std::string url_;
    std::vector<Peer> peers_;
};

std::string createSHA1(const std::string &s)
{
    std::string hash;
    hash.resize(SHA_DIGEST_LENGTH);
    SHA1(reinterpret_cast<const unsigned char *>(s.c_str()), s.size(), reinterpret_cast<unsigned char *>(hash.data()));
    return hash;
}

std::string prepareBencodeData(const BencodeValue &value)
{
    if (std::holds_alternative<BencodeString>(value))
    {
        const auto &str = std::get<BencodeString>(value);
        return std::to_string(str.length()) + ":" + str;
    }
    else if (std::holds_alternative<BencodeInt>(value))
    {
        const auto &num = std::get<BencodeInt>(value);
        return "i" + std::to_string(num) + "e";
    }
    else if (std::holds_alternative<BencodeList>(value))
    {
        const auto &list = std::get<BencodeList>(value);
        std::string bencChar = "l";
        for (const auto &item : list)
        {
            bencChar += prepareBencodeData(item);
        }
        bencChar += "e";
        return bencChar;
    }
    else if (std::holds_alternative<BencodeDict>(value))
    {
        const auto &dict = std::get<BencodeDict>(value);
        std::string bencChar = "d";
        for (const auto &[key, val] : dict)
        {
            bencChar += prepareBencodeData(BencodeString{key}) + prepareBencodeData(val);
        }
        bencChar += "e";
        return bencChar;
    }
    return "";
}

TorrentFile LoadTorrentFile(const std::string &filename)
{
    std::ifstream file(filename, std::ios::in);
    if (!file)
    {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    BencodeValue torrentData = ParseBencode(file);

    if (!std::holds_alternative<BencodeDict>(torrentData))
    {
        throw std::runtime_error("Can't find Dict");
    }

    const BencodeDict &torrentDict = std::get<BencodeDict>(torrentData);

    TorrentFile torFile;

    if (torrentDict.find("announce") != torrentDict.end())
    {
        torFile.announce = std::get<BencodeString>(torrentDict.at("announce"));
    }
    else
    {
        throw std::runtime_error("Can't find announce");
    }

    if (torrentDict.find("comment") != torrentDict.end())
    {
        torFile.comment = std::get<BencodeString>(torrentDict.at("comment"));
    }

    if (torrentDict.find("info") != torrentDict.end())
    {
        const BencodeDict &infoDict = std::get<BencodeDict>(torrentDict.at("info"));
        if (infoDict.find("length") != infoDict.end())
        {
            torFile.length = std::get<BencodeInt>(infoDict.at("length"));
        }
        else
        {
            throw std::runtime_error("Can't find length");
        }

        if (infoDict.find("name") != infoDict.end())
        {
            torFile.name = std::get<BencodeString>(infoDict.at("name"));
        }
        else
        {
            throw std::runtime_error("Can't find name");
        }

        if (infoDict.find("piece length") != infoDict.end())
        {
            torFile.pieceLength = std::get<BencodeInt>(infoDict.at("piece length"));
        }
        else

        {
            throw std::runtime_error("Can't find piece length");
        }

        if (infoDict.find("pieces") != infoDict.end())
        {
            const BencodeString &piecesString = std::get<BencodeString>(infoDict.at("pieces"));

            size_t piecesStringsCnt = piecesString.size() / 20;
            size_t cnt = 0;
            std::string tmpString;
            while (cnt != piecesStringsCnt)
            {
                tmpString.clear();
                for (size_t i = 0; i < 20; ++i)
                {
                    tmpString.push_back(piecesString[cnt * 20 + i]);
                }
                torFile.pieceHashes.push_back(tmpString);
                ++cnt;
            }
        }
        else
        {
            throw std::runtime_error("Can't find pieces");
        }

        std::string serializedInfo = prepareBencodeData(infoDict);
        torFile.infoHash = createSHA1(serializedInfo);
    }
    else
    {
        throw std::runtime_error("Can't find info");
    }

    return torFile;
}
