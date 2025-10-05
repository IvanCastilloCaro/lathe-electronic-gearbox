#include "driver/pcnt.h"

#include <Motion/HeadEncoderHandler.h>

#include <Config/LEGConfig.h>

HeadEncoderHandler::HeadEncoderHandler() : k_invert_ticks_rev(1.0 / (LEGConfig::getInstance()->getEncoderTicks() * 4)), direction(false), lastRefreshTime(millis())
{
    // pinMode(HEAD_EN1, INPUT_PULLUP);
    // pinMode(HEAD_EN2, INPUT_PULLUP);

    pcnt_config_t pcnt_config; 

    pcnt_config.pulse_gpio_num = HEAD_EN1;
    pcnt_config.ctrl_gpio_num = HEAD_EN2;
    pcnt_config.channel = PCNT_CHANNEL_0;
    pcnt_config.unit = PCNT_UNIT_0;
    pcnt_config.pos_mode = PCNT_COUNT_INC;
    pcnt_config.neg_mode = PCNT_COUNT_DEC;
    pcnt_config.lctrl_mode = PCNT_MODE_REVERSE;
    pcnt_config.hctrl_mode = PCNT_MODE_KEEP;
    pcnt_config.counter_h_lim = INT16_MAX;
    pcnt_config.counter_l_lim = INT16_MIN; 
    

    pcnt_unit_config(&pcnt_config);

    // Optional: set a filter to avoid mis-count due to hardware bounce (1us)
    pcnt_set_filter_value(PCNT_UNIT_0, 1000);
    pcnt_filter_enable(PCNT_UNIT_0);

    // Start counter
    pcnt_counter_pause(PCNT_UNIT_0);
    pcnt_counter_clear(PCNT_UNIT_0);
    pcnt_counter_resume(PCNT_UNIT_0);

    lastRefreshTime = millis();
}

void HeadEncoderHandler::update()
{
    uint32_t elapsedTime = millis() - lastRefreshTime;
    if (elapsedTime < LEGConfig::getInstance()->getEncoderPolling())
        return;

    int16_t count = 0;
    pcnt_get_counter_value(PCNT_UNIT_0, &count);
    pcnt_counter_clear(PCNT_UNIT_0);
    displayFreq = abs((double)count * k_invert_ticks_rev) * (1000.0 / (elapsedTime));
    lastRefreshTime = millis();

    direction = count >= 0 ? !LEGConfig::getInstance()->getEncoderDir() : LEGConfig::getInstance()->getEncoderDir();
}
