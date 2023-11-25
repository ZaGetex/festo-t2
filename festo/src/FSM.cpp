//
// Created by nikla on 21.11.2023.
//

#include "FSM.h"
#include <iostream>
#include "Motor.h"

using namespace std;

FSM::FSM() {
    this->running = true;
    this->state = States::ANFANGSZUSTAND;
}

bool FSM::evalTransition() {

    States nextState = state; // Standardwert setzen

    switch (state) {
        case States::ANFANGSZUSTAND:
            if(festo.pushbuttonStart.isPressed()){
                nextState = States::BETRIEBSBEREIT;
                cout << "Betriebsbereit" << endl;

            }
            state = nextState;
            break;
        case States::BETRIEBSBEREIT:
            if(festo.pushbuttonStart.isPressed()){
                nextState = States::ANFANGSZUSTAND;
                cout << "Anfangszustand" << endl;

            }
            state = nextState;
            break;
        default:
            return false; // Hier könntest du return false; hinzufügen, wenn das gewünscht ist.
    }

    // Hier könntest du nextState zurückgeben oder weitere Logik implementieren.
    return true; // Oder einen anderen sinnvollen Rückgabewert.
}



void FSM::evalStates() {

    switch (state) {
        case States::ANFANGSZUSTAND:
            // 1.
            Motor::motorStop();
            festo.feedSeparator.close();
            festo.lampRed.switchOff();
            festo.lampYellow.switchOff();
            festo.lampGreen.switchOff();
            festo.ledStart.switchOn();

        case States::BETRIEBSBEREIT:
            // 2.
            Motor::motorStop();
            festo.lampGreen.switchOn();

            // 3.
            if (festo.lightbarrierBegin.isOpen()) {
                festo.lampGreen.switchOff();
                festo.lampYellow.switchOn();
                Motor::motorSlowRight();
            }

            // 4.
            bool heightOk;
            if (festo.lightbarrierHeightSensor.isOpen()) {
                festo.lampYellow.switchOff();
                festo.lampRed.switchOn();
                Motor::motorStop();
            }
            //5.
            if (festo.heightcheck.isHeightCorrect()) {
                heightOk = true;
                if (festo.lightbarrierBegin.isClosed() && festo.heightcheck.isHeightCorrect()) {
                    festo.lampRed.switchOn();
                    festo.lampYellow.switchOn();
                    festo.ledQ1.switchOn(); //TODO: Ausmachen wenn neues Werkstück
                    Motor::motorFastLeft();
                    cout << "Höhe ist OK" << endl;
                }
                    //8:
                else if (!festo.heightcheck.isHeightCorrect() &&
                         festo.lightbarrierHeightSensor.isOpen()) { //Höhe nicht ok
                    Motor::motorFastRight();
                    festo.lampYellow.switchOn();
                    festo.lampGreen.switchOn();
                    festo.ledQ1.switchOff();
                    cout << "Höhe ist nicht OK" << endl;

                }
            }

            //6.
            if (festo.lightbarrierBegin.isOpen() && heightOk) {
                heightOk = false;

                Motor::motorStop();
                festo.lampYellow.blink();
                festo.lampRed.switchOn();
                festo.ledReset.switchOn();
            }

            //7.
            if (festo.pushbuttonReset.isPressed()) {
                Motor::motorFastRight();
                festo.lampYellow.switchOn();
                festo.lampRed.switchOff();
                festo.ledReset.switchOff();
                //TODO: NUR BIS ZUR WEICHE TRANSPORTIEREN
            }

            //9.
            if (festo.lightbarrierFeedSeparator.isOpen()) {
                Motor::motorStop();
                festo.lampRed.switchOn();
                festo.lampYellow.switchOff();
                festo.lampGreen.switchOff();
                //10.
                if (!festo.metalcheck.isMetalDetected()) //nicht metallisch
                {
                    Motor::motorFastRight();
                    festo.lampRed.switchOff();
                    festo.lampYellow.switchOn();
                    festo.feedSeparator.open();
                    festo.ledQ2.switchOn();

                }
                    //11.
                else { //metallisch
                    Motor::motorFastRight();
                    festo.ledQ2.switchOff();
                    festo.feedSeparator.close();
                    festo.lampYellow.switchOn();
                }
            }

            //12.
            bool rutsche; //true = frei; false = besetzt

            if (festo.lightbarrierEnd.isOpen()) { //rutsche besetzt
                Motor::motorStop();
                festo.lampRed.switchOn();
                festo.lampYellow.blink();
                festo.lampGreen.switchOff();
                rutsche = false;
            }
            //13.
            if (festo.lightbarrierEnd.isClosed() && !rutsche) { //rutsche und Lichtschranke frei
                Motor::motorStop();
                festo.feedSeparator.close();
                festo.lampRed.switchOn();
                festo.lampYellow.switchOff();
                festo.lampGreen.switchOn();
                rutsche = true;

            }
            //14.
            bool auslauf; //true = frei ; false=besetzt

            if (festo.lightbarrierBufferFull.isOpen()) { //auslauf besetzt
                Motor::motorStop();
                festo.feedSeparator.close();
                festo.ledQ2.switchOff();
                festo.lampRed.switchOn();
                festo.lampYellow.switchOff();
                festo.lampGreen.switchOn();
                auslauf = false;
            }
            //15.
            if (festo.lightbarrierBufferFull.isClosed() && !auslauf) { //auslauf frei
                Motor::motorStop();
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

//bool FSM::getRunning() const
//{
   // return this->running;
//}