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

        double getFreq() const; //Gets frequency in Hertz

        bool getDir() const;
    private:
        volatile uint16_t freq;
        double displayFreq;
        volatile int16_t directionCounter;
        bool direction;
        long lastRefreshTime;

        static void IRAM_ATTR freqCounter(void *p);
};