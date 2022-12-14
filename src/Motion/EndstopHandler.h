/**
 * Lathe Electronic Gearbox @ Ivan Castillo Caro @ 2022
 * 
 * HeadEncoderHandler
 * 
 * This class is used to handle EndStop
 */
#include <Arduino.h>

#include <Boards/esp_pins.h>

class EndstopHandler {
    public:
        EndstopHandler();

        inline bool getEndstopState() { return !digitalRead(X_MIN_PIN); }
};