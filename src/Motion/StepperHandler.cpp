#include <Motion/StepperHandler.h>

StepperHandler::StepperHandler() {
    m_stepper = AccelStepper(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);

    m_stepper.setAcceleration(3000);
    m_stepper.setMaxSpeed(20000);

    // Maybe we have to implement a mechanism to ensure not to run the motor to
    // certain speeds
}

void StepperHandler::updateSpeed(float newSpeed) {
    // The speed is given in RPS, so we have to pass to steps
    // per second.
    m_stepper.setSpeed(newSpeed * X_STEPS_PER_MM);
}

void StepperHandler::run() {

    m_stepper.runSpeed();
}

void StepperHandler::stop() {
    if(!m_stepper.isRunning())
        return;

    m_stepper.stop();
}

void StepperHandler::setMotorDirection(bool dir) {
    m_stepper.setPinsInverted(dir);
}