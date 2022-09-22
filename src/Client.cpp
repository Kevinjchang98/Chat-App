#include "Client.h"

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <ctime>
#include <iostream>
#include <thread>

/**
 * @brief Construct a new Client:: Client object
 *
 * @param ip_address IP address to connect to
 * @param port Port number to connect to
 */
Client::Client(const std::string ip_address, const int port,
               std::shared_ptr<chatHistory> history) {
    std::cout << "Client constructed\n";
    stopListening = false;
    this->history = history;

    // Setup a socket and connection tools
    // bzero((char *)&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr = {};  // TODO: Verify same behavior as bzero();
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr =
        inet_addr(const_cast<char *>(ip_address.c_str()));
    sendSockAddr.sin_port = htons(port);
    clientSd = socket(AF_INET, SOCK_STREAM, 0);

    // Try to connect...
    int status =
        connect(clientSd, (sockaddr *)&sendSockAddr, sizeof(sendSockAddr));
    if (status < 0) {
        std::cout << "Error connecting to socket!" << std::endl;
    }
    std::cout << "Connected to the server!" << std::endl;

    // Create new thread to listen for incoming messages
    std::cout << "Creating listen thread" << std::endl;

    std::thread listener([this] { this->receiveMessage(); });
    listener.detach();
}

/**
 * @brief Destroy the Client:: Client object
 *
 */
Client::~Client() { std::cout << "Client object destroyed\n"; }

/**
 * @brief Send a single message
 *
 * @param data Message to be sent as string.
 */
void Client::sendMessage(const std::string data) {
    char msg[MAX_CHAR];

    memset(&msg, 0, sizeof(msg));  // clear the buffer
    strcpy(msg, data.c_str());     // copy from data to msg buffer

    send(clientSd, (char *)&msg, strlen(msg), 0);
}

/**
 * @brief Wait until a message is received and print it to console
 *
 */
void Client::receiveMessage() {
    char msg[MAX_CHAR];

    std::time_t time_now = std::time(nullptr);
    char *t = ctime(&time_now);

    while (!stopListening) {
        memset(&msg, 0, sizeof(msg));  // clear the buffer

        recv(clientSd, (char *)&msg, sizeof(msg), 0);

        // if(!strcmp(msg, "exit")) {
        //     std::cout << "Server has quit the session" << std::endl;
        //     break;
        // }

        std::cout << t << "Server: " << msg << std::endl;

        // Push incoming message to chatHistory
        this->history->addMessage(msg, "Server");
    }

    std::cout << "Client stopped listening\n";
}

/**
 * @brief Stops listening for new messages
 *
 */
void Client::stop() { stopListening = true; }