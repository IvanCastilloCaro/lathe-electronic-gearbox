/**
 * Lathe Electronic Gearbox @ Ivan Castillo Caro @ 2022
 * 
 * This class is used to make a Config abstraction from ESP32 EEPROM
 * 
 **/

#pragma once

#include <Config/ConfigHandlerDefinitions.h>

#include <Arduino.h>

class ConfigHandler {
    public: 
        /**
         * Returns true if the eeprom data is valid. Returns false otherwise.
        */
        bool init();
        void commitToEEPROM();
        void loadFromEEPROM();
        void invalidateEEPROM();

    protected:
        ConfigStruct m_config;
        virtual void readParametersFromConfiguration() = 0;
};
