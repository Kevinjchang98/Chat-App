#include "ChatHistory.h"

ChatHistory::ChatHistory() { oldSize = 0; }

ChatHistory::~ChatHistory() {}

void ChatHistory::addMessage(std::string message, std::string sender) {
    ChatMessage newMessage;
    newMessage.setTime(); 
    newMessage.setMessage(message, sender);
    histVec.push_back(newMessage);
}

std::vector<ChatMessage> ChatHistory::getChatHistory() { return histVec; }

bool ChatHistory::hasNewMessage() {
    if (oldSize != histVec.size()) {
        oldSize = histVec.size();
        return true;
    }

    return false;
}