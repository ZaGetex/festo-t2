//
// Created by Tobias De Gasperis on 12.10.22.
//

#ifndef PRAKTIKUMPR2_ALARMCLOCK_H
#define PRAKTIKUMPR2_ALARMCLOCK_H


class AlarmClock {
private:
    unsigned long duration;
    bool running;
    unsigned long statTime;
public:
    AlarmClock(unsigned long durationInMS);
    AlarmClock();

    void setDuration(unsigned long durationInMS);
    void startClock();
    void stopClock();

    bool clockExpired();

};


#endif //PRAKTIKUMPR2_ALARMCLOCK_H
