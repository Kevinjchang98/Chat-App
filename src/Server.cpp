#include "Server.h"

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
 * @brief Construct a new Server:: Server object
 *
 * @param port_no Port number to listen on
 */
Server::Server(const int port_no, chatHistory* history) {
    std::cout << "Server constructed\n";
    stopListening = false;
    this->history = history;

    // Setup a socket and connection tools
    // bzero((char *)&servAddr, sizeof(servAddr));
    servAddr = {};  // TODO: Verify same behavior as bzero()
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port_no);

    // Open stream oriented socket with internet address
    // also keep track of the socket descriptor
    serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSd < 0) {
        std::cerr << "Error establishing the server socket" << std::endl;
        exit(0);
    }

    // Bind the socket to its local address
    int bindStatus =
        bind(serverSd, (struct sockaddr *)&servAddr, sizeof(servAddr));
    if (bindStatus < 0) {
        std::cerr << "Error binding socket to local address" << std::endl;
        exit(0);
    }
    std::cout << "Waiting for a host to connect..." << std::endl;

    // Listen for up to 5 requests at a time
    listen(serverSd, 5);

    // Receive a request from client using accept
    // We need a new address to connect with the client
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);

    // Accept, create a new socket descriptor to
    // handle the new connection with client
    newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if (newSd < 0) {
        std::cerr << "Error accepting request from client!" << std::endl;
        exit(0);
    }

    // Create new thread to listen for incoming messages
    std::cout << "Creating listen thread" << std::endl;

    std::thread listener([this]{ this->receiveMessage(); });
    listener.detach();
}

/**
 * @brief Destroy the Server:: Server object
 *
 */
Server::~Server() { std::cout << "Server() destroyed"; }

/**
 * @brief Sends a single message
 *
 * @param data Message to be sent as a string.
 */
void Server::sendMessage(const std::string data) {
    char msg[MAX_CHAR];

    memset(&msg, 0, sizeof(msg));  // clear the buffer
    strcpy(msg, data.c_str());     // copy from data to msg buffer

    send(newSd, (char *)&msg, strlen(msg), 0);
}

/**
 * @brief Wait until a message is received and print it to console
 *
 */
void Server::receiveMessage() {
    char msg[MAX_CHAR];

    std::time_t time_now = std::time(nullptr);
    char *t = ctime(&time_now);

    while (!stopListening) {
        memset(&msg, 0, sizeof(msg));  // clear the buffer

        recv(newSd, (char *)&msg, sizeof(msg), 0);

        // if (!strcmp(msg, "exit")) {
        //     std::cout << "Server has quit the session" << std::endl;
        //     break;
        // }

        std::cout << t << "Client: " << msg << std::endl;
        // TODO: Not actually adding properly; confirm correct pointer passing
        history->addMessage(msg, "Client");
    }

    std::cout << "Server stopped listening\n";
}

/**
 * @brief Stops listening for new messages
 *
 */
void Server::stop() { stopListening = true; }