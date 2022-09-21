#include <netinet/in.h>

#include <thread>

#ifndef CLIENT_H
#define CLIENT_H

#pragma once

class Client {
   public:
    Client(char* ip_address, int port);
    ~Client();
    void sendMessage(std::string message);
    void receiveMessage();
    void stop();

   private:
    bool stopListening;
    sockaddr_in sendSockAddr;
    int serverSock;
    int clientSd;
    int MAX_CHAR = 1500; 
};

#endif /* CLIENT_H */