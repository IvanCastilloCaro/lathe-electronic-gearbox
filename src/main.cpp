#include <Arduino.h>

#include <Screen/ScreenHandler.h>
#include <Screen/ScreenEncoderHandler.h>
#include <Motion/MotionService.h>

#include <ESP32Encoder.h>

#include <Screen/MenuHandler.h>

#include <Config/LEGConfig.h>

ScreenEncoderHandler* enc;
MenuHandler* menu;
MotionService* mot;

TaskHandle_t Task1;
TaskHandle_t Task2;

void motorTask(void * pvParameters) {
  for(;;) {
    mot->update();
  } 
}

void UITask(void * pvParameters) {
  for(;;) {
    enc->update();
    menu->update();
    delay(1);
  }
}

void setup() {
  bool init = LEGConfig::getInstance()->init();
  mot = MotionService::getInstance();
  ScreenHandler::getInstance()->init();
  enc = ScreenEncoderHandler::buildInstance(new ESP32Encoder());
  menu = new MenuHandler();

  enc->setCount(0);

  menu->enterAboutMenu();

  delay(2000);

  menu->drawEEPROMWindow(init);

  delay(2000);

  menu->enterInfoScreen();

  disableCore0WDT();

  xTaskCreatePinnedToCore(motorTask, "motorTask", 10000, NULL, 1, &Task1, 0);
  xTaskCreatePinnedToCore(UITask, "UITask", 10000, NULL, 1, &Task2, 1);

}

void loop() {
}