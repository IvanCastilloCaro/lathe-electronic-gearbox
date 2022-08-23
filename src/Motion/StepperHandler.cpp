#include <Motion/StepperHandler.h>

StepperHandler::StepperHandler() {
    m_stepper = AccelStepper(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);

    m_stepper.setAcceleration(3000);
    m_stepper.setMaxSpeed(20000);

    // Maybe we have to implement a mechanism to ensure not to run the motor to
    // certain speeds
}

void StepperHandler::stop() {
    if(!m_stepper.isRunning())
        return;

    m_stepper.stop();
}
