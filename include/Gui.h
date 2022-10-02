#ifndef GUI_H
#define GUI_H

#pragma once

#include <ChatHistory.h>
#include <Client.h>
#include <Server.h>

#include <semaphore>

class Gui {
   public:
    Gui();
    ~Gui();

   private:
    static constexpr int TEXT_MESSAGE_SIZE = 1024 * 8;
    static constexpr int INIT_WINDOW_WIDTH = 400;
    static constexpr int INIT_WINDOW_HEIGHT = 720;

    enum screen { login, connecting, chat };

    std::unique_ptr<Server> myServer;
    std::unique_ptr<Client> myClient;

    screen CURR_SCREEN = login;
    int PORT;
    std::string IP_ADDRESS;
    std::counting_semaphore<1> ATTEMPT_CONNECT{0};  // TODO: Check syntax
    bool IS_SERVER;
    std::string myName;

    static void glfw_error_callback(int error, const char* description);
    bool handleSend(char* text, std::shared_ptr<ChatHistory> history);
    bool connectionDataIsValid();
    void runImgui(std::shared_ptr<ChatHistory> history);
    void connectHelper(std::shared_ptr<ChatHistory> history);
};

#endif /* GUI_H */