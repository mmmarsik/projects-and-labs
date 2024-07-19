#include "piece_storage.h"

PieceStorage::PieceStorage(const TorrentFile &tf, const fs::path &outputDirectory) : totalPieces_(tf.pieceHashes.size()), pieceLength_(tf.pieceLength)
{
    std::cout << "creating piece storage for file " << tf.name << std::endl;
    outputFile_.open(outputDirectory / tf.name, std::ios::binary | std::ios::out);
    if (!outputFile_.is_open())
    {
        std::cout << "output file isn't open in piece storage constructor" << std::endl;
    }

    for (size_t i = 0; i < totalPieces_; ++i)
    {
        remainPieces_.push(std::make_shared<Piece>(i, tf.pieceLength, tf.pieceHashes[i]));
    }

    outputFile_.seekp(tf.length - 1);
    const char *c = "\0";
    outputFile_.write(c, 1);
}

PiecePtr PieceStorage::GetNextPieceToDownload()
{
    std::cout << "\nGetNextPieceToDownload\n";

    std::unique_lock<std::shared_mutex> lock(queueMutex_);
    if (!remainPieces_.empty())
    {
        PiecePtr nextPiece = remainPieces_.front();
        remainPieces_.pop();
        return nextPiece;
    }
    return nullptr;
}

bool PieceStorage::QueueIsEmpty() const
{
    std::cout << "\nQueueIsEmpty\n";

    std::shared_lock<std::shared_mutex> lock(queueMutex_);
    return remainPieces_.empty();
}

void PieceStorage::AppendPiece(const PiecePtr &piece)
{
    std::cout << "\nAppendPiece\n";

    std::unique_lock<std::shared_mutex> lock(queueMutex_);
    remainPieces_.push(piece);
}

void PieceStorage::PieceProcessed(const PiecePtr &piece)
{
    std::cout << "\nPieceProcessed\n";

    // std::unique_lock<std::shared_mutex> queueLock(queueMutex_);
    if (piece->HashMatches())
    {
        // queueLock.unlock();
        std::lock_guard<std::mutex> fileLock(fileMutex_);
        SavePieceToDisk(piece);
    }

    else
    {
        std::cout << "piece " << piece->GetIndex() << " hash does not match" << std::endl;
        piece->Reset();
        remainPieces_.push(piece);
    }
}

void PieceStorage::SavePieceToDisk(const PiecePtr &piece)
{
    std::cout << "\nSavePieceToDisk\n";
    // std::lock_guard<std::mutex> lock(fileMutex_);
    if (!outputFile_.is_open())
    {
        std::cout << "Output file is already closed" << std::endl;
        return;
    }

    for (auto ind : savedPiecesIndices_)
    {
        if (ind == piece->GetIndex())
        {
            std::cout << "Piece " << piece->GetIndex() << " double saving piece to disk" << std::endl;
            return;
        }
    }

    savedPiecesIndices_.push_back(piece->GetIndex());
    outputFile_.seekp(piece->GetIndex() * pieceLength_);
    auto data_ = piece->GetData();
    outputFile_.write(data_.data(), data_.size());
    std::cout << "Saved piece to Disk " << piece->GetIndex() << std::endl;
    std::cout << "Have already saved " << savedPiecesIndices_.size() << " pieces " << std::endl;
}

void PieceStorage::CloseOutputFile()
{
    std::cout << "\nCloseOutputFile\n";

    std::lock_guard<std::mutex> lock(fileMutex_);
    if (outputFile_.is_open())
    {
        outputFile_.close();
    }
    else
    {
        std::cout << "double closing output file" << std::endl;
    }
}

size_t PieceStorage::PiecesSavedToDiscCount() const
{
    std::cout << "\nPiecesSavedToDiscCount\n";

    std::shared_lock<std::shared_mutex> lock(queueMutex_);
    return savedPiecesIndices_.size();
}

const std::vector<size_t> &PieceStorage::GetPiecesSavedToDiscIndices() const
{
    std::cout << "\n GetPiecesSavedToDiscIndices\n";
    std::shared_lock<std::shared_mutex> lock(queueMutex_);
    return savedPiecesIndices_;
}

size_t PieceStorage::PiecesInProgressCount() const
{
    std::cout << "\n TotalPiecesCount\n";
    std::shared_lock<std::shared_mutex> lock(queueMutex_);
    return totalPieces_ - remainPieces_.size() - savedPiecesIndices_.size();
}

size_t PieceStorage::TotalPiecesCount() const
{
    std::cout << "\n TotalPiecesCount\n";
    return totalPieces_;
}