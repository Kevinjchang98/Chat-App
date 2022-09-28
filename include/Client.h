#include <ChatHistory.h>
#include <netinet/in.h>

#include <thread>
#include <memory>

#ifndef CLIENT_H
#define CLIENT_H

#pragma once

class Client {
   public:
    Client(const std::string ip_address, const int port,
           std::shared_ptr<ChatHistory>);
    ~Client();
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
};

#endif /* CLIENT_H */