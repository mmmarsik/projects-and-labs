#include "byte_tools.h"
#include <openssl/sha.h>
#include <stdexcept>
#include <vector>

#include "byte_tools.h"

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