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
                                 m_endstop_engage_status(EngageStatus::ENGAGED),
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
    
    updateEndstop();
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

void MotionService::setRunningMode(const RunningMode &mode)
{
    m_running_mode = mode;
}
RunningMode MotionService::getRunningMode() const
{
    return m_running_mode;
}

void MotionService::setEngageStatus(const EngageStatus &eng)
{
    m_engage_status = eng;
}

EngageStatus MotionService::getEngageStatus() const
{
    return m_engage_status;
}

void MotionService::setSettingEngageStatus(const EngageStatus &eng)
{
    m_setting_engage_status = eng;
}

EngageStatus MotionService::getSettingEngageStatus() const
{
    return m_setting_engage_status;
}

void MotionService::setHeadDirectionStatus(const FeedDirectionMode &head)
{
    m_head_direction_status = head;
}

FeedDirectionMode MotionService::getHeadDirectionStatus() const
{
    return m_head_direction_status;
}

void MotionService::setFeedDirectionMode(const FeedDirectionMode &dir)
{
    m_feed_direction_mode = dir;
}
FeedDirectionMode MotionService::getFeedDirectionMode() const
{
    return m_feed_direction_mode;
}

void MotionService::setThreadRelation(const ThreadRelation &thread)
{
    m_actual_thread_relation = thread;
}

ThreadRelation MotionService::getThreadRelation() const
{
    return m_actual_thread_relation;
}

void MotionService::setActualRPM(const uint16_t &rpm)
{
    m_actual_rpm = rpm;
}
uint16_t MotionService::getActualRPM() const
{
    return m_actual_rpm;
}

void MotionService::updateEndstop()
{
    if (endstop.getEndstopState()) {
        m_endstop_engage_status = EngageStatus::STOPPED;
    }
    else {
        m_endstop_engage_status = EngageStatus::ENGAGED;
    }
}

void MotionService::calculateEngageStatus()
{
    if (m_endstop_engage_status == EngageStatus::STOPPED)
    {
        m_engage_status = EngageStatus::STOPPED;
    }
    else
    {
        m_engage_status = m_setting_engage_status;
    }
}

void MotionService::invertFeedDirectionMode()
{
    m_feed_direction_mode = m_feed_direction_mode == FeedDirectionMode::FORWARD ? FeedDirectionMode::REVERSE : FeedDirectionMode::FORWARD;
}

void MotionService::invertEngageStatus()
{
    m_setting_engage_status = m_setting_engage_status == EngageStatus::ENGAGED ? EngageStatus::STOPPED : EngageStatus::ENGAGED; 
}
