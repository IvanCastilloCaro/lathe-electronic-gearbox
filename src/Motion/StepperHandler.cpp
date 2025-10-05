#include <Motion/StepperHandler.h>

StepperHandler::StepperHandler() {
    m_stepper = AccelStepper(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
    m_stepper.setPinsInverted(LEGConfig::getInstance()->getStepperDir(),true);

    m_stepper.setAcceleration(1000 * LEGConfig::getInstance()->getStepperSteps());
    // Set max speed in mm/s
    m_stepper.setMaxSpeed(LEGConfig::getInstance()->getStepperMaxSpeed() * LEGConfig::getInstance()->getStepperSteps());

    // Maybe we have to implement a mechanism to ensure not to run the motor to
    // certain speeds
}

void StepperHandler::stop() {
    if(!m_stepper.isRunning())
        return;

    m_stepper.stop();
}
