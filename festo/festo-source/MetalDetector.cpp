/**
 * File:   MetalDetector.cpp
 * @author Thomas Lehmann
 * @date 2016-10-12
 * @version 1
 * Initial version
 */

#include <cstdio>
#include "MetalDetector.h"
#include "FestoTransferSystem.h"

MetalDetector::MetalDetector(unsigned short bitmask) {
    this->bitmask = bitmask;
}

bool MetalDetector::getState() {
    bool result = false;
    if (FestoTransferSystem::access != NULL) {
        result = FestoTransferSystem::access->isBitSet(bitmask);
    }
    return result;
}

bool MetalDetector::isMetalDetected(){
    return getState();
}
