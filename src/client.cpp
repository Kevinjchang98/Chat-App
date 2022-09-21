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
 * @param port_no Port number to connect to
 */
Client::Client(char *ip_address, int port_no) {
    std::cout << "Client constructed\n";
    this->ip_address = ip_address;
    this->port_no = port_no;
    stopListening = false; 

    // Setup a socket and connection tools
    bzero((char *)&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr = inet_addr(ip_address);
    sendSockAddr.sin_port = htons(port_no);
    clientSd = socket(AF_INET, SOCK_STREAM, 0);

    // Try to connect...
    int status =
        connect(clientSd, (sockaddr *)&sendSockAddr, sizeof(sendSockAddr));
    if (status < 0) {
        std::cout << "Error connecting to socket!" << std::endl;
    }
    std::cout << "Connected to the server!" << std::endl;

    // [cc] (p) {fd};
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
void Client::sendMessage(std::string data) {
    char msg[MAX_CHAR];

    memset(&msg, 0, sizeof(msg));   // clear the buffer
    strcpy(msg, data.c_str());      // copy from data to msg buffer 

    send(clientSd, (char *)&msg, strlen(msg), 0);
}

/**
 * @brief Wait until a message is received and print it to console
 *
 */
void Client::receiveMessage() {
    char msg[MAX_CHAR];

    std::time_t time_now = std::time(nullptr); 
    char* t = ctime(&time_now); 

    while (true) {
        // if (stopListening == true) return;
        memset(&msg, 0, sizeof(msg));  // clear the buffer
        recv(clientSd, (char *)&msg, sizeof(msg), 0);
        if(!strcmp(msg, "exit")) {
            std::cout << "Server has quit the session" << std::endl;
            break;
        }
        std::cout << t << "Server: " << msg << std::endl;

        // Re-show prompt; this will not be needed with ImGui
        std::cout << "Enter your message: " << std::endl;
    }
    std::cout << "Client stopped listening\n";
}

// A method we expect the client to run. Thinking about it more we probably
// could just do this in the constructor idk
// void Client::init() {
//     receiveMessagesThread = std::thread(&Client::receiveMessages, this);
// }

// We want to run this at the end to join the receiveMessagesThread
void Client::joinThreads() {
    stopListening = true;
    std::cout << "Exiting\n";
    if (listener.joinable()) {
        listener.join();
        std::cout << "Receive messages thread joined\n";
    };
    close(clientSd); 
    std::cout << "End of session\n"; 
}

// std::string Client::getIP() { return ip_address; }

