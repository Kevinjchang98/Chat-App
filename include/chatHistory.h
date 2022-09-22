#ifndef CHATHISTORY_H
#define CHATHISTORY_H

#pragma once

#include <string>
#include <vector>

#include "chatMessage.h"

class ChatHistory {
   public:
    ChatHistory();
    ~ChatHistory();

    void addMessage(std::string, std::string);
    std::vector<ChatMessage> getChatHistory();
    bool hasNewMessage();

   private:
    std::vector<ChatMessage> histVec;
    int oldSize;
};

#endif