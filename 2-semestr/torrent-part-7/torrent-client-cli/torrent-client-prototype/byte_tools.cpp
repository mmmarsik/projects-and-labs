#include "byte_tools.h"
#include <openssl/sha.h>
#include <stdexcept>
#include <vector>
#include <iomanip>

int BytesToInt(std::string_view bytes)
{
    int integer = 0;
    integer |= (static_cast<int>(static_cast<unsigned char>(bytes[0])) << 24) | (static_cast<int>(static_cast<unsigned char>(bytes[1])) << 16) | (static_cast<int>(static_cast<unsigned char>(bytes[2])) << 8) | (static_cast<int>(static_cast<unsigned char>(bytes[3])));

    return integer;
}

std::string CalculateSHA1(const std::string &msg)
{
    std::string hash;
    hash.resize(SHA_DIGEST_LENGTH);
    SHA1(reinterpret_cast<const unsigned char *>(msg.c_str()), msg.size(), reinterpret_cast<unsigned char *>(hash.data()));
    return hash;
}

/*
 * Представить массив байтов в виде строки, содержащей только символы, соответствующие цифрам в шестнадцатеричном исчислении.
 * Конкретный формат выходной строки не важен. Важно то, чтобы выходная строка не содержала символов, которые нельзя
 * было бы представить в кодировке utf-8. Данная функция будет использована для вывода SHA1 хеш-суммы в лог.
 */

std::string HexEncode(const std::string &input)
{
    std::ostringstream stream;
    for (unsigned char c : input)
    {
        stream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    }
    return stream.str();
}