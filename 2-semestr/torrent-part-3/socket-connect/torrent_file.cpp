#include "torrent_file.h"
#include "bencode.h"
#include <vector>
#include <openssl/sha.h>
#include <fstream>
#include <variant>
#include <sstream>

std::string createSHA1(const std::string &s)
{
    std::string hash;
    hash.resize(SHA_DIGEST_LENGTH);
    SHA1(reinterpret_cast<const unsigned char *>(s.c_str()), s.size(), reinterpret_cast<unsigned char *>(hash.data()));
    return hash;
}

using namespace Bencode;

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



