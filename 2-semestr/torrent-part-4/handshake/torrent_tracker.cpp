#include "torrent_tracker.h"
#include "bencode.h"
#include "byte_tools.h"
#include <cpr/cpr.h>

using namespace Bencode;

TorrentTracker::TorrentTracker(const std::string &url) : url_(url) {}

void TorrentTracker::UpdatePeers(const TorrentFile &tf, std::string peerId, int port)
    {
        cpr::Response res = cpr::Get(
            cpr::Url{tf.announce},
            cpr::Parameters{
                {"info_hash", tf.infoHash},
                {"peer_id", peerId},
                {"port", std::to_string(port)},
                {"uploaded", std::to_string(0)},
                {"downloaded", std::to_string(0)},
                {"left", std::to_string(tf.length)},
                {"compact", std::to_string(1)}},
            cpr::Timeout{20000});

        std::istringstream text(res.text, std::ios::binary);
        BencodeValue ParsedText = ParseBencode(text);

        BencodeDict dict = std::get<BencodeDict>(ParsedText);

        BencodeString peers = std::get<BencodeString>(dict.at("peers"));
        for (size_t i = 0; i < peers.size(); i += 6)
        {
            Peer peer;

            peer.ip += std::to_string((unsigned char)(peers[i]));

            for (int j = 1; j < 4; ++j)
            {
                peer.ip += ".";
                peer.ip += std::to_string((unsigned char)(peers[i + j]));
            }

            uint16_t a1 = (unsigned char)(peers[i + 4]);
            uint16_t a2 = (unsigned char)(peers[i + 5]);

            peer.port = (a1 << 8) | a2;

            peers_.push_back(peer);

        }
    }


const std::vector<Peer> &TorrentTracker::GetPeers() const {
    return peers_;
}
