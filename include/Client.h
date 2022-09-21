#include <netinet/in.h>

#include <thread>

#ifndef CLIENT_H
#define CLIENT_H

#pragma once

class Client {
   public:
    Client(std::string ip_address, int port);
    ~Client();
    void sendMessage(std::string message);
    void receiveMessage();
    void joinThreads();
    std::string getIP();

   private:
    char *ip_address;
    int port_no;
    char msg;
    bool stopListening;
    std::string data;
    sockaddr_in sendSockAddr;
    int serverSock;
    int clientSd;
    std::thread listener; 
    int MAX_CHAR = 1500; 
};

#endif /* CLIENT_H */