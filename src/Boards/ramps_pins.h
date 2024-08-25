/**
 * Lathe Electronic Gearbox @ Ivan Castillo Caro @ 2022

 */
#pragma once

//
// Limit Switches
//

// Maybe is a good idea to have a limit switch in order to not to crash the carriage with the chuck (TO-DO)
#ifndef X_STOP_PIN
  #ifndef X_MIN_PIN
    #define X_MIN_PIN                          3
  #endif
  #ifndef X_MAX_PIN
    #define X_MAX_PIN                          2
  #endif
#endif

//
// Steppers
//

// X Motor used as longitudinal feed 
#define X_STEP_PIN                            54
#define X_DIR_PIN                             55
#define X_ENABLE_PIN                          38
#ifndef X_CS_PIN
  #define X_CS_PIN                            53
#endif

// Unused Y, Z and E, so we delete it

// We are not going to use MOSFET's, Thermocouples and so on, so we delete too

// Misc pins that we will use for our project
//
// AUX1    5V  GND D2  D1
//          2   4   6   8
//          1   3   5   7
//         5V  GND A3  A4
//
#define AUX1_05_PIN                           57  // (A3)
#define AUX1_06_PIN                            2
#define AUX1_07_PIN                           58  // (A4)
#define AUX1_08_PIN                            1

//
// AUX2    GND A9 D40 D42 A11
//          2   4   6   8  10
//          1   3   5   7   9
//         VCC A5 A10 D44 A12
//
#define AUX2_03_PIN                           59  // (A5)
#define AUX2_04_PIN                           63  // (A9)
#define AUX2_05_PIN                           64  // (A10)
#define AUX2_06_PIN                           40
#define AUX2_07_PIN                           44
#define AUX2_08_PIN                           42
#define AUX2_09_PIN                           66  // (A12)
#define AUX2_10_PIN                           65  // (A11)

// Necessary for handling the LCD

// AUX3    GND D52 D50 5V
//          7   5   3   1
//          8   6   4   2
//         NC  D53 D51 D49
//
#define AUX3_02_PIN                           49
#define AUX3_03_PIN                           50
#define AUX3_04_PIN                           51
#define AUX3_05_PIN                           52
#define AUX3_06_PIN                           53

//
// AUX4    5V GND D32 D47 D45 D43 D41 D39 D37 D35 D33 D31 D29 D27 D25 D23 D17 D16
//
#define AUX4_03_PIN                           32
#define AUX4_04_PIN                           47
#define AUX4_05_PIN                           45
#define AUX4_06_PIN                           43
#define AUX4_07_PIN                           41
#define AUX4_08_PIN                           39
#define AUX4_09_PIN                           37
#define AUX4_10_PIN                           35
#define AUX4_11_PIN                           33
#define AUX4_12_PIN                           31
#define AUX4_13_PIN                           29
#define AUX4_14_PIN                           27
#define AUX4_15_PIN                           25
#define AUX4_16_PIN                           23
#define AUX4_17_PIN                           17
#define AUX4_18_PIN                           16

/**
 * LCD adapters come in different variants. The socket keys can be
 * on either side, and may be backwards on some boards / displays.
 */
#ifndef EXP1_08_PIN

    #define EXP1_01_PIN                 AUX4_10_PIN
    #define EXP1_02_PIN                 AUX4_09_PIN
    #define EXP1_03_PIN                 AUX4_17_PIN
    #define EXP1_04_PIN                 AUX4_18_PIN
    #define EXP1_05_PIN                 AUX4_16_PIN
    #define EXP1_06_PIN                 AUX4_15_PIN
    #define EXP1_07_PIN                 AUX4_14_PIN
    #define EXP1_08_PIN                 AUX4_13_PIN

    //EXP2_01 and EXP2_02 is reserved for SDCard
    #define EXP2_03_PIN                 AUX4_12_PIN
    #define EXP2_04_PIN                 AUX3_06_PIN
    #define EXP2_05_PIN                 AUX4_11_PIN
    #define EXP2_06_PIN                 AUX3_04_PIN
    #define EXP2_07_PIN                 AUX3_02_PIN
    #define EXP2_08_PIN                 AUX4_07_PIN

#endif

//////////////////////////
// LCDs and Controllers //
//////////////////////////

//All deleted only for leaving Full Graphic Smart Controller Pins

    #define LCD_PINS_ENABLE             EXP1_03_PIN
    #define LCD_PINS_RS                 EXP1_04_PIN
    #define LCD_PINS_D4                 EXP1_05_PIN
    #define LCD_PINS_D5                 EXP1_06_PIN
    #define LCD_PINS_D6                 EXP1_07_PIN
    #define LCD_PINS_D7                 EXP1_08_PIN
    
    #define BTN_EN1                     EXP2_05_PIN
    #define BTN_EN2                     EXP2_03_PIN
    #define BTN_ENC                     EXP1_01_PIN

    #ifndef KILL_PIN
        #define KILL_PIN                EXP2_08_PIN
    #endif

    #ifndef BEEPER
        #define BEEPER                  EXP1_02_PIN
    #endif

    