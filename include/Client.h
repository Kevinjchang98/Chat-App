#include <netinet/in.h>

#include <thread>
#include <chatHistory.h>

#ifndef CLIENT_H
#define CLIENT_H

#pragma once

class Client {
   public:
    Client(const std::string ip_address, const int port,
           std::shared_ptr<chatHistory>);
    ~Client();
    void sendMessage(const std::string message);
    void receiveMessage();
    void stop();

   private:
    bool stopListening;
    sockaddr_in sendSockAddr;
    int serverSock;
    int clientSd;
    const int MAX_CHAR = 1500;
    std::shared_ptr<chatHistory> history;
};

#endif /* CLIENT_H */