/**
 * Lathe Electronic Gearbox @ Ivan Castillo Caro @ 2022
 * 
 * HeadEncoderHandler
 * 
 * This class is used to handle Head encoder
 */
#pragma once
#include <Arduino.h>

#include <Boards/Pins.h>

class HeadEncoderHandler {
    public:
        HeadEncoderHandler();

        void update(); //Must be executed in every cycle

        inline double getFreq() const { return displayFreq; } //Gets frequency in Hertz

        inline bool getDir() const { return direction; };
    private:
        volatile double displayFreq;
        volatile bool direction;
        long lastRefreshTime;

        const double k_invert_ticks_rev;
};