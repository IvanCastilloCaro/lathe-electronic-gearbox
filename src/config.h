/**
 * Lathe Electronic Gearbox @ Ivan Castillo Caro @ 2022
 * 
 * Configuration File
 * 
 * Custom parameters and functionality will be stored here
 */

#pragma once
#include <Arduino.h>
#include <ThreadRelation/ThreadRelation.h>

#define VERSION "V1.0.0-prerelease"

///////////////
//   Board   //
///////////////
#define BOARD ESP32

///////////////////////////
// Stepper Configuration //
///////////////////////////

#ifndef X_STEPS_PER_MM
    #define X_STEPS_PER_MM 1600  // Has to be adjusted depending on your mechanical configuration.
    #define X_INVERT_DIR true
    #define X_MAX_SPEED 1000 // mm/s. TO-DO: dont make a movement if motor cant reach it.
#endif

///////////////////////
// LCD Configuration //
///////////////////////

#define LCD_ENCODER_INVERT_DIR true // If the encoder turns in the reverse direction, change this.

///////////////////////////
// Encoder Configuration //
///////////////////////////

#define ENCODER_SAMPLING_RATE 3 // ms
#define ENCODER_TICKS_PER_REV 600 // pulses per rev
#define ENCODER_INVERT_DIR false

///////////////////////
//  Custom Settings  //
///////////////////////

// Here you can define custom Thread Relations for your applications.
// Make sure to match CUSTOM_SETTINGS_SIZE with the real length of array.

#define PREDEFINED_THREADS_SIZE 27

const ThreadRelation PredefinedRelationSettings[PREDEFINED_THREADS_SIZE] = {
    ThreadRelation("Coarse", 0.1),
    ThreadRelation("Medium", 0.05),
    ThreadRelation("Fine", 0.01),
    ThreadRelation("M2", 0.4),
    ThreadRelation("M2.5", 0.45),
    ThreadRelation("M3", 0.5),
    ThreadRelation("M4", 0.7),
    ThreadRelation("M5", 0.8),
    ThreadRelation("M6", 1),
    ThreadRelation("M7", 1),
    ThreadRelation("M8", 1.25),
    ThreadRelation("M9", 1.25),
    ThreadRelation("M10", 1.5),
    ThreadRelation("M12", 1.5),
    ThreadRelation("M14", 2),
    ThreadRelation("M16", 2),
    ThreadRelation("M18", 2.5),
    ThreadRelation("M20", 2.5),
    ThreadRelation("W1/4\"", 1.270),
    ThreadRelation("W5/16\"", 1.411),
    ThreadRelation("W3/8\"", 1.588),
    ThreadRelation("W7/16\"", 1.814),
    ThreadRelation("W1/2\"", 2.117),
    ThreadRelation("W5/8\"", 2.309),
    ThreadRelation("W3/4\"", 2.540),
    ThreadRelation("W7/8\"", 2.822),
    ThreadRelation("W1\"", 3.175)
    };


