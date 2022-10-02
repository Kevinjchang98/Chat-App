#include <ChatHistory.h>
#include <netinet/in.h>

#include <memory>
#include <thread>

#ifndef SERVER_H
#define SERVER_H

#pragma once

class Server {
   public:
    Server(const int port_no, std::shared_ptr<ChatHistory> history);
    ~Server();
    void sendMessage(const std::string data);
    void receiveMessage();
    void exchangeUsernames(const std::string myName);
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
    std::string username;
    std::string clientName;
};

#endif /* SERVER_H */