//
// Created by nikla on 21.11.2023.
//

#include "FSM.h"
#include <iostream>
#include "Motor.h"

using namespace std;

bool DEBUG_TRANSITIONS = true;
bool DEBUG_STATES  = true;

FSM::FSM() {
    this->running = true;
    this->state = States::ANFANGSZUSTAND;
}

bool FSM::evalTransition(FestoTransferSystem& festo) {

    States nextState = state;

    switch (state) {
        case States::ANFANGSZUSTAND:
            if(festo.pushbuttonStart.isPressEvent()){
                nextState = States::BETRIEBSBEREIT;
                if (DEBUG_TRANSITIONS) cout << "Transition zu Betriebsbereit" << endl;
            }
            break;

        case States::BETRIEBSBEREIT:
            if(festo.pushbuttonStart.isPressEvent()){
                nextState = States::ANFANGSZUSTAND;
                if (DEBUG_TRANSITIONS) cout << "Transition zu Anfangszustand" << endl;
            }
            else if(festo.lightbarrierBegin.isOpen()){
                nextState = States::DREI;
                cout << "3" << endl;
            }
            break;

        case States::DREI:
            if (festo.lightbarrierHeightSensor.isOpen()) {
                nextState = States::VIER;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 4" << endl;
            }


        case States::VIER:
            if(festo.heightcheck.isHeightCorrect()){
                nextState = States::FUENFZEHN;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 15" << endl;
            }
            else if(!festo.heightcheck.isHeightCorrect()){
                nextState = States::ACHT;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 8" << endl;
            }
            break;

        case States::FUENF:
            if(festo.lightbarrierBegin.isOpen()){
                nextState = States::SECHS;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 6" << endl;
            }
            break;

        case States::SECHS:
            if(festo.pushbuttonReset.isPressed()){
                nextState = States::SIEBEN;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 7" << endl;
            }
            break;

        case States::SIEBEN:
            if(festo.lightbarrierFeedSeparator.isOpen()){
                nextState = States::NEUN;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 9" << endl;
            }
            break;

        case States::ACHT:
            if(festo.pushbuttonStart.isPressEvent()){
                nextState = States::BETRIEBSBEREIT;
                if (DEBUG_TRANSITIONS) cout << "Transition zu Betriebsbereit" << endl;
            }
            break;

        case States::NEUN:
            if(!festo.metalcheck.isMetalDetected()){
                nextState = States::ZEHN;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 10" << endl;
            }
            else if (festo.metalcheck.isMetalDetected()){
                nextState = States::ELF;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 11" << endl;
            }
            break;

        case States::ZEHN:
            if(festo.lightbarrierBufferFull.isOpen()) {
                nextState = States::VIERZEHN;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 14" << endl;
            }
            break;

        case States::ELF:
            if(festo.lightbarrierEnd.isOpen()){
                nextState = States::ZWOELF;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 12" << endl;
            }
            break;

        case States::ZWOELF:
            if(festo.lightbarrierEnd.isClosed()){ //TODO: RUTSCHE LICHTSENSOR??
                nextState = States::DREIZEHN;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 13" << endl;
            }
            break;

        case States::DREIZEHN:
                nextState = States::ANFANGSZUSTAND;
            if (DEBUG_TRANSITIONS) cout << "Transition zu Anfangszustand" << endl;
            break;

        case States::VIERZEHN:
            if(festo.lightbarrierBufferFull.isClosed()){
                nextState = States::FUENFZEHN;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 15" << endl;
            }
            break;

        case States::FUENFZEHN:
                nextState = States::ANFANGSZUSTAND;
            if (DEBUG_TRANSITIONS) cout << "Transition zu Anfangszustand" << endl;
            break;

        default:
            return false;
    }
    state = nextState;

    return true;
}

void FSM::evalStates(FestoTransferSystem& festo) {
    emergency(festo);
    switch (state) {
        case States::ANFANGSZUSTAND:
            // 1.
            if (DEBUG_STATES) cout << "State Anfangszustand" << endl;
            Motor::motorStop(festo);
            festo.feedSeparator.close();
            festo.lampRed.switchOff();
            festo.lampYellow.switchOff();
            festo.lampGreen.switchOff();
            festo.ledStart.switchOn();
            break;

        case States::BETRIEBSBEREIT:
            if (DEBUG_STATES) cout << "State Betriebszustand" << endl;
            Motor::motorStop(festo);
            // 2.
            Motor::motorStop(festo);
            festo.lampGreen.switchOn();
            break;

        case States::DREI:
            // 3.
                festo.lampGreen.switchOff();
                festo.lampYellow.switchOn();
                Motor::motorSlowRight(festo);

            break;

        case States::VIER:
            // 4.
            if (DEBUG_STATES) cout << "State 4" << endl;
            Motor::motorStop(festo);
            festo.lampYellow.switchOff();
            festo.lampRed.switchOn();
            Motor::motorStop(festo);
            break;

        case States::FUENF:
            //5.
            if (DEBUG_STATES) cout << "State 5" << endl;
            festo.lampRed.switchOn();
            festo.lampYellow.switchOn();
            festo.ledQ1.switchOn(); //TODO: Ausmachen wenn neues Werkstück
            Motor::motorFastLeft(festo);
            cout << "Höhe ist OK" << endl;
            break;

        case States::ACHT:
            //8.
            if (DEBUG_STATES) cout << "State 8" << endl;
            Motor::motorFastRight(festo);
            festo.lampYellow.switchOn();
            festo.lampGreen.switchOn();
            festo.ledQ1.switchOff();
            cout << "Höhe ist nicht OK" << endl;
            break;


        case States::SECHS:
            //6.
            if (DEBUG_STATES) cout << "State 6" << endl;
            Motor::motorStop(festo);
            festo.lampYellow.blink();
            festo.lampRed.switchOn();
            festo.ledReset.switchOn();
            break;

        case States::SIEBEN:
            //7.
            if (DEBUG_STATES) cout << "State 7" << endl;
            Motor::motorFastRight(festo);
            festo.lampYellow.switchOn();
            festo.lampRed.switchOff();
            festo.ledReset.switchOff();
            //TODO: NUR BIS ZUR WEICHE TRANSPORTIEREN
            break;

        case States::NEUN:
            //9.
            if (DEBUG_STATES) cout << "State 9" << endl;
            Motor::motorStop(festo);
            festo.lampRed.switchOn();
            festo.lampYellow.switchOff();
            festo.lampGreen.switchOff();
            break;

        case States::ZEHN:
                //10.
            if (DEBUG_STATES) cout << "State 10" << endl;
            Motor::motorFastRight(festo);
                festo.lampRed.switchOff();
                festo.lampYellow.switchOn();
                festo.feedSeparator.open();
                festo.ledQ2.switchOn();
                break;

        case States::ELF:
            //11.
            if (DEBUG_STATES) cout << "State 11" << endl;
            Motor::motorFastRight(festo);
            festo.ledQ2.switchOff();
            festo.feedSeparator.close();
            festo.lampYellow.switchOn();
            break;


        case States::ZWOELF:
            //12.
            if (DEBUG_STATES) cout << "State 12" << endl;
            Motor::motorStop(festo);
            festo.lampRed.switchOn();
            festo.lampYellow.blink();
            festo.lampGreen.switchOff();
            break;

        case States::DREIZEHN:
            //13.
            if (DEBUG_STATES) cout << "State 13" << endl;
            Motor::motorStop(festo);
            festo.feedSeparator.close();
            festo.lampRed.switchOn();
            festo.lampYellow.switchOff();
            festo.lampGreen.switchOn();
            break;

        case States::VIERZEHN:
            //14.
            if (DEBUG_STATES) cout << "State 14" << endl;
            Motor::motorStop(festo);
            festo.feedSeparator.close();
            festo.ledQ2.switchOff();
            festo.lampRed.switchOn();
            festo.lampYellow.switchOff();
            festo.lampGreen.switchOn();
            break;

        case States::FUENFZEHN:
            //15.
            if (DEBUG_STATES) cout << "State 15" << endl;
            Motor::motorStop(festo);
            festo.lampRed.switchOff();
            festo.lampYellow.switchOn();
            festo.lampGreen.switchOn();
            break;

        default:
            break;
    }
}

void FSM::emergency(FestoTransferSystem &festo) {
    if(festo.switchEmergency.isPressed()){
        Motor::motorStop(festo);
        festo.feedSeparator.close();
        festo.lampRed.switchOff();
        festo.lampYellow.switchOff();
        festo.lampGreen.switchOff();
        festo.ledQ1.switchOff();
        festo.ledQ2.switchOff();
        festo.ledStart.switchOff();
        festo.ledReset.switchOff();
        cout << "Emergency Triggered" << endl;
        running = false;
    }
}

bool FSM::isRunning() const {return running;}
