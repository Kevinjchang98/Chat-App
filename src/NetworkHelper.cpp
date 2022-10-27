#include <memory>
#include <string>

#include "NetworkHelper.h"

NetworkHelper::NetworkHelper(bool isServer, std::string addr, int port,
                             std::shared_ptr<ChatHistory> history) {
    this->isServer = isServer;
    if (isServer) {
        this->myServer = std::make_unique<Server>(port, history);
    } else {
        this->myClient = std::make_unique<Client>(addr, port, history);
    }
}

NetworkHelper::~NetworkHelper() {}

void NetworkHelper::exchangeUsernames(const std::string& myName) {
    if (isServer)
        myServer->exchangeUsernames(myName);
    else
        myClient->exchangeUsernames(myName);
}

void NetworkHelper::sendMessage(const std::string& message) {
    if (isServer)
        myServer->sendMessage(message);
    else
        myClient->sendMessage(message);
}

/**
 * @brief Checks if IP_ADDRESS and PORT global variables are valid
 *
 * @return true If both are valid
 * @return false If at least one is invalid
 */
bool NetworkHelper::connectionDataIsValid(std::string ip, int port) {
    // TODO: Check IP_ADDRESS and PORT are valid in format
    return true;
}