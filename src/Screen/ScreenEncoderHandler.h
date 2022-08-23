/**
 * Lathe Electronic Gearbox @ Ivan Castillo Caro @ 2022
 * 
 * This class is used to handle Encoder and buttons
 * 
 * Wraps the EncoderButton library in order to make it
 * unique in the project
 * 
 **/

#include <Arduino.h>

#include <Boards/Pins.h>

#include <ESP32Encoder.h>
#include <Bounce2.h>

#pragma once

//Singleton class

class ScreenEncoderHandler {

    public:
        static ScreenEncoderHandler* buildInstance(ESP32Encoder* esp32enc);

        static ScreenEncoderHandler* getInstance();

        inline int getCount() { return enc->getCount(); }

        inline void setCount(int value) { enc->setCount(value); }

        inline void update() { bounce.update(); }

        inline bool buttonState() { return bounce.changed() && bounce.read(); }

    private:
        Bounce bounce;
        ESP32Encoder* enc;
        static ScreenEncoderHandler* seh;
        ScreenEncoderHandler(ESP32Encoder* esp32enc);
};
