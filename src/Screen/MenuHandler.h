/**
 * Lathe Electronic Gearbox @ Ivan Castillo Caro @ 2022
 * 
 * This class is used to handle Screen and menus
 * 
 **/
#pragma once

#include <Arduino.h>

#include <Screen/ScreenEncoderHandler.h>
#include <Screen/ScreenHandler.h>
#include <Motion/MotionService.h>

#include <config.h>

// Definition of enums to know in where we are currently

enum MenuPosition
{
    INFO_SCREEN = 0,
    MAIN_MENU = 1,
    SELECT_RELATION_MENU = 2,
    CUSTOM_RELATION_MENU = 3,
    CONFIG_MENU = 4,
    ABOUT_MENU = 5
};

class MenuHandler
{
public:
    MenuHandler();

    void update();
    void updateInfoScreen(bool force = false);

    void enterInfoScreen();
    void enterMainMenu();
    void enterPredefinedThreadMenu();
    void enterCustomRelationMenu();
    void enterSettingsMenu();
    void enterAboutMenu(); 

    void handleOkButton();
    void handleInfoScreenButton();
    void handleMainMenuButton();
    void handlePredefinedThreadButton();
    void handleCustomRelationMenuButton();
    void handleSettingsButton();
    void handleAboutButton();

    void handleEncoder();
    void handleMainMenuEncoder();
    void handlePredefinedThreadEncoder();
    void handleCustomRelationMenuEncoder();
    void handleConfigMenuEncoder();

private:
    void drawPredefinedThreadMenu(uint8_t page);
    void drawCustomRelationValue();
    void refreshSettingValues();

    uint8_t currentMenuPosition;
    uint8_t maximumMenuEntries;
    uint8_t currentPage;
    uint8_t maximumPages;
    MenuPosition m_menuPosition;

    ScreenEncoderHandler* enc;
    ScreenHandler* scrn;


    ///////// Motion Service Last Status Variables:

    uint16_t m_last_rpm;
    FeedDirectionMode m_last_feed_dir;
    EngageStatus m_last_engage_status;
    RunningMode m_last_running_mode;
 
    long m_last_refresh_time;
    ///////// Custom Relation Menu variables:

    uint16_t m_custom_relation;
};