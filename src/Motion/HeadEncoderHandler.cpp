#include <Motion/HeadEncoderHandler.h>

#include <Config/LEGConfig.h>

HeadEncoderHandler::HeadEncoderHandler() : k_invert_ticks_rev(1.0/LEGConfig::getInstance()->getEncoderTicks()), freq(0), direction(false), lastRefreshTime(millis())
{
    pinMode(HEAD_EN1, INPUT_PULLUP);
    pinMode(HEAD_EN2, INPUT_PULLUP);

    attachInterruptArg(HEAD_EN1, freqCounter, this, FALLING);
}

void HeadEncoderHandler::update()
{
    if (millis() - lastRefreshTime < LEGConfig::getInstance()->getEncoderPolling())
        return;

    displayFreq = ((double)freq * k_invert_ticks_rev) * (1000.0 / (millis() - lastRefreshTime));
    freq = 0;
    lastRefreshTime = millis();

    direction = directionCounter >= 0 ? !LEGConfig::getInstance()->getEncoderDir() : LEGConfig::getInstance()->getEncoderDir();
    directionCounter = 0;
}

void IRAM_ATTR HeadEncoderHandler::freqCounter(void *p)
{
    ((HeadEncoderHandler *)p)->freq++;

    if (digitalRead(HEAD_EN2))
    {
        ((HeadEncoderHandler *)p)->directionCounter++;
    }
    else
    {
        ((HeadEncoderHandler *)p)->directionCounter--;
    }
};