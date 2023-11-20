/*
 * File:   simlbiaction.cpp
 * @author Jaehnichen
 * @date 14. April 2021
 */

#include "simlbiaction.h"
#include "simmasks.h"

#include <string>
#include <sstream>

SimLBIAction::SimLBIAction(unsigned int atTime) : executed(false), atTime(atTime), pattern(0) {
}

SimLBIAction::SimLBIAction(unsigned int atTime, SimLBIActionKind kind) : executed(false), atTime(atTime), pattern(0) {
    switch (kind) {
        case SimLBIActionKind::interruptBegin:
            interruptStart();
            break;
        case SimLBIActionKind::interruptHeightSensor:
            interruptHeightSensor();
            break;
        case SimLBIActionKind::interruptFeedSeparator:
            interruptFeedSeparator();
            break;
        case SimLBIActionKind::interruptBufferFull:
            interruptBufferFull();
            break;
        case SimLBIActionKind::interruptEnd:
            interruptEnd();
            break;
        case SimLBIActionKind::closeAll:
            closeAll();
            break;
        case SimLBIActionKind::closeBegin:
            closeStart();
            break;
        case SimLBIActionKind::closeHeightSensor:
            closeHeightSensor();
            break;
        case SimLBIActionKind::closeFeedSeparator:
            closeFeedSeparator();
            break;
        case SimLBIActionKind::closeBufferFull:
            closeBufferFull();
            break;
        case SimLBIActionKind::closeEnd:
            closeEnd();
            break;
        default:
            ;
    }
}

void SimLBIAction::interruptStart() {
    lb = SimLBKind::lbBegin;
    manuallyInterrupted = true;
}

void SimLBIAction::closeStart() {
    lb = SimLBKind::lbBegin;
    manuallyInterrupted = false;
}

void SimLBIAction::interruptHeightSensor() {
    lb = SimLBKind::lbHeightSensor;
    manuallyInterrupted = true;
}

void SimLBIAction::closeHeightSensor() {
    lb = SimLBKind::lbHeightSensor;
    manuallyInterrupted = false;
}

void SimLBIAction::interruptFeedSeparator() {
    lb = SimLBKind::lbFeedSeparator;
    manuallyInterrupted = true;
}

void SimLBIAction::closeFeedSeparator() {
    lb = SimLBKind::lbFeedSeparator;
    manuallyInterrupted = false;
}

void SimLBIAction::interruptBufferFull() {
    lb = SimLBKind::lbBufferFull;
    manuallyInterrupted = true;
}

void SimLBIAction::closeBufferFull() {
    lb = SimLBKind::lbBufferFull;
    manuallyInterrupted = false;
}

void SimLBIAction::interruptEnd() {
    lb = SimLBKind::lbEnd;
    manuallyInterrupted = true;
}

void SimLBIAction::closeEnd() {
    lb = SimLBKind::lbEnd;
    manuallyInterrupted = false;
}

void SimLBIAction::closeAll() {
    lb = SimLBKind::all;
    manuallyInterrupted = false;
}

void SimLBIAction::setToDefault() {
    executed = false;
    atTime = 0;
    lb = SimLBKind::all;
    manuallyInterrupted = false;
}

std::string SimLBIAction::toJSONString() {
    std::ostringstream result;
    result << "{\"type\":\"lightbarrieraction\", ";
    result << "\"atTime\": " << atTime << ", ";
    result << "\"lb\": " << (int)lb << ", ";
    result << "\"manually\": " << (manuallyInterrupted?1:0) << "}";

    return result.str();
}

bool SimLBIAction::evalPair(const char *key, double value) { //TODO
//cout << "nummeric>" << key << ":" << value << endl;
    bool validPair = false;
    if (std::string("atTime") == key) {
        atTime = (int) value;
        validPair = true;
    }
    if (std::string("pattern") == key) {
        pattern = (SIM_ITEM_DETECTED | SIM_ITEM_AT_HEIGHT_SENSOR | SIM_ITEM_AT_JUNCTION | SIM_ITEM_AT_END | SIM_BUFFER_IS_FULL);
        if(((int)value) & (int)SimLBKind::lbBegin){
            pattern &=  SIM_ITEM_DETECTED;
        };
        if(((int)value) & 0x02){
            pattern &=  SIM_ITEM_AT_HEIGHT_SENSOR;
        };
        if(((int)value) & 0x04){
            pattern &=  SIM_ITEM_AT_JUNCTION;
        };
        if(((int)value) & 0x08){
            pattern &=  SIM_BUFFER_IS_FULL;
        };
        if(((int)value) & 0x10){
            pattern &=  SIM_ITEM_AT_END;
        };

        validPair = true;
    }
    return validPair;
}

bool SimLBIAction::evalPair(const char *key, const char *value) {
    //cout << "text>" << key << ":" << value << endl;
    bool validPair = false;
    if (std::string("type") == key) {
        if (std::string("lightbarrieraction") == value) {
            validPair = true;   // got valid string
        }
    }
    //cout << "valid:" << (validPair?"T":"F") << endl;
    return validPair;
}