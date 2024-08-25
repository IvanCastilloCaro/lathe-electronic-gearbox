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

#include <Config/LEGConfig.h>

class StepperHandler {
    public:
        StepperHandler();

        inline void updateSpeed(float newSpeed) { m_stepper.setSpeed(newSpeed * LEGConfig::getInstance()->getStepperSteps()); }

        inline void run() { m_stepper.runSpeed(); }
        
        void stop();

        inline void setMotorDirection(bool dir) { m_stepper.setPinsInverted(dir); }
    private:
        AccelStepper m_stepper;


};
