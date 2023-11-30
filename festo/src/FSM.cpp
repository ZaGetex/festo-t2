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
                nextState = States::TRANSPORT;
                cout << "3" << endl;
            }
            break;

        case States::TRANSPORT: //3
            if (festo.lightbarrierHeightSensor.isOpen()) {
                nextState = States::HOEHENMESSUNG;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 4" << endl;
            }
            break;

        case States::HOEHENMESSUNG: //4
            if(festo.heightcheck.isHeightCorrect()){
                nextState = States::HOEHE_OK;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 5" << endl;
            }
            else if(!festo.heightcheck.isHeightCorrect()){
                nextState = States::HOEHE_NOT_OK;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 8" << endl;
            }
            break;

        case States::HOEHE_OK: //5
            if(festo.lightbarrierBegin.isOpen()){
                nextState = States::DREHEN;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 6" << endl;
            }
            break;

        case States::DREHEN: //6
            if(festo.pushbuttonReset.isPressed()){
                nextState = States::TRANSPORT_GEDREHT;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 7" << endl;
            }
            break;

        case States::TRANSPORT_GEDREHT: //7
            if(festo.lightbarrierFeedSeparator.isOpen()){
                nextState = States::WEICHE;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 9" << endl;
            }
            break;

        case States::HOEHE_NOT_OK: //8
            if(festo.lightbarrierFeedSeparator.isOpen()){
                nextState = States::WEICHE;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 9" << endl;
            }
            break;

        case States::WEICHE: //9
            if(!festo.metalcheck.isMetalDetected()){
                nextState = States::NOT_METALLIC;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 10" << endl;
            }
            else if (festo.metalcheck.isMetalDetected()){
                nextState = States::METALLIC;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 11" << endl;
            }
            break;

        case States::NOT_METALLIC: //10
            if(festo.lightbarrierEnd.isOpen()){
                nextState = States::END;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 14" << endl;
            }
            break;

        case States::METALLIC: //11
            if(festo.lightbarrierBufferFull.isOpen()) {
                nextState = States::BUFFER;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 12" << endl;
            }
            break;

        case States::BUFFER: //12
            if(festo.lightbarrierBufferFull.isClosed()){
                nextState = States::BUFFER_FREE;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 13" << endl;
            }
            break;

        case States::BUFFER_FREE: //13
            if (festo.lightbarrierBegin.isOpen()) {
                nextState = States::TRANSPORT;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 3" << endl;
            }
            else if (festo.pushbuttonStart.isPressEvent()) {
                nextState = States::ANFANGSZUSTAND;
                if (DEBUG_TRANSITIONS) cout << "Transition zum Anfangszustand" << endl;
            }
            break;

        case States::END: //14
            if(festo.lightbarrierBufferFull.isClosed()){
                nextState = States::END_FREE;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 15" << endl;
            }
            break;

        case States::END_FREE: //15
            if (festo.lightbarrierBegin.isOpen()) {
                nextState = States::TRANSPORT;
                if (DEBUG_TRANSITIONS) cout << "Transition zu 3" << endl;
            }
            else if (festo.pushbuttonStart.isPressEvent()) {
                nextState = States::ANFANGSZUSTAND;
                if (DEBUG_TRANSITIONS) cout << "Transition zum Anfangszustand" << endl;
            }

            break;

        default:
            return false;
    }
    state = nextState;

    return true;
}

void FSM::evalStates(FestoTransferSystem& festo) {
    emergency(festo);
    if(running) {
        switch (state) {
            case States::ANFANGSZUSTAND:
                // 1.
                if (DEBUG_STATES) cout << "State Anfangszustand" << endl;
                motor.motorStop(festo);
                festo.feedSeparator.close();
                festo.lampRed.switchOff();
                festo.lampYellow.switchOff();
                festo.lampGreen.switchOff();
                festo.ledStart.switchOn();
                break;

            case States::BETRIEBSBEREIT:
                if (DEBUG_STATES) cout << "State Betriebszustand" << endl;
                // 2.
                motor.motorStop(festo);
                festo.lampGreen.switchOn();
                break;

            case States::TRANSPORT:
                // 3.
                if (DEBUG_STATES) cout << "State 3" << endl;
                festo.lampGreen.switchOff();
                festo.lampYellow.switchOn();
                motor.motorSlowRight(festo);

                break;

            case States::HOEHENMESSUNG:
                // 4.
                if (DEBUG_STATES) cout << "State 4" << endl;
                motor.motorStop(festo);
                festo.lampYellow.switchOff();
                festo.lampRed.switchOn();
                motor.motorStop(festo);
                break;

            case States::HOEHE_OK:
                //5.
                if (DEBUG_STATES) cout << "State 5" << endl;
                festo.lampRed.switchOn();
                festo.lampYellow.switchOn();
                festo.ledQ1.switchOn();
                motor.motorFastLeft(festo);
                cout << "Höhe ist OK" << endl;
                break;

            case States::HOEHE_NOT_OK:
                //8.
                if (DEBUG_STATES) cout << "State 8" << endl;
                motor.motorFastRight(festo);
                festo.lampYellow.switchOn();
                festo.lampGreen.switchOn();
                festo.ledQ1.switchOff();
                cout << "Höhe ist nicht OK" << endl;
                break;


            case States::DREHEN:
                //6.
                if (DEBUG_STATES) cout << "State 6" << endl;
                motor.motorStop(festo);
                festo.lampYellow.blink();
                festo.lampRed.switchOn();
                festo.ledReset.switchOn();

                break;

            case States::TRANSPORT_GEDREHT:
                //7.
                if (DEBUG_STATES) cout << "State 7" << endl;
                motor.motorFastRight(festo);
                festo.lampYellow.switchOn();
                festo.lampRed.switchOff();
                festo.ledReset.switchOff();
                festo.ledQ1.switchOff();
                break;

            case States::WEICHE:
                //9.
                if (DEBUG_STATES) cout << "State 9" << endl;
                motor.motorStop(festo);
                festo.lampRed.switchOn();
                festo.lampYellow.switchOff();
                festo.lampGreen.switchOff();
                break;

            case States::NOT_METALLIC:
                //10.
                if (DEBUG_STATES) cout << "State 10" << endl;
                cout << "Metal not detected!" << endl;
                motor.motorFastRight(festo);
                festo.lampRed.switchOff();
                festo.lampYellow.switchOn();
                festo.feedSeparator.open();
                festo.ledQ2.switchOn();
                break;

            case States::METALLIC:
                //11.
                if (DEBUG_STATES) cout << "State 11" << endl;
                cout << "Metal detected!" << endl;
                motor.motorFastRight(festo);
                festo.ledQ2.switchOff();
                festo.feedSeparator.close();
                festo.lampYellow.switchOn();
                break;


            case States::BUFFER:
                //12.
                if (DEBUG_STATES) cout << "State 12" << endl;
                motor.motorStop(festo);
                festo.lampRed.switchOn();
                festo.lampYellow.blink();
                festo.lampGreen.switchOff();
                break;

            case States::BUFFER_FREE:
                //13.
                if (DEBUG_STATES) cout << "State 13" << endl;
                motor.motorStop(festo);
                festo.feedSeparator.close();
                festo.lampRed.switchOn();
                festo.lampYellow.switchOff();
                festo.lampGreen.switchOn();
                break;

            case States::END:
                //14.
                if (DEBUG_STATES) cout << "State 14" << endl;
                motor.motorStop(festo);
                festo.feedSeparator.close();
                festo.ledQ2.switchOff();
                festo.lampRed.switchOn();
                festo.lampYellow.switchOff();
                festo.lampGreen.switchOn();
                break;

            case States::END_FREE:
                //15.
                if (DEBUG_STATES) cout << "State 15" << endl;
                motor.motorStop(festo);
                festo.lampRed.switchOff();
                festo.lampYellow.switchOn();
                festo.lampGreen.switchOn();
                break;

            default:
                break;
        }
    }
}


void FSM::emergency(FestoTransferSystem &festo) {
    if(festo.switchEmergency.isPressed()){
        motor.motorStop(festo);
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

bool FSM::getRunning() const {return running;}
