#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#pragma once

#include <string>
#include <ctime>

class ChatMessage {
   public:
    ChatMessage();
    ChatMessage(std::string, std::string);
    ~ChatMessage();

    void setMessage(std::string);
    void setMessage(std::string, std::string);
    void setSender(std::string);
    void setTime();

    std::string getMessage();
    std::string getSender();
    std::string getTimestamp();

   private:
    std::string message;
    std::string sender;
    std::string timestamp;
};

#endif