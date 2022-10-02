#include <ChatHistory.h>
#include <netinet/in.h>

#include <memory>
#include <thread>

#ifndef CLIENT_H
#define CLIENT_H

#pragma once

class Client {
   public:
    Client(const std::string ip_address, const int port,
           std::shared_ptr<ChatHistory>);
    ~Client();
    void exchangeUsernames(const std::string myName);
    void sendMessage(const std::string message);
    void receiveMessage();
    void stop();

   private:
    bool stopListening;
    sockaddr_in sendSockAddr;
    // int serverSock;
    int clientSd;
    const int MAX_CHAR = 1500;
    std::shared_ptr<ChatHistory> history;
    std::string username;
    std::string serverName;
};

#endif /* CLIENT_H */