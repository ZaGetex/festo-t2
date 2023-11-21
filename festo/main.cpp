/**
 * @author Niklas Dathe
 * @author Florian Czorniuk
 * @date   21.11.2023
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

void anfangszustand(FestoTransferSystem *, bool *);
void transportieren(FestoTransferSystem *, bool *);
void hoehenmessung(FestoTransferSystem *, bool *);
void anfang(FestoTransferSystem *, bool *);
void reset(FestoTransferSystem *);
void weiche(FestoTransferSystem *);
void rutsche(FestoTransferSystem *);
void auslauf(FestoTransferSystem *);

int main() {
    FestoTransferSystem festo;

    //Boot
    for (int i = 0; i < LAP; ++i) {
        ampelschaltung(&festo);
    }
    bool height = false;
    bool betriebsbereit = false;
    bool run = true;
    while(run) {
        festo.updateSensors();

        anfangszustand(&festo, &betriebsbereit);
        transportieren(&festo, &betriebsbereit);
        hoehenmessung(&festo, &height);
        anfang(&festo, &height);
        weiche(&festo);
        rutsche(&festo);
        auslauf(&festo);
        //start(&festo);
        //stop(&festo);
        //q1(&festo);
        //q2(&festo);

        emergency(&festo, &run);
        festo.updateActuators();
    }
    return 0;
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

void anfangszustand(FestoTransferSystem *festo, bool * betriebsbereit){
    if (festo->pushbuttonStart.isPressed() && *betriebsbereit) {
        cout << "Anfangszustand" << endl;
        *betriebsbereit = false;
        festo->ledStart.switchOn();
        festo->lampGreen.switchOff();
        festo->lampYellow.switchOff();
        festo->lampRed.switchOff();

    }
    else if (festo->pushbuttonStart.isPressed() && !*betriebsbereit) {
        cout << "Betriebsbereit" << endl;
        *betriebsbereit = true;
        festo->lampGreen.switchOn();

    }


}

void transportieren(FestoTransferSystem *festo, bool * betriebsbereit) {
    if (betriebsbereit && festo->lightbarrierBegin.isOpen()) {
        festo->drive.setSpeed(CONVEYERBELT_RIGHT_SLOW);
        festo->lampGreen.switchOff();
        festo->lampYellow.switchOn();
    }

}

void hoehenmessung(FestoTransferSystem *festo, bool * height){
    if (festo->lightbarrierHeightSensor.isOpen()){
        festo->drive.setSpeed(CONVEYERBELT_STOP);
        festo->lampRed.switchOn();
        festo->lampYellow.switchOff();

    }
    if (festo->heightcheck.isHeightCorrect() && festo->lightbarrierHeightSensor.isOpen()){
        festo->drive.setSpeed(CONVEYERBELT_LEFT_FAST);
        festo->lampRed.switchOn();
        festo->lampYellow.switchOn();
        *height = true;

        festo->ledQ1.switchOn();
        if (festo->lightbarrierBegin.isOpen()) {
            festo->ledQ1.switchOff();
        }
        cout << "Hoehenmessung: " << festo->heightcheck.isHeightCorrect() << endl; //Gibt nur einen bool aus
    }
    else if (!festo->heightcheck.isHeightCorrect() && festo->lightbarrierHeightSensor.isOpen()){
        festo->drive.setSpeed(CONVEYERBELT_RIGHT_FAST);
        festo->lampGreen.switchOn();
        festo->lampYellow.switchOn();
        festo->lampRed.switchOff();
        festo->ledQ1.switchOff();

        cout << "Hoehenmessung: " << festo->heightcheck.isHeightCorrect() << endl; //Gibt nur einen bool aus

    }

}

void anfang(FestoTransferSystem *festo, bool * height){
    if (festo->lightbarrierBegin.isOpen() && height){
        *height = false;

        festo->drive.setSpeed(CONVEYERBELT_STOP);
        festo->lampYellow.blink();
        festo->lampRed.switchOn();
        festo->ledReset.switchOn();


    }

}

void reset(FestoTransferSystem *festo){
    if (festo->pushbuttonReset.isPressed()){
        festo->drive.setSpeed(CONVEYERBELT_RIGHT_FAST);
        festo->lampYellow.switchOn();
        festo->lampRed.switchOff();
        festo->ledReset.switchOff();
    }
}

void weiche(FestoTransferSystem *festo){
    if (festo->lightbarrierFeedSeparator.isOpen()){
        festo->drive.setSpeed(CONVEYERBELT_STOP);
        festo->lampRed.switchOn();
        festo->lampYellow.switchOff();
        festo->lampGreen.switchOff();

        if (!festo->metalcheck.isMetalDetected()) //nicht metallisch
        {
            festo->drive.setSpeed(CONVEYERBELT_RIGHT_FAST);
            festo->lampRed.switchOff();
            festo->lampYellow.switchOn();
            festo->feedSeparator.open();
            festo->ledQ2.switchOn();

        }
        else { //metallisch
            festo->drive.setSpeed(CONVEYERBELT_RIGHT_FAST);
            festo->ledQ2.switchOff();
            festo->feedSeparator.close();
            festo->lampYellow.switchOn();
        }
    }
}

void rutsche(FestoTransferSystem *festo){
    if (festo->lightbarrierEnd.isOpen()){ //rutsche besetzt
        festo->drive.setSpeed(CONVEYERBELT_STOP);
        festo->lampRed.switchOn();
        festo->lampYellow.blink();
        festo->lampGreen.switchOff();
    }
    else { //rutsche frei
        festo->drive.setSpeed(CONVEYERBELT_STOP);
        festo->feedSeparator.close();
        festo->lampRed.switchOn();
        festo->lampYellow.switchOff();
        festo->lampGreen.switchOn();

    }
}


void auslauf(FestoTransferSystem *festo) {
    if (festo->lightbarrierBufferFull.isOpen()) { //auslauf besetzt
        festo->drive.setSpeed(CONVEYERBELT_STOP);
        festo->feedSeparator.close();
        festo->ledQ2.switchOff();
        festo->lampRed.switchOn();
        festo->lampYellow.switchOff();
        festo->lampGreen.switchOn();
    } else { //auslauf frei
        festo->drive.setSpeed(CONVEYERBELT_STOP);
        festo->lampRed.switchOff();
        festo->lampYellow.switchOn();
        festo->lampGreen.switchOn();
    }
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