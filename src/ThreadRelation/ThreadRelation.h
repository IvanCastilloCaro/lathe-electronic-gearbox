#include <Arduino.h>
/**
 * Lathe Electronic Gearbox @ Ivan Castillo Caro @ 2022
 * 
 * Definition of class that represents a gear relation between the headstock
 * and the longitudinal axis.
 * 
 * The name is used to show it in display.
 * 
 * The value field is shown in mm's per revolution.
 *
 **/


#pragma once

class ThreadRelation {
    public:
        String m_name;
        float m_value;

    String getDisplayValue() const {
        return String(m_name + ":" + String(m_value, 2)); 
    }

    ThreadRelation(String name, float value);
};
