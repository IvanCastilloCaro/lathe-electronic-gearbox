 /**
 * Lathe Electronic Gearbox @ Ivan Castillo Caro @ 2022
 *
 * This program is inspired in Marlin in order to have a small HAL.
 *
 * All the symbology follows Marlin's convention. Otherwise, it will be indicated here.
 *
 * Custom pins: HEAD_EN1, HEAD_EN2
 *
 * This is useful to port the project between different boards
 */
#pragma once

//
// Limit Switches
//

// Maybe is a good idea to have a limit switch in order to not to crash the carriage with the chuck (TO-DO)
#define X_MIN_PIN 34


//
// Steppers
//

// X Motor used as longitudinal feed
#define X_STEP_PIN 0
#define X_DIR_PIN 2

//////////////////////////
// LCDs and Controllers //
//////////////////////////

// All deleted only for leaving Full Graphic Smart Controller Pins

#define LCD_PINS_ENABLE 5
#define LCD_PINS_RS 23
#define LCD_PINS_D4 18

#define BTN_EN1 17
#define BTN_EN2 16
#define BTN_ENC 4

#ifndef KILL_PIN
#define KILL_PIN 0
#endif

#ifndef BEEPER
#define BEEPER 0
#endif

/////////////////////////
//    Head Encoder     //
/////////////////////////

#define HEAD_EN1 22
#define HEAD_EN2 21