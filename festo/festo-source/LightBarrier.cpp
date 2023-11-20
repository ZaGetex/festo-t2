/** 
 * File:   LightBarrier.cpp
 * @author Thomas Lehmann
 * @date 2016-09-26
 * @version 1
 * Initial version
 */

#include <cstdio>
#include "LightBarrier.h"
#include "FestoTransferSystem.h"

LightBarrier::LightBarrier(unsigned short bitmask) : bitmask(bitmask) {
}

bool LightBarrier::getState() {
    bool result = false;
    if (FestoTransferSystem::access != NULL) {
        result = FestoTransferSystem::access->isBitSet(bitmask);
    }
    return result;
}

bool LightBarrier::isClosed(){
    return getState();
}

bool LightBarrier::isOpen(){
    return !getState();
}
