/* 
 * File:   PushButton.cpp
 * @author Thomas Lehmann
 * @date 2016-09-26
 * @version 1
 * Initial version
 * @date 2018-11-07
 * @version 2
 *
 */

#include <cstdio>
#include "PushButton.h"
#include "FestoTransferSystem.h"

PushButton::PushButton(unsigned short bitmask):bitmask(bitmask), inverseLogic(false) {
}

PushButton::PushButton(unsigned short bitmask, bool inverse):bitmask(bitmask), inverseLogic(inverse) {
}

bool PushButton::getState() {
    bool result = false;
    if (FestoTransferSystem::access != NULL) {
        result = FestoTransferSystem::access->isBitSet(bitmask);
    }
    return result;
}

bool PushButton::positiveEvent() {
    bool result = false;
    if (FestoTransferSystem::access != NULL) {
        result = FestoTransferSystem::access->isBitPosEdge(bitmask);
    }
    return result;
}

bool PushButton::negativeEvent() {
    bool result = false;
    if (FestoTransferSystem::access != NULL) {
        result = FestoTransferSystem::access->isBitNegEdge(bitmask);
    }
    return result;
}

bool PushButton::isPressEvent() {
    return inverseLogic ? negativeEvent() : positiveEvent();
}

bool PushButton::isReleaseEvent() {
    return inverseLogic ? positiveEvent() : negativeEvent();
}

bool PushButton::isPressed() {
    return getState() ^ inverseLogic;
}

bool PushButton::isReleased() {
    return !(getState() ^ inverseLogic);
}

