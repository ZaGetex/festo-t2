/** 
 * File:   AlarmLamp.h
 * @author Lehmann
 * @date 2016-09-17
 * @version 1
 * Initial version
 */

#ifndef ALARMLAMP_H
#define ALARMLAMP_H

#include "AlarmClock.h"

class AlarmLamp{
private:
    unsigned int bitmask;
    void setState(bool state);
    AlarmClock ac;
    bool state = false;
public:
    explicit AlarmLamp(unsigned short bitmask);
    void switchOn();
    void switchOff();

    /**
     * Lässt die Lampe blinken.
     * Diese Methode checkt den Zustand der Lampe und wie viel Zeit seit dem letzten Aufruf vergangen ist.
     * Sind mehr als 500 ms vergangen, wird der Zustand der Lampe geändert.
     * Diese Methode muss also regelmäßig aufgerufen werden, damit die Lampe blinkt.
     */
    void blink();
};

#endif /* ALARMLAMP_H */

