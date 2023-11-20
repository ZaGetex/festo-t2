/**
 * @author Niklas Dathe
 * @author Florian Czorniuk
 * @date   09.11.2023
 */

#include <iostream>
#include "TimeHelper.h"
#include "FestoTransferSystem.h"
#include "AlarmLamp.h"

using namespace std;

#define WAIT 1000
#define LAP 5

void setAlarmLampState(FestoTransferSystem& festo, AlarmLamp& lamp, bool state);
void ampelschaltung(FestoTransferSystem *);
void consoleLogBarrierState(FestoTransferSystem * );

void start(FestoTransferSystem *);
void stop(FestoTransferSystem *);
void q1(FestoTransferSystem *);
void q2(FestoTransferSystem *);
void emergency(FestoTransferSystem *, bool *);


int main() {
    FestoTransferSystem festo;
    bool run = true;
    //Boot
    for (int i = 0; i < LAP; ++i) {
        ampelschaltung(&festo);
    }

    while(run) {
        festo.updateSensors();
        start(&festo);
        stop(&festo);
        q1(&festo);
        q2(&festo);
        emergency(&festo, &run);
        festo.updateActuators();
    }
    return 0;
}

void setAlarmLampState(FestoTransferSystem& festo, AlarmLamp& lamp, bool state) {
    unsigned short bitmask = lamp.getBitmask();
    if (state) { //true
        festo.setBitInOutput(bitmask);
    } else { //false
        festo.clearBitInOutput(bitmask);
    }
}

void ampelschaltung(FestoTransferSystem *festo){

    festo->updateSensors();
    setAlarmLampState(*festo, festo->lampRed, true);
    setAlarmLampState(*festo, festo->lampYellow, false);
    setAlarmLampState(*festo, festo->lampGreen, false);
    consoleLogBarrierState(festo);
    festo->updateActuators();
    sleepForMS(WAIT);

    festo->updateSensors();
    setAlarmLampState(*festo, festo->lampRed, true);
    setAlarmLampState(*festo, festo->lampYellow, true);
    setAlarmLampState(*festo, festo->lampGreen, false);
    consoleLogBarrierState(festo);
    festo->updateActuators();
    sleepForMS(WAIT);

    festo->updateSensors();
    setAlarmLampState(*festo, festo->lampRed, false);
    setAlarmLampState(*festo, festo->lampYellow, false);
    setAlarmLampState(*festo, festo->lampGreen, true);
    consoleLogBarrierState(festo);
    festo->updateActuators();
    sleepForMS(WAIT);

    festo->updateSensors();
    setAlarmLampState(*festo, festo->lampRed, false);
    setAlarmLampState(*festo, festo->lampYellow, true);
    setAlarmLampState(*festo, festo->lampGreen, false);
    consoleLogBarrierState(festo);
    festo->updateActuators();
    sleepForMS(WAIT);

}


void consoleLogBarrierState(FestoTransferSystem * festo){

        cout << "Beginn:" << festo->lightbarrierBegin.getState() << endl;
        cout << "End:" << festo->lightbarrierEnd.getState() << endl;
        cout << "Height:" << festo->lightbarrierHeightSensor.getState() << endl;
        cout << "BufferFull:" << festo->lightbarrierBufferFull.getState() << endl;
        cout << "Separator:" << festo->lightbarrierFeedSeparator.getState() << endl;

}

void start(FestoTransferSystem *festo){
    festo->ledStart.setState(festo->pushbuttonStart.getState());
    if(festo->pushbuttonStart.getState() && festo->lightbarrierEnd.getState()){
        festo->drive.setSpeed(CONVEYERBELT_RIGHT_FAST);
    }
    else {
        festo->drive.setSpeed(CONVEYERBELT_STOP);
    }
}

void stop(FestoTransferSystem *festo){
    if(!festo->pushbuttonStop.getState()){
        festo->feedSeparator.setState(true);
        festo->ledReset.setState(true);
    }
    else {
        festo->feedSeparator.setState(false);
        festo->ledReset.setState(false);
    }
}

void q1(FestoTransferSystem *festo){
    festo->ledQ1.setState(festo->lightbarrierBegin.getState());
}

void q2(FestoTransferSystem *festo){
    festo->ledQ2.setState(!festo->lightbarrierHeightSensor.getState());
}

void emergency(FestoTransferSystem *festo, bool * run){
    if(!festo->switchEmergency.getState()){
        festo->drive.setSpeed(CONVEYERBELT_STOP);
        festo->feedSeparator.setState(false);
        festo->lampRed.setState(false);
        festo->lampYellow.setState(false);
        festo->lampGreen.setState(false);
        festo->ledQ1.setState(false);
        festo->ledQ2.setState(false);
        festo->ledStart.setState(false);
        festo->ledReset.setState(false);
        *run = false;
    }
}