#include "ChatMessage.h"

#include <ctime>

ChatMessage::ChatMessage() {
    message = "";
    sender = "Unknown";
}

ChatMessage::ChatMessage(std::string inMessage, std::string inSender) {
    setMessage(inMessage, inSender);
}

ChatMessage::~ChatMessage() {}

void ChatMessage::setMessage(std::string input) { message = input; }

void ChatMessage::setMessage(std::string inMessage, std::string inSender) {
    message = inMessage;
    sender = inSender;
}

void ChatMessage::setSender(std::string input) { sender = input; }

void ChatMessage::setTime() {
    time_t time_now = time(NULL);
    char *ct = ctime(&time_now);
    timestamp = ct; 
}

std::string ChatMessage::getMessage() { return message; }

std::string ChatMessage::getSender() { return sender; }

std::string ChatMessage::getTimestamp() { return timestamp; }
