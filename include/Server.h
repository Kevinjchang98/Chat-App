#include <netinet/in.h>

#include <thread>

#ifndef SERVER_H
#define SERVER_H

#pragma once

class Server {
   public:
    Server(int port_no);
    ~Server();
    void sendMessage(std::string data);
    void receiveMessage();
    void stop();

   private:
    bool stopListening;
    int serverSd;
    int newSd;
    sockaddr_in servAddr;
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize;
    int MAX_CHAR = 1500;
};

#endif /* SERVER_H */