#ifndef GUI_H
#define GUI_H

#include "NetworkHelper.h"
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
    // ImGui parameters
    static constexpr int TEXT_MESSAGE_SIZE = 1024 * 8;
    static constexpr int INIT_WINDOW_WIDTH = 400;
    static constexpr int INIT_WINDOW_HEIGHT = 720;

    // ImGui window states
    enum screen { login, connecting, chat };

    // Network Helper
    std::unique_ptr<NetworkHelper> connection;

    // ImGui state
    screen CURR_SCREEN = login;
    int PORT;
    std::string IP_ADDRESS;
    std::counting_semaphore<1> ATTEMPT_CONNECT{0};  // TODO: Check syntax
    bool IS_SERVER;
    std::string myName;

    // TODO: Fix callback function
    static void glfw_error_callback(int error, const char* description);
    // Check if addr and port given are valid
    static bool connectionDataIsValid(std::string, int);
    // Send message
    bool handleSend(char*, std::shared_ptr<ChatHistory>);
    // Run main GUI loop
    void runImgui(std::shared_ptr<ChatHistory>);
    // Init server/client based on user choice
    void connectHelper(std::shared_ptr<ChatHistory>);
};

#endif /* GUI_H */
