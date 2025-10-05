/**
 * Lathe Electronic Gearbox @ Ivan Castillo Caro @ 2022
 * 
 * Motion Service
 * 
 * Service used to manage all system's sensors and actuators 
 */
#pragma once

#include <Arduino.h>

#include <Motion/HeadEncoderHandler.h>
#include <Motion/StepperHandler.h>
#include <Motion/EndstopHandler.h>

#include <Boards/Pins.h>
#include <config.h>

enum RunningMode {
    PREDEFINED_MODE = 0,
    CUSTOM_MODE = 1
};

enum EngageStatus {
    ENGAGED = false,
    STOPPED = true
};

enum FeedDirectionMode {
    FORWARD = false,
    REVERSE = true
};

class MotionService {
public:
    static MotionService* getInstance();
    
    void update();

    inline void setRunningMode(const RunningMode& mode) { m_running_mode = mode; }
    inline RunningMode getRunningMode() const { return m_running_mode; }

    inline void setEngageStatus(const EngageStatus& eng) { m_engage_status = eng; }
    inline EngageStatus getEngageStatus() const { return m_engage_status; }
    
    inline void setSettingEngageStatus (const EngageStatus& eng) { m_setting_engage_status = eng; }
    inline EngageStatus getSettingEngageStatus() const { return m_setting_engage_status; }
    inline void invertEngageStatus() { m_setting_engage_status = m_setting_engage_status == EngageStatus::ENGAGED ? EngageStatus::STOPPED : EngageStatus::ENGAGED; }

    inline void setHeadDirectionStatus(const FeedDirectionMode& head) { m_head_direction_status = head; }
    inline FeedDirectionMode getHeadDirectionStatus() const { return m_head_direction_status; }


    inline void setFeedDirectionMode(const FeedDirectionMode& dir) { m_feed_direction_mode = dir; }
    inline FeedDirectionMode getFeedDirectionMode() const { return m_feed_direction_mode; }
    inline void invertFeedDirectionMode() { m_feed_direction_mode = m_feed_direction_mode == FeedDirectionMode::FORWARD ? FeedDirectionMode::REVERSE : FeedDirectionMode::FORWARD; }


    inline void setThreadRelation(const ThreadRelation& thread) { m_actual_thread_relation = thread; }
    inline ThreadRelation getThreadRelation() const { return m_actual_thread_relation; }

    inline void setActualRPM(const uint16_t& rpm) { m_actual_rpm = rpm; }
    inline uint16_t getActualRPM() const {return m_actual_rpm; }

    void updateEndstop();
    void calculateEngageStatus();

private:
    MotionService();

    volatile RunningMode m_running_mode;
    volatile EngageStatus m_engage_status;
    volatile EngageStatus m_setting_engage_status;
    volatile FeedDirectionMode m_head_direction_status;
    volatile FeedDirectionMode m_feed_direction_mode;
    ThreadRelation m_actual_thread_relation;
    volatile uint16_t m_actual_rpm;

    static MotionService* m_motion_service;

    // Motion Handlers

    EndstopHandler endstop;
    HeadEncoderHandler* enc;
    StepperHandler* stp;
};
