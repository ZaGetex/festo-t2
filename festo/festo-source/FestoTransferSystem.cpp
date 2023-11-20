/** 
 * File:   FestoTransferSystem.cpp
 * @author Thomas Lehmann
 * @date 2016-09-26
 * @version 1
 * Initial version
 * @version 2
 * Adds inverse logic for buttons.
 */

#include <iostream>
#include "FestoTransferSystem.h"
#include "iomasks.h"

MiniLab1008* FestoTransferSystem::access = nullptr;
unsigned int FestoTransferSystem::objectCounter = 0;

FestoTransferSystem::FestoTransferSystem() : lightbarrierBegin(ITEM_DETECTED),
        lightbarrierHeightSensor(ITEM_AT_HEIGHT_SENSOR),
        lightbarrierFeedSeparator(ITEM_AT_JUNCTION),
        lightbarrierBufferFull(BUFFER_IS_FULL),
        lightbarrierEnd(ITEM_AT_END),
        heightcheck(ITEM_HEIGHT_FITS),
        metalcheck(ITEM_IS_METTAL),
        pushbuttonStart(BUTTON_START_PRESSED),
        pushbuttonStop(BUTTON_STOP_PRESSED, true),
        pushbuttonReset(BUTTON_RESET_PRESSED),
        switchEmergency(EMERGENCY_STOP_PRESSED, true),
        ledStart(LED_START_BUTTON),
        ledReset(LED_RESET_BUTTON),
        ledQ1(LED_Q1),
        ledQ2(LED_Q2),
        feedSeparator(FEED_SEPARATOR),
        lampRed(ALARM_LAMP_RED),
        lampYellow(ALARM_LAMP_YELLOW),
        lampGreen(ALARM_LAMP_GREEN),
        drive()
{
    if (nullptr == access) {
        access = MiniLab1008::getInstance();
    }
    objectCounter++;
#ifdef FESTO_VERBOSE
    if(objectCounter>1){
        std::cerr << "Warning, multiple object of FestoTransferSystem, counter:" << objectCounter << std::endl;
    }
#endif
}
FestoTransferSystem::FestoTransferSystem(FestoTransferSystem &other) : lightbarrierBegin(other.lightbarrierBegin),
        lightbarrierHeightSensor(other.lightbarrierHeightSensor),
        lightbarrierFeedSeparator(other.lightbarrierFeedSeparator),
        lightbarrierBufferFull(other.lightbarrierBufferFull),
        lightbarrierEnd(other.lightbarrierEnd),
        heightcheck(other.heightcheck),
        metalcheck(other.metalcheck),
        pushbuttonStart(other.pushbuttonStart),
        pushbuttonStop(other.pushbuttonStop),
        pushbuttonReset(other.pushbuttonReset),
        switchEmergency(other.switchEmergency),
        ledStart(other.ledStart),
        ledReset(other.ledReset),
        ledQ1(other.ledQ1),
        ledQ2(other.ledQ2),
        feedSeparator(other.feedSeparator),
        lampRed(other.lampRed),
        lampYellow(other.lampYellow),
        lampGreen(other.lampGreen),
        drive(other.drive)
{

    if (nullptr == access) {
        access = MiniLab1008::getInstance();
    }
    objectCounter++;
#ifdef FESTO_VERBOSE
    if(objectCounter>1){
        std::cerr << "Warning, copy of object FestoTransferSystem has been created" << std::endl;
        std::cerr << "Warning, multiple object of FestoTransferSystem, counter:" << objectCounter << std::endl;
    }
#endif
}



void FestoTransferSystem::updateSensors() {
    if (nullptr != access) {
        access->updateProcessImage();
    }
}

void FestoTransferSystem::updateActuators() {
    if (nullptr != access) {
        access->applyOutputToProcess();
    }
}



