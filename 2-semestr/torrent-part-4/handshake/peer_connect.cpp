#include "byte_tools.h"
#include "peer_connect.h"
#include "message.h"
#include <iostream>
#include <sstream>
#include <utility>
#include <cassert>

using namespace std::chrono_literals;

PeerConnect::PeerConnect(const Peer &peer, const TorrentFile &tf, std::string selfPeerId)
    : tf_(tf), socket_(peer.ip, peer.port, 1000ms, 1000ms), selfPeerId_(selfPeerId), terminated_(false), choked_(true) {}

PeerPiecesAvailability::PeerPiecesAvailability(std::string bitfield) : bitfield_(bitfield) {}

bool PeerPiecesAvailability::IsPieceAvailable(size_t pieceIndex) const
{
    if (pieceIndex / 8 >= bitfield_.size())
    {
        return false;
    }
    return (bitfield_[pieceIndex / 8] & (1 << (pieceIndex % 8))) != 0;
}

size_t PeerPiecesAvailability::Size() const
{
    return bitfield_.size() * 8;
}

// Пометить часть файла как доступную
void PeerPiecesAvailability::SetPieceAvailability(size_t pieceIndex)
{
    // if (pieceIndex / 8 >= bitfield_.size())
    // {
    //     bitfield_.resize((pieceIndex / 8) + 1, 0);
    // }
    bitfield_[pieceIndex / 8] |= (1 << (pieceIndex % 8));
}

void PeerConnect::Run()
{
    while (!terminated_)
    {
        try
        {
            if (EstablishConnection())
            {
                std::cout << "__Connection established to peer" << std::endl;
                MainLoop();
            }
            else
            {
                std::cerr << "__Cannot establish connection to peer" << std::endl;
                Terminate();
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "__Exception occurred: " << e.what() << std::endl;
            Terminate();
        }
    }
}
void PeerConnect::PerformHandshake()
{

    std::cerr << "_Starting handshake with " << socket_.GetIp() << ":" << socket_.GetPort() << std::endl;
    socket_.EstablishConnection();
    std::cerr << "_Have established connection with socket" << std::endl;
    const std::string pstr = "BitTorrent protocol";
    const size_t pstrlen = 19;

    const std::string reserved(8, '\0');
    std::string handshake(0, '\0');
    handshake += (char)pstrlen;
    handshake += pstr;
    handshake += reserved;
    handshake += tf_.infoHash;
    handshake += selfPeerId_;

    std::cerr << "_Sending handshake to " << socket_.GetIp() << ":" << socket_.GetPort() << std::endl;
    socket_.SendData(handshake);

    const size_t expectedLength = 49 + pstrlen;
    std::string response = socket_.ReceiveData(expectedLength);

    if (response.length() < expectedLength)
    {
        throw std::runtime_error("_Invalid handshake response length");
    }

    const std::string receivedInfoHash = response.substr(28, 20);
    const std::string receivedPeerId = response.substr(48, 20);

    if (receivedInfoHash != tf_.infoHash)
    {
        throw std::runtime_error("_Invalid handshake: info_hash mismatch");
    }
    if (receivedPeerId == selfPeerId_)
    {
        throw std::runtime_error("_Invalid handshake: received own peer ID");
    }
    peerId_ = receivedPeerId;
    std::cout << "_Handshake successful with " << socket_.GetIp() << std::endl;
}

bool PeerConnect::EstablishConnection()
{
    try
    {
        PerformHandshake();
        ReceiveBitfield();
        SendInterested();
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "_Failed to establish connection with peer in PeerConncet function "
                  << socket_.GetIp() << ":" << socket_.GetPort() << " -- " << e.what() << std::endl;
        return false;
    }
}
void PeerConnect::ReceiveBitfield()
{
    Message message = Message::Parse(socket_.ReceiveData());

    if (message.id == MessageId::BitField)
    {
        piecesAvailability_ = PeerPiecesAvailability(message.payload);
    }
    else if (message.id == MessageId::Unchoke)
    {
        choked_ = false;
        piecesAvailability_ = PeerPiecesAvailability(std::string(tf_.pieceHashes.size() / 8 + bool(tf_.pieceHashes.size() % 8), '\0'));
    }
    else
    {
        std::cerr << "_Unexpected message type received: " << static_cast<int>(message.id) << std::endl;
    }
}

void PeerConnect::SendInterested()
{

    Message interested = Message::Init(MessageId::Interested, "");
    socket_.SendData(interested.ToString());
}

void PeerConnect::Terminate()
{
    std::cerr << "Terminate" << std::endl;
    terminated_ = true;
    socket_.CloseConnection();
}

void PeerConnect::MainLoop()
{
    /*
     * При проверке вашего решения на сервере этот метод будет переопределен.
     * Если вы провели handshake верно, то в этой функции будет работать обмен данными с пиром
     */
    std::cout << "Dummy main loop" << std::endl;
    Terminate();
}
