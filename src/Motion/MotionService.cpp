#include <Motion/MotionService.h>

MotionService *MotionService::m_motion_service = nullptr;

MotionService *MotionService::getInstance()
{
    if (m_motion_service == nullptr)
    {
        m_motion_service = new MotionService();
    }
    return m_motion_service;
}

MotionService::MotionService() : m_running_mode(RunningMode::PREDEFINED_MODE),
                                 m_engage_status(EngageStatus::ENGAGED),
                                 m_setting_engage_status(EngageStatus::ENGAGED),
                                 m_feed_direction_mode(FeedDirectionMode::FORWARD),
                                 m_head_direction_status(FeedDirectionMode::FORWARD),
                                 m_actual_thread_relation(PredefinedRelationSettings[0]),
                                 m_actual_rpm(0)
{
    enc = new HeadEncoderHandler();
    stp = new StepperHandler();
}

void MotionService::update()
{
    // First, update all handlers, if neccesary
    enc->update();

    // Get all data
    setActualRPM(enc->getFreq() * 60);
    stp->updateSpeed(enc->getFreq() * m_actual_thread_relation.m_value);
    setHeadDirectionStatus(enc->getDir() ? FeedDirectionMode::FORWARD : FeedDirectionMode::REVERSE);
    stp->setMotorDirection(!enc->getDir());
    
    calculateEngageStatus();

    // Actuate over all system actuators
    if (m_engage_status == EngageStatus::ENGAGED)
    {
        stp->run();
    }
    else
    {
        stp->stop();
    }
}

void MotionService::calculateEngageStatus()
{
    if (endstop.getEndstopState())
    {
        m_engage_status = EngageStatus::STOPPED;
    }
    else
    {
        m_engage_status = m_setting_engage_status;
    }
}
