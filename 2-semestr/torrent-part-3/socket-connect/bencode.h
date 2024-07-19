#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <variant>
#include <list>
#include <map>
#include <sstream>
#include <openssl/sha.h>
#include <cassert>
#include <iostream>

namespace Bencode
{

    /*
     * В это пространство имен рекомендуется вынести функции для работы с данными в формате bencode.
     * Этот формат используется в .torrent файлах и в протоколе общения с трекером
     */
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

    BencodeInt ParseInteger(std::istream &is);

    BencodeString ParseString(std::istream &is);

    BencodeList ParseList(std::istream &is);

    BencodeDict ParseDictionary(std::istream &is);

    std::string prepareBencodeData(const BencodeValue &value);

}
