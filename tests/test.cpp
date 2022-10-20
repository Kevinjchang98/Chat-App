#define CATCH_CONFIG_MAIN

#include <string>

#include "catch.hpp"

#define private public
#include "ChatMessage.cpp"
#include "ChatMessage.h"
#include "Gui.cpp"
#include "Gui.h"
#undef private

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