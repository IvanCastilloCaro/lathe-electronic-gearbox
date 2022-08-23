#include <Arduino.h>

#include <Screen/ScreenHandler.h>
#include <Screen/ScreenEncoderHandler.h>
#include <Motion/MotionService.h>

#include <ESP32Encoder.h>

#include <Screen/MenuHandler.h>

ScreenEncoderHandler* enc;
MenuHandler* menu;
MotionService* mot;


void setup() {

  mot = MotionService::getInstance();
  ScreenHandler::getInstance()->init();
  enc = ScreenEncoderHandler::buildInstance(new ESP32Encoder());
  menu = new MenuHandler();

  enc->setCount(0);

  menu->enterAboutMenu();

  delay(2500);

  menu->enterInfoScreen();
}

void loop() {
  mot->update();
  enc->update();
  menu->update();
}