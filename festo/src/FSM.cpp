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

bool FSM::evalTransition(FestoTransferSystem& festo) {

    States nextState = state;

    switch (state) {
        case States::ANFANGSZUSTAND:
            if(festo.pushbuttonStart.isPressEvent()){
                nextState = States::BETRIEBSBEREIT;
                cout << "Betriebsbereit" << endl;
            }
            break;

        case States::BETRIEBSBEREIT:
            if(festo.pushbuttonStart.isPressEvent()){
                nextState = States::ANFANGSZUSTAND;
                cout << "Anfangszustand" << endl;
            }
            else if(festo.lightbarrierHeightSensor.isOpen()){
                nextState = States::VIER;
                cout << "4" << endl;
            }
            break;


        case States::VIER:
            if(festo.heightcheck.isHeightCorrect()){
                nextState = States::FUENFZEHN;
                cout << "5" << endl;
            }
            else if(!festo.heightcheck.isHeightCorrect()){
                nextState = States::ACHT;
                cout << "8" << endl;
            }
            break;

        case States::FUENF:
            if(festo.lightbarrierBegin.isOpen()){
                nextState = States::SECHS;
                cout << "6" << endl;
            }
            break;

        case States::SECHS:
            if(festo.pushbuttonReset.isPressed()){
                nextState = States::SIEBEN;
                cout << "7" << endl;
            }
            break;

        case States::SIEBEN:
            if(festo.lightbarrierFeedSeparator.isOpen()){
                nextState = States::NEUN;
                cout << "9" << endl;
            }
            break;

        case States::ACHT:
            if(festo.pushbuttonStart.isPressEvent()){
                nextState = States::BETRIEBSBEREIT;
                cout << "Betriebsbereit" << endl;
            }
            break;

        case States::NEUN:
            if(!festo.metalcheck.isMetalDetected()){
                nextState = States::ZEHN;
                cout << "10" << endl;
            }
            else if (festo.metalcheck.isMetalDetected()){
                nextState = States::ELF;
                cout << "11" << endl;
            }
            break;

        case States::ZEHN:
            if(festo.lightbarrierBufferFull.isOpen()) {
                nextState = States::VIERZEHN;
                cout << "14" << endl;
            }
            break;

        case States::ELF:
            if(festo.lightbarrierEnd.isOpen()){
                nextState = States::ZWOELF;
                cout << "12" << endl;
            }
            break;

        case States::ZWOELF:
            if(festo.lightbarrierEnd.isClosed()){ //TODO: RUTSCHE LICHTSENSOR??
                nextState = States::DREIZEHN;
                cout << "13" << endl;
            }
            break;

        case States::DREIZEHN:
                nextState = States::ANFANGSZUSTAND;
                cout << "Anfangszustand" << endl;
            break;

        case States::VIERZEHN:
            if(festo.lightbarrierBufferFull.isClosed()){
                nextState = States::FUENFZEHN;
                cout << "15" << endl;
            }
            break;

        case States::FUENFZEHN:
                nextState = States::ANFANGSZUSTAND;
                cout << "Anfangszustand" << endl;
            break;

        default:
            return false;
    }
    state = nextState;
    return true;
}




void FSM::evalStates(FestoTransferSystem& festo) {

    switch (state) {
        case States::ANFANGSZUSTAND:
            // 1.
            Motor::motorStop(festo);
            festo.feedSeparator.close();
            festo.lampRed.switchOff();
            festo.lampYellow.switchOff();
            festo.lampGreen.switchOff();
            festo.ledStart.switchOn();
            break;

        case States::BETRIEBSBEREIT:
            // 2.
            Motor::motorStop(festo);
            festo.lampGreen.switchOn();

            // 3.
            if (festo.lightbarrierBegin.isOpen()) {
                festo.lampGreen.switchOff();
                festo.lampYellow.switchOn();
                Motor::motorSlowRight(festo);
            }
            else {
                festo.lampYellow.switchOff();
            }
            break;

        case States::VIER:
            // 4.
                festo.lampYellow.switchOff();
                festo.lampRed.switchOn();
                Motor::motorStop(festo);
            break;

        case States::FUENF:
            //5.
                    festo.lampRed.switchOn();
                     festo.lampYellow.switchOn();
                    festo.ledQ1.switchOn(); //TODO: Ausmachen wenn neues Werkstück
                    Motor::motorFastLeft(festo);
                    cout << "Höhe ist OK" << endl;
                break;

        case States::ACHT:
            //8.
                    Motor::motorFastRight(festo);
                    festo.lampYellow.switchOn();
                    festo.lampGreen.switchOn();
                    festo.ledQ1.switchOff();
                    cout << "Höhe ist nicht OK" << endl;
                    break;


        case States::SECHS:
            //6.
                Motor::motorStop(festo);
                festo.lampYellow.blink();
                festo.lampRed.switchOn();
                festo.ledReset.switchOn();
            break;

        case States::SIEBEN:
            //7.

                Motor::motorFastRight(festo);
                festo.lampYellow.switchOn();
                festo.lampRed.switchOff();
                festo.ledReset.switchOff();
                //TODO: NUR BIS ZUR WEICHE TRANSPORTIEREN
            break;

        case States::NEUN:
            //9.
                Motor::motorStop(festo);
                festo.lampRed.switchOn();
                festo.lampYellow.switchOff();
                festo.lampGreen.switchOff();
                break;

        case States::ZEHN:
                //10.
                    Motor::motorFastRight(festo);
                    festo.lampRed.switchOff();
                    festo.lampYellow.switchOn();
                    festo.feedSeparator.open();
                    festo.ledQ2.switchOn();
                break;

        case States::ELF:
            //11.
                    Motor::motorFastRight(festo);
                    festo.ledQ2.switchOff();
                    festo.feedSeparator.close();
                    festo.lampYellow.switchOn();
                break;


        case States::ZWOELF:
            //12.
                Motor::motorStop(festo);
                festo.lampRed.switchOn();
                festo.lampYellow.blink();
                festo.lampGreen.switchOff();
            break;

        case States::DREIZEHN:
            //13.
                Motor::motorStop(festo);
                festo.feedSeparator.close();
                festo.lampRed.switchOn();
                festo.lampYellow.switchOff();
                festo.lampGreen.switchOn();
            break;

        case States::VIERZEHN:
            //14.
                Motor::motorStop(festo);
                festo.feedSeparator.close();
                festo.ledQ2.switchOff();
                festo.lampRed.switchOn();
                festo.lampYellow.switchOff();
                festo.lampGreen.switchOn();
            break;

        case States::FUENFZEHN:
            //15.
                Motor::motorStop(festo);
                festo.lampRed.switchOff();
                festo.lampYellow.switchOn();
                festo.lampGreen.switchOn();
            break;


        default:
            break;
    }

}
