#include <Motion/EndstopHandler.h>

EndstopHandler::EndstopHandler() {
    pinMode(X_MIN_PIN, INPUT_PULLUP);
}

bool EndstopHandler::getEndstopState() {
    return !digitalRead(X_MIN_PIN);
}