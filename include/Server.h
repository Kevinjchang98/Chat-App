#include <ChatHistory.h>
#include <netinet/in.h>

#include <thread>
#include <memory>

#ifndef SERVER_H
#define SERVER_H

#pragma once

class Server {
   public:
    Server(const int port_no, std::shared_ptr<ChatHistory> history);
    ~Server();
    void sendMessage(const std::string data);
    void receiveMessage();
    void stop();

   private:
    bool stopListening;
    int serverSd;
    int newSd;
    sockaddr_in servAddr;
    // sockaddr_in newSockAddr;
    // socklen_t newSockAddrSize;
    const int MAX_CHAR = 1500;
    std::shared_ptr<ChatHistory> history;
};

#endif /* SERVER_H */