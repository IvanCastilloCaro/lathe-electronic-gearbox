#include <Config/ConfigHandler.h>

#include <EEPROM.h>

bool ConfigHandler::init() {
    EEPROM.begin(sizeof(ConfigStruct) + 1);
    char checksum = EEPROM.readChar(0);
    if (checksum != 82) {
        readParametersFromConfiguration();
        EEPROM.writeChar(0, 82);
        commitToEEPROM();
        return false;
    }
    loadFromEEPROM();
    return true;
}

void ConfigHandler::commitToEEPROM() {
    EEPROM.put(1,m_config); 
    EEPROM.commit();
}
void ConfigHandler::loadFromEEPROM() {
    m_config = EEPROM.get(1, m_config);
}

void ConfigHandler::invalidateEEPROM() {
    EEPROM.writeChar(0,0);
    EEPROM.commit();
}