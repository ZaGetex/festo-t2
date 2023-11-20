/**
 * File:   TimeHelper.h
 * @author Tobias De Gasperis
 * @date 20. April 2022
 */

#ifndef PRAKTIKUMPR2_TIMEHELPER_H
#define PRAKTIKUMPR2_TIMEHELPER_H

#include "minilab1008.h"

class TimeHelper {
private:
    static MiniLab1008* access;
public:
    TimeHelper();
    void sleep(unsigned int ms);
    unsigned long getMS();
};

void sleepForMS(unsigned int ms);
unsigned long getMilliSeconds();



#endif //PRAKTIKUMPR2_TIMEHELPER_H
