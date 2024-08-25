 /**
 * Lathe Electronic Gearbox @ Ivan Castillo Caro @ 2022
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
#define X_STEP_PIN 13
#define X_INVERT_STEP_PIN true
#define X_DIR_PIN 9
#define X_INVERT_DIR_PIN true

//////////////////////////
// LCDs and Controllers //
//////////////////////////

// All deleted only for leaving Full Graphic Smart Controller Pins

#define LCD_PINS_ENABLE 17
#define LCD_PINS_RS 23
#define LCD_PINS_D4 18

#define BTN_EN1 16
#define BTN_EN2 4
#define BTN_ENC 5

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