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
    void joinThreads(); 
    void receiveMessage();
    // int getClient();
    // std::string getIP();

   private:
    char *ip_address;
    int port_no;
    char msg;
    bool stopListening;
    std::string data;
    int serverSd;
    int newSd;
    sockaddr_in servAddr;
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize;
    std::thread listener; 
    int MAX_CHAR = 1500; 
};

#endif /* SERVER_H */