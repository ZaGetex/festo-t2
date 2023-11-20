/** 
 * File:   AlarmLamp.cpp
 * @author Thomas Lehmann
 * @date 2016-09-17
 * @version 1
 * Initial version
 */

#include <cstdio>
#include "AlarmLamp.h"
#include "FestoTransferSystem.h"

AlarmLamp::AlarmLamp(unsigned short bitmask) : bitmask(bitmask), ac(500), state(false)
{
    ac.startClock();
}

void AlarmLamp::setState(bool state) {
    if (FestoTransferSystem::access != NULL) {
        if (state) {
            FestoTransferSystem::access->setBitInOutput(bitmask);
        } else {
            FestoTransferSystem::access->clearBitInOutput(bitmask);
        }
    }
    this->state = state;
}

void AlarmLamp::switchOn(){
    setState(true);
}

void AlarmLamp::switchOff(){
    setState(false);
}

void AlarmLamp::blink() {
    if(ac.clockExpired()){
        if(state){
            this->switchOff();
        }else{
            this->switchOn();
        }
    }
}