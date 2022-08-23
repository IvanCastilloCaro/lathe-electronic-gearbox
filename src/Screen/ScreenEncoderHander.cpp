#include <Screen/ScreenEncoderHandler.h>

#if (LCD_ENCODER_INVERT_DIR == true) 
    #define A_PIN BTN_EN1
    #define B_PIN BTN_EN2
#else
    #define A_PIN BTN_EN2
    #define B_PIN BTN_EN1
#endif

ScreenEncoderHandler* ScreenEncoderHandler::seh = nullptr;
// ESP32Encoder ScreenEncoderHandler::enc = ESP32Encoder();


ScreenEncoderHandler::ScreenEncoderHandler(ESP32Encoder* esp32enc) : enc(esp32enc) {

    //ESP32Encoder::useInternalWeakPullResistors=UP;

    bounce.attach(BTN_ENC, INPUT_PULLUP);
    bounce.interval(20);

    enc->attachHalfQuad(A_PIN,B_PIN);

    enc->setCount(0);
}

ScreenEncoderHandler* ScreenEncoderHandler::buildInstance(ESP32Encoder* esp32enc) {
        ScreenEncoderHandler::seh = new ScreenEncoderHandler(esp32enc);

    return ScreenEncoderHandler::seh;
}

ScreenEncoderHandler* ScreenEncoderHandler::getInstance() {
    return seh;
}


