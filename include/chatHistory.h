#ifndef CHATHISTORY_H
#define CHATHISTORY_H

#pragma once

#include <string>
#include <vector>

#include "chatMessage.h"

class chatHistory {
   public:
    chatHistory();
    ~chatHistory();

    void addMessage(std::string, std::string);
    std::vector<chatMessage> getChatHistory();
    bool hasNewMessage();

   private:
    std::vector<chatMessage> histVec;
    int oldSize;
};

#endif