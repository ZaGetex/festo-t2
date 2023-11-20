/**
 * @author Niklas Dathe
 * @author Florian Czorniuk
 * @date   09.11.2023
 */

#include <iostream>
#include "TimeHelper.h"
#include "FestoTransferSystem.h"

using namespace std;

#define WAIT 1000
#define LAP 5

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


void ampelschaltung(FestoTransferSystem *festo){
    //new
    festo->updateSensors();
    festo->lampRed.switchOn();
    festo->lampYellow.switchOff();
    festo->lampGreen.switchOff();
    consoleLogBarrierState(festo);
    festo->updateActuators();
    sleepForMS(WAIT);

    festo->updateSensors();
    festo->lampRed.switchOn();
    festo->lampYellow.switchOn();
    festo->lampGreen.switchOff();
    consoleLogBarrierState(festo);
    festo->updateActuators();
    sleepForMS(WAIT);

    festo->updateSensors();
    festo->lampRed.switchOff();
    festo->lampYellow.switchOff();
    festo->lampGreen.switchOn();
    consoleLogBarrierState(festo);
    festo->updateActuators();
    sleepForMS(WAIT);

    festo->updateSensors();
    festo->lampRed.switchOff();
    festo->lampYellow.switchOn();
    festo->lampGreen.switchOff();
    consoleLogBarrierState(festo);
    festo->updateActuators();
    sleepForMS(WAIT);

}


void consoleLogBarrierState(FestoTransferSystem * festo){

    cout << "Beginn:";
    if (festo->lightbarrierBegin.isOpen()) {cout << "0" << endl;}
    else {cout << 1 << endl;}

    cout << "End:";
    if (festo->lightbarrierEnd.isOpen()) {cout << "0" << endl;}
    else {cout << 1 << endl;}

    cout << "Height:";
    if (festo->lightbarrierHeightSensor.isOpen()) {cout << "0" << endl;}
    else {cout << 1 << endl;}

    cout << "Seperator:";
    if (festo->lightbarrierFeedSeparator.isOpen()) {cout << "0" << endl;}
    else {cout << 1 << endl;}

    //cout << "Beginn:" << festo->lightbarrierBegin.getState() << endl;
    // cout << "End:" << festo->lightbarrierEnd.getState() << endl;
    //cout << "Height:" << festo->lightbarrierHeightSensor.getState() << endl;
    //cout << "BufferFull:" << festo->lightbarrierBufferFull.getState() << endl;
    //cout << "Separator:" << festo->lightbarrierFeedSeparator.getState() << endl;

}

void start(FestoTransferSystem *festo){
    if (festo->pushbuttonStart.isPressed()) {
        festo->ledStart.switchOn();
    }
    else {
        festo->ledStart.switchOff();
    }
    //festo->ledStart.setState(festo->pushbuttonStart.getState());

    if(festo->pushbuttonStart.isPressed() && festo->lightbarrierEnd.isClosed()){
        festo->drive.setSpeed(CONVEYERBELT_RIGHT_FAST);
    }
    else {
        festo->drive.setSpeed(CONVEYERBELT_STOP);
    }
}

void stop(FestoTransferSystem *festo){
    if(festo->pushbuttonStop.isReleased()){
        festo->feedSeparator.open();
        festo->ledReset.switchOn();
    }
    else {
        festo->feedSeparator.close();
        festo->ledReset.switchOff();
    }
}

void q1(FestoTransferSystem *festo){
    if (festo->lightbarrierBegin.isOpen()) {
        festo->ledQ1.switchOn();
    }
    else {
        festo->ledQ1.switchOff();
    }
    //festo->ledQ1.setState(festo->lightbarrierBegin.getState());
}

void q2(FestoTransferSystem *festo){
    if (festo->lightbarrierHeightSensor.isOpen()) {
        festo->ledQ2.switchOff();
    }
    else {
        festo->ledQ2.switchOn();
    }
    //festo->ledQ2.setState(!festo->lightbarrierHeightSensor.getState());
}

void emergency(FestoTransferSystem *festo, bool * run){
    if(festo->switchEmergency.isPressed()){
        festo->drive.setSpeed(CONVEYERBELT_STOP);
        festo->feedSeparator.close();
        festo->lampRed.switchOff();
        festo->lampYellow.switchOff();
        festo->lampGreen.switchOff();
        festo->ledQ1.switchOff();
        festo->ledQ2.switchOff();
        festo->ledStart.switchOff();
        festo->ledReset.switchOff();
        *run = false;
    }
}