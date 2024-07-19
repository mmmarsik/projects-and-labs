#include "message.h"
#include "byte_tools.h"
#include <netinet/in.h>
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <utility>

Message::Message(MessageId id_, size_t messageLength_, std::string payload_)
    : id(id_), messageLength(messageLength_), payload(std::move(payload_)) {}

Message Message::Parse(const std::string &messageString)
{
    std::cerr << "Parsing message..." << std::endl;

    size_t messageLength = messageString.size();

    if (messageLength == 0)
    {
        return Message(MessageId::KeepAlive, 0, "");
    }

    MessageId id = static_cast<MessageId>(messageString[0]);
    std::string payload = messageString.substr(1);
    return Message(id, messageLength, payload);
}

Message Message::Init(MessageId id, const std::string &payload)
{
    if (id == MessageId::KeepAlive)
    {
        return Message(id, 0, "");
    }
    size_t messageLength = 1 + payload.size();
    return Message(id, messageLength, payload);
}

std::string Message::ToString() const
{
    std::cerr << "Converting message to string..." << std::endl;
    std::string messageString;
    messageString.reserve(1 + payload.size());

    uint32_t bigEndianLength = htonl(messageLength);

    if (messageLength == 0)
    {
        return std::string(4, '\0');
    }

    const char *bytes = reinterpret_cast<const char *>(&bigEndianLength);
    for (int i = 0; i < 4; ++i)
    {
        messageString.push_back(bytes[i]);
    }

    messageString.push_back(static_cast<char>(id));
    messageString += payload;

    std::cerr << "Message string created." << std::endl;
    return messageString;
}