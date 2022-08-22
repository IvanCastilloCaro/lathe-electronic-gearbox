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

    void setRunningMode(const RunningMode& mode);
    RunningMode getRunningMode() const;

    void setEngageStatus(const EngageStatus& eng);
    EngageStatus getEngageStatus() const;

    void setSettingEngageStatus (const EngageStatus& eng);
    EngageStatus getSettingEngageStatus() const;
    void invertEngageStatus();

    void setHeadDirectionStatus(const FeedDirectionMode& eng);
    FeedDirectionMode getHeadDirectionStatus() const;


    void setFeedDirectionMode(const FeedDirectionMode& eng);
    FeedDirectionMode getFeedDirectionMode() const;
    void invertFeedDirectionMode();

    void setThreadRelation(const ThreadRelation& eng);
    ThreadRelation getThreadRelation() const;

    void setActualRPM(const uint16_t& m_actual_rpm);
    uint16_t getActualRPM() const;

    void updateEndstop();
    void calculateEngageStatus();

private:
    MotionService();

    RunningMode m_running_mode;
    EngageStatus m_engage_status;
    EngageStatus m_setting_engage_status;
    EngageStatus m_endstop_engage_status;
    FeedDirectionMode m_head_direction_status;
    FeedDirectionMode m_feed_direction_mode;
    ThreadRelation m_actual_thread_relation;
    uint16_t m_actual_rpm;

    static MotionService* m_motion_service;

    // Motion Handlers

    EndstopHandler endstop;
    HeadEncoderHandler* enc;
    StepperHandler* stp;
};
