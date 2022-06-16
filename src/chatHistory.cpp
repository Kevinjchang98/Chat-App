#include "chatHistory.h"

chatHistory::chatHistory() {}

chatHistory::~chatHistory() {}

void chatHistory::addMessage(std::string message, std::string sender) {
    chatMessage newMessage;
    newMessage.setMessage(message, sender);
    histVec.push_back(newMessage);
}

std::vector<chatMessage> chatHistory::getChatHistory() { return histVec; }