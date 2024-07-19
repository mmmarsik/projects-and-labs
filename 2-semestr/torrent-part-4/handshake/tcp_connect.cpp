#include "tcp_connect.h"
#include "byte_tools.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <cstring>
#include <iostream>
#include <chrono>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <limits>
#include <utility>

TcpConnect::TcpConnect(std::string ip, int port, std::chrono::milliseconds connectTimeout, std::chrono::milliseconds readTimeout)
    : ip_(ip), port_(port), connectTimeout_(connectTimeout), readTimeout_(readTimeout), sock_(-1) {}

TcpConnect::~TcpConnect()
{
    CloseConnection();
}

void TcpConnect::EstablishConnection()
{
    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ == -1)
    {
        throw std::runtime_error("_Socket");
    }

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip_.c_str());
    address.sin_port = htons(port_);

    int flags = fcntl(sock_, F_GETFL, 0);
    fcntl(sock_, F_SETFL, flags | O_NONBLOCK);

    if (connect(sock_, (struct sockaddr *)&address, sizeof(address)) == -1 && errno != EINPROGRESS)
    {
        close(sock_);
        sock_ = -1;
        throw std::runtime_error("_Connection failed");
    }

    fd_set writefds;
    FD_ZERO(&writefds);
    FD_SET(sock_, &writefds);
    struct timeval timeout;
    timeout.tv_sec = connectTimeout_.count() / 1000;
    timeout.tv_usec = (connectTimeout_.count()) * 1000;

    if (select(sock_ + 1, nullptr, &writefds, nullptr, &timeout) <= 0)
    {
        close(sock_);
        sock_ = -1;
        throw std::runtime_error("_Connection timeout ");
    }

    int err;
    socklen_t len = sizeof(err);
    getsockopt(sock_, SOL_SOCKET, SO_ERROR, &err, &len);
    if (err != 0)
    {
        close(sock_);
        sock_ = -1;
        throw std::runtime_error("_Connection failed");
    }
}

void TcpConnect::SendData(const std::string &data) const
{
    send(sock_, data.c_str(), data.length(), 0);
}

void TcpConnect::CloseConnection()
{
    if (sock_ != -1)
    {
        close(sock_);
        sock_ = -1;
    }
}

std::string TcpConnect::ReceiveData(size_t bufferSize) const
{
    struct pollfd fds;
    fds.fd = sock_;
    fds.events = POLLIN;
    int ret = poll(&fds, 1, readTimeout_.count());

    if (ret == -1)
    {
        throw std::runtime_error("_Poll failed");
    }
    else if (ret == 0)
    {
        throw std::runtime_error("_Receive timeout");
    }

    if (bufferSize == 0)
    {
        char length[4] = {};
        ssize_t total_bytes_received = 0;
        while (total_bytes_received < 4)
        {
            ssize_t bytes_received = recv(sock_, &length[total_bytes_received], sizeof(length), MSG_WAITALL);
            if (bytes_received < 0 && errno != EAGAIN)
            {
                std::cerr << bufferSize << ' ' << total_bytes_received << ' ' << bytes_received << ' ' << strerror(errno) << std::endl;
                throw std::runtime_error("_Failed to receive data");
            }
            else if (bytes_received == 0)
            {
                throw std::runtime_error("_Connection closed by peer");
            }
            else if (bytes_received > 0)
            {
                total_bytes_received += bytes_received;
            }
        }

        bufferSize = BytesToInt(std::string_view(length, 4));
    }

    std::string data(bufferSize, '\0');
    ssize_t total_bytes_received = 0;
    while (total_bytes_received < bufferSize)
    {
        ssize_t bytes_received = recv(sock_, &data[total_bytes_received], bufferSize, MSG_WAITALL);
        if (bytes_received < 0 && errno != EAGAIN)
        {
            std::cerr << bufferSize << ' ' << total_bytes_received << ' ' << bytes_received << ' ' << strerror(errno) << std::endl;
            throw std::runtime_error("_Failed to receive data");
        }
        else if (bytes_received == 0)
        {
            throw std::runtime_error("_Connection closed by peer");
        }
        else if (bytes_received > 0)
        {
            total_bytes_received += bytes_received;
        }
    }

    /*else if (bytes_received < bufferSize)
    {
        throw std::runtime_error("_Incomplete data received");
    }*/
    std::cout << "received " << total_bytes_received << " bytes\n";
    return data;
}

const std::string &TcpConnect::GetIp() const
{
    return ip_;
}

int TcpConnect::GetPort() const
{
    return port_;
}
