#include "piece_storage.h"
#include <iostream>

PieceStorage::PieceStorage(const TorrentFile &tf) : totalPieces_(tf.pieceHashes.size())
{
    totalPieces_ = tf.length / tf.pieceLength;
    for (size_t i = 0; i < totalPieces_; ++i)
    {
        remainPieces_.push(std::make_shared<Piece>(i, tf.pieceLength, tf.pieceHashes[i]));
    }
    size_t lastPieceLength = tf.length % tf.pieceLength;
    if (lastPieceLength > 0)
    {
        remainPieces_.push(std::make_shared<Piece>(totalPieces_, lastPieceLength, tf.pieceHashes[totalPieces_]));
    }
}

PiecePtr PieceStorage::GetNextPieceToDownload()
{
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
    return remainPieces_.empty();
}

size_t PieceStorage::TotalPiecesCount() const
{
    return totalPieces_;
}

void PieceStorage::SavePieceToDisk(PiecePtr piece)
{
    // Эта функция будет переопределена при запуске вашего решения в проверяющей системе
    // Вместо сохранения на диск там пока что будет проверка, что часть файла скачалась правильно
    std::cout << "Downloaded piece " << piece->GetIndex() << std::endl;
    std::cerr << "Clear pieces list, don't want to download all of them" << std::endl;
    while (!remainPieces_.empty())
    {
        remainPieces_.pop();
    }
}

void PieceStorage::PieceProcessed(const PiecePtr &piece)
{
    if (piece->HashMatches())
    {
        SavePieceToDisk(piece);
        while (!remainPieces_.empty())
        {
            remainPieces_.pop();
        }
    }
    piece->Reset();
}

void PieceStorage::AppendPiece(const PiecePtr &piece)
{
    remainPieces_.push(piece);
}
