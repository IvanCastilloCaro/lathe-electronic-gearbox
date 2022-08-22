/**
 * Lathe Electronic Gearbox @ Ivan Castillo Caro @ 2022
 *
 * This class is used to handle Screen and menus
 *
 **/
#pragma once

#include <Arduino.h>
#include <Boards/Pins.h>
#include <U8g2lib.h>


// Enum for selecting symbols
enum ScreenMenuSymbols
{
    NO_SYMBOLS = 0,
    BACK_ARROW = 8617,
    RIGHT_ARROW = 0x2192
};

enum ScreenTextEnum
{
    TEXT_SMALL = 0,
    TEXT_NORMAL = 1,
    TEXT_LARGE = 2,
    TEXT_EXTRALARGE = 3
};

#define NO_COMMIT false
#define COMMIT true


class ScreenHandler
{
public:
    static ScreenHandler *getInstance();

    void init();
    void test();
    void clearScreen();
    void clearPartOfScreen(const int& x1, const int& y1, const int& width, const int& height, bool commit = true);
    U8G2_ST7920_128X64_F_HW_SPI *getU8g2Obj();
    void drawText(const String &a, const int &x_pos, const int &y_pos, ScreenTextEnum font_type = ScreenTextEnum::TEXT_NORMAL , bool commit = true);
    void drawHLine(const int &x, const int &y, const int &len, bool commit = true);
    void drawMenuLine(const String &text, uint8_t row, ScreenMenuSymbols menu_symbols = ScreenMenuSymbols::NO_SYMBOLS);
    void drawMenuLineSelected(uint8_t row);
    void clearMenuLine(const size_t &row, bool commit = true);
    void drawBitmap(const unsigned char* bitmap, const int &w, const int &h, const int &x, const int &y, bool commit = true);

    static const uint8_t* ScreenTextArray[4];

    static const uint8_t TextSizes[4];

private:
    ScreenHandler();

    void clearLine(uint8_t selection);

    uint8_t m_last_selected;

    U8G2_ST7920_128X64_F_HW_SPI *m_u8g2;
    static ScreenHandler *m_instance;
};