#include "hw/TILink.hpp"

TILink::TILink(uint32_t baudRate) : _baudRate(baudRate) {}

void TILink::begin() {
    Serial.begin(_baudRate);
}

bool TILink::hasData() {
    return Serial.available() > 0;
}

String TILink::readMessage() {
    String msg = Serial.readStringUntil('\n');
    msg.trim();
    return msg;
}

void TILink::writeMessage(const String& msg) {
    Serial.println(msg);
}
