// Dear ImGui: standalone example application for GLFW + OpenGL 3, using
// programmable pipeline (GLFW is a cross-platform general purpose library for
// handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation,
// etc.) If you are new to Dear ImGui, read documentation from the docs/ folder
// + read the top of imgui.cpp. Read online:
// https://github.com/ocornut/imgui/tree/master/docs

#include <stdio.h>

#include <iostream>  // TODO: Remove later when not needed

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>  // Will drag system OpenGL headers

// Socket programming
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "Server.h"
#include "Client.h"
#include "chatHistory.h"
#include "chatMessage.h"

// Global pointers to the Client and Server objects
Server *myServer;
Client *myClient;

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to
// maximize ease of testing and compatibility with old VS compilers. To link
// with VS2010-era libraries, VS2015+ requires linking with
// legacy_stdio_definitions.lib, which we do using this pragma. Your own project
// should not be affected, as you are likely to link with a newer binary of GLFW
// that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && \
    !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// Global variables
// synchronize 
// everytime user sends message, IMGUI sets global variable to message 
// signal client server ... lock/unlock mutex
constexpr int TEXT_MESSAGE_SIZE = 1024 * 8;
constexpr int INIT_WINDOW_WIDTH = 400;
constexpr int INIT_WINDOW_HEIGHT = 720;

int PORT = -1;
std::string IP_ADDRESS = "";
bool TRY_CONNECT = false;
bool IS_SERVER = false;
bool IS_CONNECTED = false;

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

/**
 * @brief Function to handle sending the chat message
 * TODO: Currently just cout's the message
 *
 * @param text Char array of text to be sent
 * @param history The chatlog as a chatHistory*
 * @return true if successfully sent
 */
bool handleSend(char* text, chatHistory* history) {
    // TODO: Replace with desired behavior
    std::cout << "Send button pressed with text contents: " << text
              << std::endl;

    // TODO: Probably want to only add to chat history once the message has been
    // sent. Also don't hardcode "Me" as the sender
    history->addMessage(text, "Me");

    // Clear text input area
    strncpy(text, "", TEXT_MESSAGE_SIZE);

    // If successfully sent return true
    return true;
}

/**
 * @brief Main ImGUI loop
 */
void runImgui(chatHistory history) {
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) return;

// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+
    // only glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT,
                                          "Chat app", NULL, NULL);
    if (window == NULL) return;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable
    // Keyboard Controls io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; //
    // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can
    // also load multiple fonts and use ImGui::PushFont()/PopFont() to select
    // them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you
    // need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please
    // handle those errors in your application (e.g. use an assertion, or
    // display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and
    // stored into a texture when calling
    // ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame
    // below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string
    // literal you need to write a double backslash \\ !
    // io.Fonts->AddFontDefault();
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    // ImFont* font =
    // io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f,
    // NULL, io.Fonts->GetGlyphRangesJapanese()); IM_ASSERT(font != NULL);

    // Our state
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    bool justSent = true;
    bool newMessage = true;
    bool isServer = false;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard
        // flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input
        // data to your main application, or clear/overwrite your copy of
        // the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard
        // input data to your main application, or clear/overwrite your copy
        // of the keyboard data. Generally you may always pass all inputs to
        // dear imgui, and hide them from your application based on those
        // two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        /**
         * @brief Shows connection window if not connected, otherwise show
         * basic chat window
         */
        if (!IS_CONNECTED && !TRY_CONNECT) {
            // Initial connection screen

            // Init variables for IP address and port number
            // TODO: Probably directly change global state
            char ipAddress[64] = "";    
            char port[8] = "";          

            // Make window take up full system window
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(io.DisplaySize);

            // Create a window
            ImGui::Begin("Connect");

            // Create a checkbox for whether to run server or client setup
            ImGui::Checkbox("Server", &isServer);

            // Input box for IP Address
            ImGui::InputText("IP Address", ipAddress, 64,
                             ImGuiInputTextFlags_CharsDecimal);

            // Input box for Port number
            ImGui::InputText("Port", port, 64,
                             ImGuiInputTextFlags_CharsDecimal);

            // Button to connect
            if (ImGui::Button("Connect")) {
                std::cout << "Connect button clicked" << std::endl;

                IP_ADDRESS = ipAddress;
                PORT = std::stoi(port);
                IS_SERVER = isServer;
                TRY_CONNECT = true;
            };

            // Exit button TODO: interrupt and exit properly
            if (ImGui::Button("Exit")) {
                break;
            }

            ImGui::End();

        } else if (TRY_CONNECT && !IS_CONNECTED) {
            // Is loading

            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(io.DisplaySize);

            ImGui::Begin("Connecting");

            ImGui::Text("Setting up connection");

            // Exit button TODO: interrupt and exit properly
            if (ImGui::Button("Exit")) {
                break;
            }

            ImGui::End();
        } else {
            // Is connected
            int TEXTBOX_HEIGHT = ImGui::GetTextLineHeight() * 4;

            // Make window take up full system window
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(io.DisplaySize);

            // Create window
            // TODO: Probably rename this to currently connected IP or
            // something
            ImGui::Begin("Chat box");

            // Child window scrollable area
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
            ImGui::BeginChild(
                "ChildR",
                ImVec2(0, ImGui::GetContentRegionAvail().y - TEXTBOX_HEIGHT -
                              27),  // 27 for send button
                true, window_flags);

            // TODO: Format chat history
            ImGui::Dummy(ImVec2(0, ImGui::GetContentRegionAvail().y));

            for (chatMessage message : history.getChatHistory()) {
                ImGui::Spacing();
                ImGui::TextWrapped("%s", message.getSender().c_str());
                ImGui::TextWrapped("%s",
                                   ("    " + message.getMessage()).c_str());
            }

            // TODO: Revise as newMessage is updated in the future; probably
            // need to move setting newMessage to elsewhere in the code
            if (newMessage || justSent) {
                ImGui::SetScrollHereY(1.0f);
                newMessage = false;
            }

            ImGui::EndChild();
            ImGui::PopStyleVar();

            // Initial text
            char text[TEXT_MESSAGE_SIZE]; // = ""

            // Text input area flags
            ImGuiInputTextFlags input_flags =
                ImGuiInputTextFlags_EnterReturnsTrue |
                ImGuiInputTextFlags_CtrlEnterForNewLine;

            // Refocus text area if text was just sent
            if (justSent) {
                ImGui::SetKeyboardFocusHere();
                justSent = false;
            }

            // Create text area and send button
            if (ImGui::InputTextMultiline("##source", text, IM_ARRAYSIZE(text),
                                          ImVec2(-FLT_MIN, TEXTBOX_HEIGHT),
                                          input_flags) ||
                ImGui::Button("Send")) {
                justSent = handleSend(text, &history);
            };

            // Exit button
            ImGui::SameLine(ImGui::GetWindowWidth() - 44);

            if (ImGui::Button("Exit")) {
                break;
            }

            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w,
                     clear_color.y * clear_color.w,
                     clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    std::cout << "Main ImGUI loop ended" << std::endl;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

// /**
//  * @brief Closes client and server connections
//  * TODO: Close the appropriate connection instead of attempting to close both
//  */
// void closeConnections() {
//     std::cout << "Closing connections" << std::endl;
//     close(CLIENT);
//     close(SERVER_SOCK);
//     std::cout << "Connections closed" << std::endl;
// }

/**
 * @brief Runs the appropriate setup method for server or client depending on
 * option chosen in gui. Constantly checks the TRY_CONNECT bool until it's time
 * to attempt a setup
 */
void connect() {
    while (!IS_CONNECTED) {
        if (TRY_CONNECT) {
            std::cout << "Using port " << PORT << std::endl;

            // Start session 
            if (IS_SERVER) {
                // Create server object
                myServer = new Server(PORT);
            } else {
                // Create client object
                myClient = new Client(IP_ADDRESS, PORT);
            }

            IS_CONNECTED = true;
            return;
        }
    }
}

int main() {
   // Initialize chat history
    chatHistory history;

    // Start server-client session
    connect(); 

    runImgui(history);

    // closeConnections();

    return 0;
}