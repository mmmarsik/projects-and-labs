#pragma once

#include <string>
#include <vector>

struct TorrentFile {
    std::string announce;
    std::string comment;
    std::vector<std::string> pieceHashes;
    size_t pieceLength;
    size_t length;
    std::string name;
    std::string infoHash;
};

std::string createSHA1(const std::string &s);

TorrentFile LoadTorrentFile(const std::string& filename);

