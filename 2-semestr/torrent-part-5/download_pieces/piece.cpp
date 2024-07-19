#include "byte_tools.h"
#include "piece.h"
#include <iostream>
#include <algorithm>

namespace
{
    constexpr size_t BLOCK_SIZE = 1 << 14;
}

Piece::Piece(size_t index, size_t length, std::string hash)
    : index_(index), length_(length), hash_(std::move(hash))
{
    size_t numBlocks = (length + BLOCK_SIZE - 1) / BLOCK_SIZE;
    blocks_.reserve(numBlocks);

    for (size_t i = 0; i < numBlocks; ++i)
    {
        size_t blockOffset = i * BLOCK_SIZE;
        size_t blockLength = std::min(BLOCK_SIZE, length - blockOffset);

        Block block{(index), (blockOffset), (blockLength), Block::Status::Missing, ""};
        blocks_.emplace_back(std::move(block));
    }
}

bool Piece::HashMatches() const
{
    return GetDataHash() == hash_;
}

Block *Piece::FirstMissingBlock()
{
    for (auto &block : blocks_)
    {
        if (block.status == Block::Missing)
        {
            return &block;
        }
    }
    return nullptr;
}

size_t Piece::GetIndex() const
{
    return index_;
}

void Piece::SaveBlock(size_t blockOffset, std::string data)
{
    size_t pos = blockOffset / BLOCK_SIZE;
    blocks_[pos].data = std::move(data);
    blocks_[pos].status = Block::Status::Retrieved;
}

bool Piece::AllBlocksRetrieved() const
{
    for (const auto &block : blocks_)
    {
        if (block.status != Block::Retrieved)
        {
            return false;
        }
    }
    return true;
}

std::string Piece::GetData() const
{
    std::string data;
    for (const auto &block : blocks_)
    {
        data += block.data;
    }
    return data;
}

std::string Piece::GetDataHash() const
{
    return CalculateSHA1(GetData());
}

const std::string &Piece::GetHash() const
{
    return hash_;
}

void Piece::Reset()
{
    for (auto &block : blocks_)
    {
        block.status = Block::Missing;
        block.data.clear();
    }
}

const size_t Piece::GetSize() const
{
    return length_;
}