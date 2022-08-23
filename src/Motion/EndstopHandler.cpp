#include <Motion/EndstopHandler.h>

EndstopHandler::EndstopHandler() {
    pinMode(X_MIN_PIN, INPUT_PULLUP);
}
