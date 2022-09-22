#include "ChatMessage.h"

ChatMessage::ChatMessage() {
    message = "";
    sender = "Unknown";
    // timestamp = time(NULL);
}

ChatMessage::ChatMessage(std::string inMessage, std::string inSender) {
    setMessage(inMessage, inSender);
    // timestamp = time(NULL);
}

ChatMessage::~ChatMessage() {}

void ChatMessage::setMessage(std::string input) { message = input; }

void ChatMessage::setMessage(std::string inMessage, std::string inSender) {
    message = inMessage;
    sender = inSender;
}

void ChatMessage::setSender(std::string input) { sender = input; }

// void ChatMessage::setTime() { timestamp = time(NULL); }

std::string ChatMessage::getMessage() { return message; }

std::string ChatMessage::getSender() { return sender; }

// std::time_t ChatMessage::getTimestamp() { return timestamp; }