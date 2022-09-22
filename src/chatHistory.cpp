#include "chatHistory.h"

chatHistory::chatHistory() { oldSize = 0; }

chatHistory::~chatHistory() {}

void chatHistory::addMessage(std::string message, std::string sender) {
    chatMessage newMessage;
    newMessage.setMessage(message, sender);
    histVec.push_back(newMessage);
}

std::vector<chatMessage> chatHistory::getChatHistory() { return histVec; }

bool chatHistory::hasNewMessage() {
    if (oldSize != histVec.size()) {
        oldSize = histVec.size();
        return true;
    }

    return false;
}