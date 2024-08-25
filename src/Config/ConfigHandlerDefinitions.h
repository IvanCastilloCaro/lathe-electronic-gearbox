#pragma once

#include <Arduino.h>

#define MAX_CONFIG_ENTRIES 6

template<typename T, typename U> constexpr size_t offsetOf(U T::*member)
{
    return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}

struct ConfigStruct {
    bool encoder_dir;
    float encoder_ticks_per_rev;
    uint32_t encoder_polling_ratio;
    bool stepper_dir;
    float stepper_steps_mm;
    uint32_t stepper_max_speed;
}; 

