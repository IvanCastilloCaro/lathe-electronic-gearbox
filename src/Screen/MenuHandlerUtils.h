/**
 * Lathe Electronic Gearbox @ Ivan Castillo Caro @ 2022
 *
 * This class is used to define auxiliary functions for Menu's
 *
 **/
#include <Arduino.h>

#include <Screen/ScreenHandler.h>

#pragma once

uint8_t calculateTextCenter(const String& str, ScreenTextEnum size);

uint8_t calculateTextCenter(const String& str1, const String& str2, ScreenTextEnum size1, ScreenTextEnum size2);

uint8_t calculateSecondStringOffset(const String& str1, const String& str2, ScreenTextEnum size1, ScreenTextEnum size2);

String formatRPMString(const uint16_t& rpm);

String getLineChecked(const String& str, const bool& value);