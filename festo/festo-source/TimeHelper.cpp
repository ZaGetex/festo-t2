/**
 * File:   TimeHelper.cpp
 * @author Tobias De Gasperis
 * @date 20. April 2022
 */
#include <chrono>
#include <thread>
#include "TimeHelper.h"
#include "minilab1008.h"

MiniLab1008* TimeHelper::access = NULL;

void TimeHelper::sleep(unsigned int ms) {
    access->sleep(ms);
}

TimeHelper::TimeHelper() {
    if (access == NULL) {
        access = MiniLab1008::getInstance();
    }
}

unsigned long TimeHelper::getMS() {
    return access->getMS();
}

void sleepForMS(unsigned int ms){
    TimeHelper th;
    th.sleep(ms);
}

unsigned long getMilliSeconds() {
    TimeHelper th;
    return th.getMS();

}



