#include "bencode.h"

namespace Bencode
{
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

}
