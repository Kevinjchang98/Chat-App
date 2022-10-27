#ifndef NETWORKHELPER_H
#define NETWORKHELPER_H

#include <string>
#pragma once

#include <Client.h>
#include <Server.h>

#include <memory>

class NetworkHelper {
   public:
    NetworkHelper(bool isServer, std::string addr, int port,
                  std::shared_ptr<ChatHistory> history);
    ~NetworkHelper();
    void exchangeUsernames(const std::string& myName);
    void sendMessage(const std::string& message);

    // Check if addr and port given are valid
    static bool connectionDataIsValid(std::string, int);

   private:
    bool isServer;

    // Server and Client
    std::unique_ptr<Server> myServer;
    std::unique_ptr<Client> myClient;
};

#endif