#include <Motion/HeadEncoderHandler.h>

HeadEncoderHandler::HeadEncoderHandler() : freq(0), direction(false), lastRefreshTime(millis())
{
    pinMode(HEAD_EN1, INPUT_PULLUP);
    pinMode(HEAD_EN2, INPUT_PULLUP);

    attachInterruptArg(HEAD_EN1, freqCounter, this, FALLING);
}

void HeadEncoderHandler::update()
{
    if (millis() - lastRefreshTime > ENCODER_SAMPLING_RATE)
    {
        displayFreq = ((double)freq / ENCODER_TICKS_PER_REV) * (1000 / (millis() - lastRefreshTime));
        freq = 0;
        lastRefreshTime = millis();

        direction = directionCounter >= 0 ? !ENCODER_INVERT_DIR : ENCODER_INVERT_DIR;
        directionCounter = 0;
    }
}

double HeadEncoderHandler::getFreq() const
{
    return displayFreq;
}

bool HeadEncoderHandler::getDir() const
{
    return direction;
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