
/* 
 * File:   simhciaction.cpp
 * @author Lehmann
 * @date 9. Mai 2020
 */

#include "simhciaction.h"
#include "simmasks.h"

#include <string>
#include <sstream>

SimHCIAction::SimHCIAction(unsigned int atTime) : executed(false), atTime(atTime), setPattern(0), clearPattern(0) {
}

SimHCIAction::SimHCIAction(unsigned int atTime, SimHCIActionKind kind) : executed(false), atTime(atTime), setPattern(0), clearPattern(0) {
    switch (kind) {
        case SimHCIActionKind::pressStartOnly:
            pressStartOnly();
            break;
        case SimHCIActionKind::pressStopOnly:
            pressStopOnly();
            break;
        case SimHCIActionKind::pressResetOnly:
            pressResetOnly();
            break;
        case SimHCIActionKind::pressEStopOnly:
            pressEStopOnly();
            break;
        case SimHCIActionKind::releaseAll:
            releaseAll();
            break;
        case SimHCIActionKind::pressStart:
            pressStart();
            break;
        case SimHCIActionKind::pressStop:
            pressStop();
            break;
        case SimHCIActionKind::pressReset:
            pressReset();
            break;
        case SimHCIActionKind::pressEStop:
            pressEStop();
            break;
        default:
            ;
    }
}

void SimHCIAction::releaseAll() {
    setPattern = SIM_BUTTON_STOP | SIM_EMERGENCY_STOP;
    clearPattern = SIM_BUTTON_START | SIM_BUTTON_RESET;
}

void SimHCIAction::pressStart() {
    setPattern = setPattern | SIM_BUTTON_START;
}

void SimHCIAction::pressStop() {
    clearPattern = clearPattern | SIM_BUTTON_STOP;
}

void SimHCIAction::pressReset() {
    setPattern = setPattern | SIM_BUTTON_RESET;
}

void SimHCIAction::pressEStop() {
    clearPattern = clearPattern | SIM_EMERGENCY_STOP;
}

void SimHCIAction::releaseStart() {
    clearPattern = clearPattern | SIM_BUTTON_START;
}

void SimHCIAction::releaseStop() {
    setPattern = setPattern | SIM_BUTTON_STOP;
}

void SimHCIAction::releaseReset() {
    clearPattern = clearPattern | SIM_BUTTON_RESET;
}

void SimHCIAction::releaseEStop() {
    setPattern = setPattern | SIM_EMERGENCY_STOP;
}

void SimHCIAction::pressStartOnly() {
    setPattern = SIM_BUTTON_START | SIM_BUTTON_STOP | SIM_EMERGENCY_STOP;
    clearPattern = SIM_BUTTON_RESET;
}

void SimHCIAction::pressStopOnly() {
    setPattern = SIM_EMERGENCY_STOP;
    clearPattern = SIM_BUTTON_STOP | SIM_BUTTON_START | SIM_BUTTON_RESET;
}

void SimHCIAction::pressResetOnly() {
    setPattern = SIM_BUTTON_RESET | SIM_BUTTON_STOP | SIM_EMERGENCY_STOP;
    clearPattern = SIM_BUTTON_START;
}

void SimHCIAction::pressEStopOnly() {
    setPattern = SIM_BUTTON_STOP;
    clearPattern = SIM_EMERGENCY_STOP | SIM_BUTTON_START | SIM_BUTTON_RESET;
}

void SimHCIAction::setToDefault() {
    executed = false;
    atTime = 0;
    setPattern = SIM_BUTTON_STOP | SIM_EMERGENCY_STOP;
    clearPattern = SIM_BUTTON_START | SIM_BUTTON_RESET;
}

bool SimHCIAction::evalPair(const char* key, const char* value) {
    //cout << "text>" << key << ":" << value << endl;
    bool validPair = false;
    if (std::string("type") == key) {
        if (std::string("hciaction") == value) {
            validPair = true;   // got valid string
        }        
    }
    //cout << "valid:" << (validPair?"T":"F") << endl;
    return validPair;
};

bool SimHCIAction::evalPair(const char* key, double value) {
    //cout << "nummeric>" << key << ":" << value << endl;
    bool validPair = false;
    if (std::string("atTime") == key) {
        atTime = (int) value;
        validPair = true;
    }
    if (std::string("pattern") == key) {
        setPattern =  ((int)value & 0x0F) << 8;
        clearPattern = ((int)value & 0xF0) << 4;

        validPair = true;
    }
    return validPair;
};

std::string SimHCIAction::toJSONString() {
    std::ostringstream result;
    result << "{\"type\":\"hciaction\", ";
    result << "\"atTime\": " << atTime << ", ";
    result << "\"pattern\": ";

    int patternvalue = (clearPattern >> 4) | (setPattern >> 8);
    result << patternvalue << "}";

    return result.str();
}

