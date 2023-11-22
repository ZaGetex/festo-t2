//
// Created by nikla on 21.11.2023.
//

#include "FSM.h"
#include <iostream>
using namespace std;

FSM::FSM() {
    this->running = true;
    this->state = States::ANFANGSZUSTAND;
}

bool FSM::evalTransition() {

    States nextState;
    switch (state) {
        case States::ANFANGSZUSTAND:
            if(festo.pushbuttonStart.isPressed()){
                nextState = States::BETRIEBSBEREIT;
                cout << "Betriebsbereit" << endl;
            }
            break;
        case States::BETRIEBSBEREIT:
            if(festo.pushbuttonStart.isPressed()){
                nextState = States::ANFANGSZUSTAND;
                cout << "Anfangszustand" << endl;
            }
            break;
        default:
            return false;
    }
}

void FSM::evalStates() {

    switch (state) {
        case States::ANFANGSZUSTAND:
            // 1.
            festo.drive.setSpeed(CONVEYERBELT_STOP); //TODO: Zu Motorwrapper ändern
            festo.feedSeparator.close();
            festo.lampRed.switchOff();
            festo.lampYellow.switchOff();
            festo.lampGreen.switchOff();
            festo.ledStart.switchOn();

        case States::BETRIEBSBEREIT:
            // 2.
            festo.drive.setSpeed(CONVEYERBELT_STOP); //TODO: Zu Motorwrapper ändern
            festo.lampGreen.switchOn();

            // 3.
            if (festo.lightbarrierBegin.isOpen()) {
                festo.lampGreen.switchOff();
                festo.lampYellow.switchOn();
                festo.drive.setSpeed(CONVEYERBELT_RIGHT_SLOW); //TODO: Zu Motorwrapper ändern
            }

            // 4.
            bool heightOk;
            if (festo.lightbarrierHeightSensor.isOpen()) {
                festo.lampYellow.switchOff();
                festo.lampRed.switchOn();
                festo.drive.setSpeed(CONVEYERBELT_STOP); //TODO: Zu Motorwrapper ändern
            }
            //5.
            if (festo.heightcheck.isHeightCorrect()) {
                heightOk = true;
                if (festo.lightbarrierBegin.isClosed() && festo.heightcheck.isHeightCorrect()) {
                    festo.lampRed.switchOn();
                    festo.lampYellow.switchOn();
                    festo.ledQ1.switchOn(); //TODO: Ausmachen wenn neues Werkstück
                    festo.drive.setSpeed(CONVEYERBELT_LEFT_FAST); //TODO: Zu Motorwrapper ändern
                    cout << "Höhe ist OK" << endl;
                }
                    //8:
                else if (!festo.heightcheck.isHeightCorrect() &&
                         festo.lightbarrierHeightSensor.isOpen()) { //Höhe nicht ok
                    festo.drive.setSpeed(CONVEYERBELT_RIGHT_FAST); //TODO: Motor Wrapper
                    festo.lampYellow.switchOn();
                    festo.lampGreen.switchOn();
                    festo.ledQ1.switchOff();
                    cout << "Höhe ist nicht OK" << endl;

                }
            }

            //6.
            if (festo.lightbarrierBegin.isOpen() && heightOk) {
                heightOk = false;

                festo.drive.setSpeed(CONVEYERBELT_STOP); //TODO: Motor Wrapper
                festo.lampYellow.blink();
                festo.lampRed.switchOn();
                festo.ledReset.switchOn();
            }

            //7.
            if (festo.pushbuttonReset.isPressed()) {
                festo.drive.setSpeed(CONVEYERBELT_RIGHT_FAST); //TODO: Motor Wrapper
                festo.lampYellow.switchOn();
                festo.lampRed.switchOff();
                festo.ledReset.switchOff();
                //TODO: NUR BIS ZUR WEICHE TRANSPORTIEREN
            }

            //9.
            if (festo.lightbarrierFeedSeparator.isOpen()) {
                festo.drive.setSpeed(CONVEYERBELT_STOP); //TODO: Motor Wrapper
                festo.lampRed.switchOn();
                festo.lampYellow.switchOff();
                festo.lampGreen.switchOff();
                //10.
                if (!festo.metalcheck.isMetalDetected()) //nicht metallisch
                {
                    festo.drive.setSpeed(CONVEYERBELT_RIGHT_FAST); //TODO: Motor Wrapper
                    festo.lampRed.switchOff();
                    festo.lampYellow.switchOn();
                    festo.feedSeparator.open();
                    festo.ledQ2.switchOn();

                }
                    //11.
                else { //metallisch
                    festo.drive.setSpeed(CONVEYERBELT_RIGHT_FAST); //TODO: Motor Wrapper
                    festo.ledQ2.switchOff();
                    festo.feedSeparator.close();
                    festo.lampYellow.switchOn();
                }
            }

            //12.
            bool rutsche; //true = frei; false = besetzt

            if (festo.lightbarrierEnd.isOpen()) { //rutsche besetzt
                festo.drive.setSpeed(CONVEYERBELT_STOP); //TODO: Motor Wrapper
                festo.lampRed.switchOn();
                festo.lampYellow.blink();
                festo.lampGreen.switchOff();
                rutsche = false;
            }
            //13.
            if (festo.lightbarrierEnd.isClosed() && !rutsche) { //rutsche und Lichtschranke frei
                festo.drive.setSpeed(CONVEYERBELT_STOP); //TODO: Motor Wrapper
                festo.feedSeparator.close();
                festo.lampRed.switchOn();
                festo.lampYellow.switchOff();
                festo.lampGreen.switchOn();
                rutsche = true;

            }
            //14.
            bool auslauf; //true = frei ; false=besetzt

            if (festo.lightbarrierBufferFull.isOpen()) { //auslauf besetzt
                festo.drive.setSpeed(CONVEYERBELT_STOP); //TODO: Motor Wrapper
                festo.feedSeparator.close();
                festo.ledQ2.switchOff();
                festo.lampRed.switchOn();
                festo.lampYellow.switchOff();
                festo.lampGreen.switchOn();
                auslauf = false;
            }
            //15.
            if (festo.lightbarrierBufferFull.isClosed() && !auslauf) { //auslauf frei
                festo.drive.setSpeed(CONVEYERBELT_STOP); //TODO: Motor Wrapper
                festo.lampRed.switchOff();
                festo.lampYellow.switchOn();
                festo.lampGreen.switchOn();
                auslauf = true;
            }


            break;
        default:
            break;
    }

}

bool FSM::getRunning() const
{
    return this->running;
}