#include <Screen/MenuHandler.h>

#include <Screen/MenuHandlerUtils.h>

#include <Screen/SplashScreen.h>

MenuHandler::MenuHandler() : m_last_refresh_time(millis())
{
    enc = ScreenEncoderHandler::getInstance();
    scrn = ScreenHandler::getInstance();
}

void MenuHandler::enterInfoScreen()
{
    m_menuPosition = MenuPosition::INFO_SCREEN;
    currentMenuPosition = 0;
    maximumMenuEntries = 0;
    maximumPages = 0;
    currentPage = 0;

    scrn->clearScreen();

    // Reset encoder count
    enc->setCount(0);

    // TO-DO: Replace texts with MotionService Calls
    scrn->drawHLine(11, 12, 105, NO_COMMIT);
    scrn->drawText("F0000", 23, 38, TEXT_EXTRALARGE, NO_COMMIT);
    scrn->drawText("rpm", 103, 38, TEXT_SMALL, NO_COMMIT);

    String feed = MotionService::getInstance()->getThreadRelation().getDisplayValue();

    uint8_t textXPos = calculateTextCenter(feed, "mm/rev", TEXT_LARGE, TEXT_SMALL);
    uint8_t secondStr = calculateSecondStringOffset(feed, "mm/rev", TEXT_LARGE, TEXT_SMALL);

    scrn->drawText(feed, textXPos, 55, TEXT_LARGE, NO_COMMIT);
    scrn->drawText("mm/rev", secondStr, 55, TEXT_SMALL, COMMIT);
    updateInfoScreen(true);
}

void MenuHandler::enterMainMenu()
{
    m_menuPosition = MenuPosition::MAIN_MENU;
    currentMenuPosition = 0;
    maximumMenuEntries = 5;
    currentPage = 0;
    maximumPages = 0;

    scrn->clearScreen();

    // Reset encoder count
    enc->setCount(0);

    // Show static content at screen
    scrn->drawMenuLine("Go back", 0, ScreenMenuSymbols::BACK_ARROW);
    scrn->drawMenuLine("Predefined Threads", 1, ScreenMenuSymbols::RIGHT_ARROW);
    scrn->drawMenuLine("Custom Gear Rel", 2, ScreenMenuSymbols::RIGHT_ARROW);
    scrn->drawMenuLine("Settings", 3, ScreenMenuSymbols::RIGHT_ARROW);
    scrn->drawMenuLine("About", 4, ScreenMenuSymbols::RIGHT_ARROW);

    scrn->drawMenuLineSelected(0);
}

void MenuHandler::enterPredefinedThreadMenu()
{
    m_menuPosition = MenuPosition::SELECT_RELATION_MENU;
    currentMenuPosition = 0;
    maximumMenuEntries = PREDEFINED_THREADS_SIZE + 1; // We have to add Go back;
    currentPage = 0;
    maximumPages = maximumMenuEntries / 5 + 1; // Ceiling division

    scrn->clearScreen();

    enc->setCount(0);

    drawPredefinedThreadMenu(currentPage);
}

void MenuHandler::drawPredefinedThreadMenu(uint8_t page)
{
    scrn->clearScreen();
    if (page == 0)
    {
        scrn->drawMenuLine("Go back", 0, ScreenMenuSymbols::BACK_ARROW);
        scrn->drawMenuLine(PredefinedRelationSettings[0].getDisplayValue(), 1, ScreenMenuSymbols::RIGHT_ARROW);
        scrn->drawMenuLine(PredefinedRelationSettings[1].getDisplayValue(), 2, ScreenMenuSymbols::RIGHT_ARROW);
        scrn->drawMenuLine(PredefinedRelationSettings[2].getDisplayValue(), 3, ScreenMenuSymbols::RIGHT_ARROW);
        scrn->drawMenuLine(PredefinedRelationSettings[3].getDisplayValue(), 4, ScreenMenuSymbols::RIGHT_ARROW);
    }
    else
    {
        uint8_t index = 0;
        for (size_t i = (page * 5) - 1; i < ((page + 1) * 5) - 1; i++)
        {
            if (i < PREDEFINED_THREADS_SIZE)
            {
                scrn->drawMenuLine(PredefinedRelationSettings[i].getDisplayValue(), index, ScreenMenuSymbols::RIGHT_ARROW);
            }
            index++;
        }
    }
}

void MenuHandler::enterCustomRelationMenu()
{
    m_menuPosition = MenuPosition::CUSTOM_RELATION_MENU;
    currentMenuPosition = 0;
    maximumMenuEntries = 0;
    maximumPages = 0;
    currentPage = 0;
    m_custom_relation = 0;

    scrn->clearScreen();

    enc->setCount(0);

    // TO-DO: Replace texts with MotionService Calls
    scrn->drawText("Custom Gear Rel", 20, 10, TEXT_NORMAL, NO_COMMIT);
    scrn->drawHLine(11, 12, 105, NO_COMMIT);

    scrn->drawText("0.000", 10, 45, TEXT_EXTRALARGE, NO_COMMIT);
    scrn->drawText("mm/rev", 90, 45, TEXT_SMALL, COMMIT);
}

void MenuHandler::drawCustomRelationValue()
{

    scrn->clearPartOfScreen(10, 25, 80, 20, NO_COMMIT);
    scrn->drawText(String((float)m_custom_relation / 1000, 3U), 10, 45, TEXT_EXTRALARGE, COMMIT);
}

void MenuHandler::enterSettingsMenu()
{
    MotionService* mot = MotionService::getInstance();
    scrn->clearScreen();

    enc->setCount(0);

    m_menuPosition = MenuPosition::CONFIG_MENU;
    currentMenuPosition = 0;
    maximumMenuEntries = 3;
    maximumPages = 0;
    currentPage = 0;

    scrn->drawMenuLine("Go back", 0, ScreenMenuSymbols::BACK_ARROW);
    scrn->drawMenuLine(getLineChecked("Reverse Feed  ", mot->getFeedDirectionMode()), 1);
    scrn->drawMenuLine(getLineChecked("Manual Stop   ", mot->getEngageStatus()), 2);

    scrn->drawMenuLineSelected(0);
}

void MenuHandler::enterAboutMenu()
{
    scrn->clearScreen();

    enc->setCount(0);

    m_menuPosition = MenuPosition::ABOUT_MENU;
    currentMenuPosition = 0;
    maximumMenuEntries = 0;
    maximumPages = 0;
    currentPage = 0;

    scrn->drawBitmap(splash_bitmap,SPLASH_WIDTH,SPLASH_HEIGHT,75,3);
    scrn->drawText("Lathe", 5, 12, TEXT_NORMAL, false);
    scrn->drawText("Electronic", 5, 23, TEXT_NORMAL, false);
    scrn->drawText("Gearbox", 5, 34, TEXT_NORMAL, false);
    scrn->drawText(VERSION, 5, 46, TEXT_SMALL, false);
    scrn->drawText("Ivan Castillo @ 2022",5, 58);
}

// Button Handling

void MenuHandler::handleOkButton()
{
    switch (m_menuPosition)
    {
    case INFO_SCREEN:
        handleInfoScreenButton();
        break;
    case MAIN_MENU:
        handleMainMenuButton();
        break;
    case SELECT_RELATION_MENU:
        handlePredefinedThreadButton();
        break;
    case CUSTOM_RELATION_MENU:
        handleCustomRelationMenuButton();
        break;
    case CONFIG_MENU:
        handleSettingsButton();
        break;
    case ABOUT_MENU:
        handleAboutButton();
        break;
    default:
        break;
    };
}

void MenuHandler::handleInfoScreenButton()
{
    // Go to Main menu
    enterMainMenu();
}

void MenuHandler::handleMainMenuButton()
{
    switch (currentMenuPosition)
    {
    case 0: // Go back
        enterInfoScreen();
        break;
    case 1: // PredefinedThreads
        enterPredefinedThreadMenu();
        break;
    case 2: // Custom Gear Relation
        enterCustomRelationMenu();
        break;
    case 3: // Enter Settings
        enterSettingsMenu();
        break;
    case 4: // Enter About
        enterAboutMenu();
        break;
    }
}

void MenuHandler::handlePredefinedThreadButton()
{
    if (currentMenuPosition != 0)
    {
        MotionService::getInstance()->setThreadRelation(PredefinedRelationSettings[currentMenuPosition - 1]);
        MotionService::getInstance()->setRunningMode(RunningMode::PREDEFINED_MODE);
    }

    enterInfoScreen();
}

void MenuHandler::handleCustomRelationMenuButton()
{
    // Motion::ApplyCurrentThread(currentMenuPosition);
    MotionService::getInstance()->setRunningMode(RunningMode::CUSTOM_MODE);
    MotionService::getInstance()->setThreadRelation(ThreadRelation("Custom", (float)m_custom_relation/1000));
    enterInfoScreen();
}

void MenuHandler::handleSettingsButton()
{
    MotionService* mot = MotionService::getInstance();
    switch (currentMenuPosition)
    {
        case 1:
            mot->invertFeedDirectionMode();
            refreshSettingValues();
            break;
        case 2:
            mot->invertEngageStatus();
            refreshSettingValues();
            break;
        default:
            enterInfoScreen();
    }
}

void MenuHandler::handleAboutButton()
{
    enterInfoScreen();
}

//////////////////////
// Encoder Handlers //
//////////////////////

void MenuHandler::handleEncoder()
{
    switch (m_menuPosition)
    {
    case INFO_SCREEN:
        // There is no need to handle encoder
        break;
    case MAIN_MENU:
        handleMainMenuEncoder();
        break;
    case SELECT_RELATION_MENU:
        handlePredefinedThreadEncoder();
        break;
    case CUSTOM_RELATION_MENU:
        handleCustomRelationMenuEncoder();
        break;
    case CONFIG_MENU:
        handleConfigMenuEncoder();
        break;
    case ABOUT_MENU:
        // There is no need to handle encoder
        break;
    default:

        break;
    }
}

void MenuHandler::handleMainMenuEncoder()
{
    int8_t actualEnc = enc->getCount();

    // Saturation Mechanism
    if ((actualEnc & 1) == 0)  //More efficient than actualEnc % 2 == 0
    {
        actualEnc = actualEnc / 2;
        if (actualEnc < 0)
        {
            enc->setCount(0);
            actualEnc = 0;
        }
        if (actualEnc > maximumMenuEntries - 1)
        {
            enc->setCount((maximumMenuEntries - 1) * 2);
            actualEnc = maximumMenuEntries - 1;
        }
        // Redraw if neccesary
        if (actualEnc != currentMenuPosition)
        {
            scrn->drawMenuLineSelected(actualEnc);
            currentMenuPosition = actualEnc;
        }
    }
}

void MenuHandler::handlePredefinedThreadEncoder()
{
    int16_t actualEnc = enc->getCount();

    // Saturation Mechanism
    if ((actualEnc & 1) == 0)  //More efficient than actualEnc % 2 == 0
    {
        actualEnc = actualEnc / 2; // Is better to mess with the encoder in this way
        if (actualEnc < 0)
        {
            enc->setCount(0);
            actualEnc = 0;
        }
        if (actualEnc > maximumMenuEntries - 1)
        {
            enc->setCount((maximumMenuEntries - 1) * 2); // We have to double the number
            actualEnc = maximumMenuEntries - 1;
        }
        // Redraw if neccesary
        if (actualEnc != currentMenuPosition)
        {
            // If we pass between pages, we have to check if redraw
            if (actualEnc / 5 != currentPage)
            {
                currentPage = actualEnc / 5;
                drawPredefinedThreadMenu(currentPage);
            }

            scrn->drawMenuLineSelected(actualEnc % 5);
            currentMenuPosition = actualEnc;
        }
    }
}

void MenuHandler::handleCustomRelationMenuEncoder()
{
    int actualEnc = enc->getCount();

    // Saturation Mechanism
    if ((actualEnc & 1) == 0)  //More efficient than actualEnc % 2 == 0
    {
        if (actualEnc < 0)
        {
            enc->setCount(0);
            actualEnc = 0;
        }
        if (actualEnc > 9999) // No more than 9.999mm
        {
            enc->setCount(9999); // We have to double the number
            actualEnc = 9999;
        }
        // Redraw if neccesary
        if (actualEnc != m_custom_relation)
        {
            // If we pass between pages, we have to check if redraw
            drawCustomRelationValue();
            m_custom_relation = actualEnc;
        }
    }
}

void MenuHandler::handleConfigMenuEncoder() {

    int8_t actualEnc = enc->getCount();

    // Saturation Mechanism
    if ((actualEnc & 1) == 0)  //More efficient than actualEnc % 2 == 0
    {
        actualEnc = actualEnc / 2;
        if (actualEnc < 0)
        {
            enc->setCount(0);
            actualEnc = 0;
        }
        if (actualEnc > maximumMenuEntries - 1)
        {
            enc->setCount((maximumMenuEntries - 1) * 2);
            actualEnc = maximumMenuEntries - 1;
        }
        // Redraw if neccesary
        if (actualEnc != currentMenuPosition)
        {
            scrn->drawMenuLineSelected(actualEnc);
            currentMenuPosition = actualEnc;
        }
    }
}


void MenuHandler::update()
{
    if (millis() - m_last_refresh_time > 1000) {

    switch (m_menuPosition)
    {
    case INFO_SCREEN:
        updateInfoScreen();
        break;
    case MAIN_MENU:

        break;

    case SELECT_RELATION_MENU:

        break;

    case CUSTOM_RELATION_MENU:

        break;

    case CONFIG_MENU:

        break;

    case ABOUT_MENU:

        break;
    }

    m_last_refresh_time = millis();
    }

    if (ScreenEncoderHandler::getInstance()->buttonState()) {
        handleOkButton();
    }

    handleEncoder();
}

void MenuHandler::updateInfoScreen(bool force)
{
    MotionService *mot = MotionService::getInstance();
    // TO-DO: Refresh status string
    if (force || mot->getRunningMode() != m_last_running_mode || mot->getEngageStatus() != m_last_engage_status || mot->getFeedDirectionMode() != m_last_feed_dir)
    {
        // Refresh variables
        m_last_running_mode = mot->getRunningMode();
        m_last_engage_status = mot->getEngageStatus();
        m_last_feed_dir = mot->getFeedDirectionMode();

        String statusStr;
        statusStr = m_last_engage_status == EngageStatus::ENGAGED ? "Engd" : "Stop";
        statusStr += "|";
        statusStr += m_last_running_mode == RunningMode::PREDEFINED_MODE ? "Predef" : "Custom";
        statusStr += "|";
        statusStr += m_last_feed_dir == FeedDirectionMode::FORWARD ? "Dir" : "Inv";

        // Clear last statusStr

        scrn->clearPartOfScreen(20, 0, 100, 12, NO_COMMIT);
        scrn->drawText(statusStr, 20, 10);
    }

    // Refresh RPM:
    if ((mot->getActualRPM() != m_last_rpm) || force)
    {
        String rpmStr = MotionService::getInstance()->getHeadDirectionStatus() == FeedDirectionMode::FORWARD ? "F" : "R";
        m_last_rpm = MotionService::getInstance()->getActualRPM();
        rpmStr += formatRPMString(m_last_rpm);
        scrn->clearPartOfScreen(23, 19, 80, 20, NO_COMMIT);
        scrn->drawText(rpmStr, 23, 38, TEXT_EXTRALARGE, COMMIT);
    }
}

void MenuHandler::refreshSettingValues() {
    switch(currentMenuPosition) {
        case 1:
            scrn->clearMenuLine(1, false);
            scrn->drawMenuLine(getLineChecked("Reverse Feed  ", MotionService::getInstance()->getFeedDirectionMode()), 1);
            scrn->drawMenuLineSelected(1);
            break;
        
        case 2:
            scrn->clearMenuLine(2, false);
            scrn->drawMenuLine(getLineChecked("Manual Stop   ", MotionService::getInstance()->getSettingEngageStatus()), 2);
            scrn->drawMenuLineSelected(2);
        
            break;

    }
}