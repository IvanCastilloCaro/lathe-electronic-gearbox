#include <Screen/MenuHandlerUtils.h>

uint8_t calculateTextCenter(const String& str, ScreenTextEnum size) {
    return (128-str.length() * ScreenHandler::TextSizes[static_cast<size_t>(size)])/2;
}

uint8_t calculateTextCenter(const String& str1, const String& str2, ScreenTextEnum size1, ScreenTextEnum size2) {
    return (128-(str1.length() * ScreenHandler::TextSizes[static_cast<size_t>(size1)]+
                str2.length() * ScreenHandler::TextSizes[static_cast<size_t>(size2)]))/2;
}

uint8_t calculateSecondStringOffset(const String& str1, const String& str2, ScreenTextEnum size1, ScreenTextEnum size2) {
    return calculateTextCenter(str1, str2, size1, size2) + str1.length() * ScreenHandler::TextSizes[static_cast<size_t>(size1)];
}

String formatRPMString(const uint16_t& rpm) {
    if (rpm < 10) {
        return "000" + String(rpm);
    }
    if (rpm < 100) {
        return "00" + String(rpm);
    }
    if (rpm < 1000) {
        return "0" + String(rpm);
    }
    return String(rpm); // Default case
}

String getLineChecked(const String& str, const bool& checked) {
    if (checked)
        return str + "  [X]";

    return str + "  [ ]";
}