#include "Boards/Boards.h"
#include "config.h"

#ifdef BOARD
    #if (BOARD == RAMPS)
        #include "Boards/ramps_pins.h"
    #elif (BOARD == ESP32)
        #include "Boards/esp_pins.h"
    #endif

#else  
    #error "No board defined"
#endif