/**
 * @author Niklas Dathe
 * @author Florian Czorniuk
 * @date   21.11.2023
 */

#include <iostream>
#include "TimeHelper.h"
#include "FestoTransferSystem.h"
#include "FSM.h"

using namespace std;

#define WAIT 1000
#define LAP 2

void ampelschaltung(FestoTransferSystem *);
void emergency(FestoTransferSystem *,bool *);



int main() {
    FestoTransferSystem festo;
    FSM fsm;

    //Boot
    for (int i = 0; i < LAP; ++i) {
        ampelschaltung(&festo);
    }

    //Main Code
    while(fsm.getRunning()) {
        festo.updateSensors();

        fsm.evalStates();
        fsm.evalTransition();

        emergency(&festo, reinterpret_cast<bool *>(fsm.getRunning())); //E-Break

        festo.updateActuators();
    }
    return 0;

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


void ampelschaltung(FestoTransferSystem *festo){
    //new
    festo->updateSensors();
    festo->lampRed.switchOn();
    festo->lampYellow.switchOff();
    festo->lampGreen.switchOff();
    festo->updateActuators();
    sleepForMS(WAIT);

    festo->updateSensors();
    festo->lampRed.switchOn();
    festo->lampYellow.switchOn();
    festo->lampGreen.switchOff();
    festo->updateActuators();
    sleepForMS(WAIT);

    festo->updateSensors();
    festo->lampRed.switchOff();
    festo->lampYellow.switchOff();
    festo->lampGreen.switchOn();
    festo->updateActuators();
    sleepForMS(WAIT);

    festo->updateSensors();
    festo->lampRed.switchOff();
    festo->lampYellow.switchOn();
    festo->lampGreen.switchOff();
    festo->updateActuators();
    sleepForMS(WAIT);

}

