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
    std::time_t timestamp = time(NULL);
    current_time = ctime(&timestamp);
}

std::string ChatMessage::getMessage() { return message; }

std::string ChatMessage::getSender() { return sender; }

std::string ChatMessage::getTimestamp() {
    std::string timestamp = current_time; 
    return time_now; 
}

// std::string ChatMessage::convertToString(char *curr_time) {
//     std::string time_now = curr_time;
//     return time_now;
// }
