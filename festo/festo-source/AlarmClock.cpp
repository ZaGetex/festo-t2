//
// Created by Tobias De Gasperis on 12.10.22.
//

#include "AlarmClock.h"
#include "TimeHelper.h"

void AlarmClock::setDuration(unsigned long durationInMS)
{
    AlarmClock::duration = durationInMS;
}

AlarmClock::AlarmClock(unsigned long durationInMS)
: duration(durationInMS)
, running(false)
, statTime(0)
{
}

AlarmClock::AlarmClock()
: duration(0)
, running(false)
, statTime(0)
{
}

void AlarmClock::startClock() {
    running = true;
    statTime = getMilliSeconds();
}

bool AlarmClock::clockExpired() {
    bool ret = false;
    if(running){
        ret = (getMilliSeconds() - statTime > duration);
        if(ret) {
            statTime = getMilliSeconds();
        }
    }
    return ret;
}

void AlarmClock::stopClock() {
    running = false;
}
