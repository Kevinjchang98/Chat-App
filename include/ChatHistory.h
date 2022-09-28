#ifndef CHATHISTORY_H
#define CHATHISTORY_H

#pragma once

#include <string>
#include <vector>

#include "ChatMessage.h"

class ChatHistory {
   public:
    ChatHistory();
    ~ChatHistory();

    void addMessage(std::string, std::string);
    std::vector<ChatMessage> getChatHistory();
    bool hasNewMessage();

   private:
    std::vector<ChatMessage> histVec;
    std::vector<ChatMessage>::size_type oldSize;
};

#endif