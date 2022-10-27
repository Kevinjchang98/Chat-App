#define CATCH_CONFIG_MAIN

#include <string>

#include "catch.hpp"

#define private public
#include "ChatMessage.h"
#include "ChatHistory.h"
#undef private

// ChatMessage
TEST_CASE("Empty message") {
    ChatMessage test = ChatMessage();

    REQUIRE(test.getMessage() == "");
    REQUIRE(test.getSender() == "Unknown");
    REQUIRE(test.getTimestamp() == "");
}

TEST_CASE("Empty constructor") {
    ChatMessage test = ChatMessage();

    test.setMessage("test message");
    test.setSender("test sender");
    test.setTime();

    REQUIRE(test.getMessage() == "test message");
    REQUIRE(test.getSender() == "test sender");
    REQUIRE(test.getTimestamp() != "");
}

TEST_CASE("Two string constructor") {
    ChatMessage test = ChatMessage("message", "sender");
    test.setTime();

    REQUIRE(test.getMessage() == "message");
    REQUIRE(test.getSender() == "sender");
    REQUIRE(test.getTimestamp() != "");
}

TEST_CASE("Single string set message") {
    ChatMessage test = ChatMessage();

    test.setMessage("test message");
    test.setSender("test sender");
    test.setTime();

    REQUIRE(test.getMessage() == "test message");
    REQUIRE(test.getSender() == "test sender");
    REQUIRE(test.getTimestamp() != "");
}

TEST_CASE("Double string set message") {
    ChatMessage test = ChatMessage();

    test.setMessage("test message", "test sender");
    test.setTime();

    REQUIRE(test.getMessage() == "test message");
    REQUIRE(test.getSender() == "test sender");
    REQUIRE(test.getTimestamp() != "");
}

TEST_CASE("Set time") {
    ChatMessage test = ChatMessage();

    REQUIRE(test.getTimestamp() == "");

    test.setTime();

    REQUIRE(test.getTimestamp() != "");
}

// ChatHistory
TEST_CASE("Add message with content saves in history") {
    ChatHistory test = ChatHistory();

    REQUIRE(test.histVec.size() == 0);

    test.addMessage("Test message", "Test sender");

    REQUIRE(test.histVec.size() == 1);
}

TEST_CASE("Add empty message doesn't save in history") {
    ChatHistory test = ChatHistory();

    REQUIRE(test.histVec.size() == 0);

    test.addMessage("", "Test sender");

    REQUIRE(test.histVec.size() == 0);
}

TEST_CASE("Add message with empty sender saves in history") {
    ChatHistory test = ChatHistory();

    REQUIRE(test.histVec.size() == 0);

    test.addMessage("Test message", "");

    REQUIRE(test.histVec.size() == 1);
}

TEST_CASE("Has new message returns true then false") {
    ChatHistory test = ChatHistory();
    
    test.addMessage("Test", "Test");

    REQUIRE(test.hasNewMessage() == true);
    REQUIRE(test.hasNewMessage() == false);
}

TEST_CASE("Has new message returns false with empty history") {
    ChatHistory test = ChatHistory();

    REQUIRE(test.hasNewMessage() == false);
}
