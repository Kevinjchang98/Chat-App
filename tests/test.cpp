#define CATCH_CONFIG_MAIN

#include <string>

#include "catch.hpp"

#define private public
#include "ChatHistory.h"
#include "ChatMessage.h"
#include "NetworkHelper.h"
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

// NetworkHelper
TEST_CASE("Valid IP and port returns true") {
    REQUIRE(NetworkHelper::connectionDataIsValid("127.0.0.1", 5000) == true);
}

TEST_CASE("Too short IP returns false") {
    REQUIRE(NetworkHelper::connectionDataIsValid("192.0.0", 5000) == false);
}

TEST_CASE("Too long IP returns false") {
    REQUIRE(NetworkHelper::connectionDataIsValid("192.0.0.0.0", 5000) == false);
}

TEST_CASE("Negative number in IP returns false") {
    REQUIRE(NetworkHelper::connectionDataIsValid("-192.0.0.0", 5000) == false);
    REQUIRE(NetworkHelper::connectionDataIsValid("192.-0.0.0", 5000) == false);
    REQUIRE(NetworkHelper::connectionDataIsValid("192.0.-100.0", 5000) ==
            false);
    REQUIRE(NetworkHelper::connectionDataIsValid("192.0.0.-5", 5000) == false);
}

TEST_CASE("Too high value in IP returns false") {
    REQUIRE(NetworkHelper::connectionDataIsValid("256.0.0.0", 5000) == false);
    REQUIRE(NetworkHelper::connectionDataIsValid("0.256.0.0", 5000) == false);
    REQUIRE(NetworkHelper::connectionDataIsValid("0.0.256.0", 5000) == false);
    REQUIRE(NetworkHelper::connectionDataIsValid("0.0.0.256", 5000) == false);
}

TEST_CASE("Negative port value returns false") {
    REQUIRE(NetworkHelper::connectionDataIsValid("127.0.0.1", -1) == false);
}

TEST_CASE("Too high port value returns false") {
    REQUIRE(NetworkHelper::connectionDataIsValid("127.0.0.1", 65537) == false);
}

TEST_CASE("Minimum port value returns true") {
    REQUIRE(NetworkHelper::connectionDataIsValid("127.0.0.1", 0) == true);
}

TEST_CASE("Maximum port value returns true") {
    REQUIRE(NetworkHelper::connectionDataIsValid("127.0.0.1", 65536) == true);
}
