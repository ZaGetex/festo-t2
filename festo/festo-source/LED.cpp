/** 
 * File:   LED.cpp
 * @author Thomas Lehmann
 * @date 2016-09-26
 * @version 1
 * Initial version
 */

#include <cstdio>
#include "LED.h"
#include "FestoTransferSystem.h"

LED::LED(unsigned short bitmask) : bitmask(bitmask) {
}

void LED::setState(bool state) {
    if (FestoTransferSystem::access != NULL) {
        if (state) {
            FestoTransferSystem::access->setBitInOutput(bitmask);
        } else {
            FestoTransferSystem::access->clearBitInOutput(bitmask);
        }
    }
}

void LED::switchOn(){
    setState(true);
}

void LED::switchOff(){
    setState(false);
}

