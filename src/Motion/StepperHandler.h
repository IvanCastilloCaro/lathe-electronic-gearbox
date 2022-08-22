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

#include <AccelStepper.h>

class StepperHandler {
    public:
        StepperHandler();

        void updateSpeed(float newSpeed);

        void run();
        
        void stop();

        void setMotorDirection(bool dir);
    private:
        AccelStepper m_stepper;


};
