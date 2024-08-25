#pragma once

#include <Config/ConfigHandler.h>

#include <config.h>

class LEGConfig : public ConfigHandler {
    public:
        static LEGConfig* getInstance();

        inline void setEncoderDir(bool enc) { m_config.encoder_dir = enc; }
        inline bool getEncoderDir() { return m_config.encoder_dir; }

        inline void setEncoderTicks(float ticks) { m_config.encoder_ticks_per_rev = ticks; }
        inline float getEncoderTicks() { return m_config.encoder_ticks_per_rev; }
        
        inline void setEncoderPolling(uint32_t enc) { m_config.encoder_polling_ratio = enc; }
        inline uint32_t getEncoderPolling() { return m_config.encoder_polling_ratio; }
        
        inline void setStepperDir(bool enc) { m_config.stepper_dir = enc; }
        inline bool getStepperDir() { return m_config.stepper_dir; }
        
        inline void setStepperSteps(float steps) { m_config.stepper_steps_mm = steps; }
        inline float getStepperSteps() { return m_config.stepper_steps_mm; }
        
        inline void setStepperMaxSpeed(uint32_t spd) { m_config.stepper_max_speed = spd; }
        inline uint32_t getStepperMaxSpeed() { return m_config.stepper_max_speed; }

    private:
        LEGConfig();
        static LEGConfig* m_legconfig; 

        void readParametersFromConfiguration() {
            m_config.encoder_dir = ENCODER_INVERT_DIR;
            m_config.encoder_polling_ratio = ENCODER_SAMPLING_RATE;
            m_config.encoder_ticks_per_rev = ENCODER_TICKS_PER_REV;

            m_config.stepper_dir = X_INVERT_DIR;
            m_config.stepper_max_speed = X_MAX_SPEED;
            m_config.stepper_steps_mm = X_STEPS_PER_MM;

        }
};