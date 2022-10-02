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
    // ImGui parameters
    static constexpr int TEXT_MESSAGE_SIZE = 1024 * 8;
    static constexpr int INIT_WINDOW_WIDTH = 400;
    static constexpr int INIT_WINDOW_HEIGHT = 720;

    // ImGui window states
    enum screen { login, connecting, chat };

    // Server and Client
    std::unique_ptr<Server> myServer;
    std::unique_ptr<Client> myClient;

    // ImGui state
    screen CURR_SCREEN = login;
    int PORT;
    std::string IP_ADDRESS;
    std::counting_semaphore<1> ATTEMPT_CONNECT{0};  // TODO: Check syntax
    bool IS_SERVER;
    std::string myName;

    // TODO: Fix callback function
    static void glfw_error_callback(int error, const char* description);
    // Send message
    bool handleSend(char* text, std::shared_ptr<ChatHistory> history);
    // Check if addr and port given are valid
    bool connectionDataIsValid();
    // Run main GUI loop
    void runImgui(std::shared_ptr<ChatHistory> history);
    // Init server/client based on user choice
    void connectHelper(std::shared_ptr<ChatHistory> history);
};

#endif /* GUI_H */