/* 
 * File:   HeightSensor.cpp
 * @author Thomas Lehmann
 * @date 2016-10-12
 * @version 1
 * Initial version
 */

#include <cstdio>
#include "HeightSensor.h"
#include "FestoTransferSystem.h"

HeightSensor::HeightSensor(unsigned short bitmask) {
    this->bitmask = bitmask;
}

bool HeightSensor::getState() {
    bool result = false;
    if (FestoTransferSystem::access != NULL) {
        result = FestoTransferSystem::access->isBitSet(bitmask);
    }
    return result;
}

bool HeightSensor::isHeightCorrect(){
    return getState();
}
