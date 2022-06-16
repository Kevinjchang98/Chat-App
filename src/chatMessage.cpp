#include "chatMessage.h"

chatMessage::chatMessage() {
    message = "";
    sender = "Unknown";
    timestamp = time(NULL);
}

chatMessage::chatMessage(std::string inMessage, std::string inSender) {
    setMessage(inMessage, inSender);
    timestamp = time(NULL);
}

chatMessage::~chatMessage() {}

void chatMessage::setMessage(std::string input) { message = input; }

void chatMessage::setMessage(std::string inMessage, std::string inSender) {
    message = inMessage;
    sender = inSender;
}

void chatMessage::setSender(std::string input) { sender = input; }

void chatMessage::setTime() { timestamp = time(NULL); }

std::string chatMessage::getMessage() { return message; }

std::string chatMessage::getSender() { return sender; }

std::time_t chatMessage::getTimestamp() { return timestamp; }