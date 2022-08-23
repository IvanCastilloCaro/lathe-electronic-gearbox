#include <Screen/ScreenHandler.h>

const uint8_t rows[5] = {12, 24, 36, 48, 60};

const uint8_t *ScreenHandler::ScreenTextArray[4] = {
    u8g2_font_profont10_tf,
    u8g2_font_profont12_tf,
    u8g2_font_profont15_tf,
    u8g2_font_profont29_tf};

const uint8_t ScreenHandler::TextSizes[4] = {5, 6, 7, 16}; // Stands for Small, Normal...

U8G2_ST7920_128X64_F_HW_SPI ext_m_u8g2(U8G2_R0, 5);

ScreenHandler *ScreenHandler::m_instance = nullptr;

ScreenHandler *ScreenHandler::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new ScreenHandler();
    }

    return m_instance;
}

ScreenHandler::ScreenHandler() : m_last_selected(0)
{
    m_u8g2 = &ext_m_u8g2;
}

void ScreenHandler::init()
{
    m_u8g2->setBusClock(600000);
    m_u8g2->begin();
    m_u8g2->setFont(u8g2_font_profont12_tf); // choose a suitable font
    m_u8g2->setFontMode(1);
}

void ScreenHandler::clearScreen()
{
    m_u8g2->clearDisplay();
}

// Only for testing purposes
void ScreenHandler::test()
{
    m_u8g2->clearBuffer();                  // clear the internal memory
    m_u8g2->drawStr(0, 10, "Hello World!"); // write something to the internal memory
    m_u8g2->sendBuffer();                   // transfer internal memory to the display
    delay(1000);
}

void ScreenHandler::drawText(const String &str, const int &x_pos, const int &y_pos, ScreenTextEnum font_type, bool commit)
{
    char c_str[21];
    str.getBytes((unsigned char *)c_str, 21);
    m_u8g2->setFont(ScreenTextArray[static_cast<size_t>(font_type)]);
    m_u8g2->drawStr(x_pos, y_pos, c_str);

    if (commit)
        m_u8g2->sendBuffer();
}

void ScreenHandler::drawMenuLine(const String &str, uint8_t row, ScreenMenuSymbols symbol)
{
    drawText(str, 4, rows[row]);
    m_u8g2->setFont(u8g2_font_unifont_t_symbols);
    m_u8g2->setFontMode(1);
    m_u8g2->drawGlyph(120, rows[row] + 2, static_cast<uint16_t>(symbol));
    m_u8g2->sendBuffer();
}

void ScreenHandler::drawMenuLineSelected(uint8_t row)
{

    // drawMenuLine(str,row,symbol);
    clearLine(m_last_selected);
    m_last_selected = row;

    m_u8g2->drawHLine(8, rows[row] - 10, 108);
    m_u8g2->drawHLine(8, rows[row] + 2, 108);
    m_u8g2->sendBuffer();
}

void ScreenHandler::clearLine(uint8_t selection)
{

    m_u8g2->setDrawColor(0);
    m_u8g2->drawHLine(8, rows[m_last_selected] - 10, 108);
    m_u8g2->drawHLine(8, rows[m_last_selected] + 2, 108);
    m_u8g2->sendBuffer();
    m_u8g2->setDrawColor(1);
}

U8G2_ST7920_128X64_F_HW_SPI *ScreenHandler::getU8g2Obj()
{
    return m_u8g2;
}

void ScreenHandler::drawHLine(const int &x, const int &y, const int &len, bool commit)
{
    m_u8g2->drawHLine(x, y, len);
    if (commit)
    {
        m_u8g2->sendBuffer();
    }
}

void ScreenHandler::clearPartOfScreen(const int &x, const int &y, const int &w, const int &h, bool commit)
{
    m_u8g2->setDrawColor(0);
    m_u8g2->drawBox(x, y, w, h);
    if (commit)
    {
        m_u8g2->sendBuffer();
    }
    m_u8g2->setDrawColor(1);
}

void ScreenHandler::clearMenuLine(const size_t &row, bool commit) {
    clearPartOfScreen(0, rows[row]-10, 128, 12, commit);
}

void ScreenHandler::drawBitmap(const unsigned char* bitmap, const int &w, const int &h, const int& x, const int& y, bool commit) {

    m_u8g2->setBitmapMode(false);
    m_u8g2->drawXBM(x,y,w,h,bitmap);
    if (commit) {
        m_u8g2->sendBuffer();
    }
}