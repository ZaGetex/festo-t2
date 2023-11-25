//
// Created by nikla on 21.11.2023.
//

#ifndef PRAKTIKUMPR2_FSM_H
#define PRAKTIKUMPR2_FSM_H

#include "../festo-source/FestoTransferSystem.h"
#include "Motor.h"

class FSM {
private:
    enum class States {
        ANFANGSZUSTAND = 0,
        BETRIEBSBEREIT,
        NUll,
        EINS,
        ZWEI,
        DREI,
        VIER,
        FUENF,
        SECHS,
        SIEBEN,
        ACHT,
        NEUN,
        ZEHN,
        ELF,
        ZWOELF,
        DREIZEHN,
        VIERZEHN,
        FUENFZEHN,
        };

    States state;
    Motor motor;
public:
    FSM();
    bool evalTransition(FestoTransferSystem&);
    void evalStates(FestoTransferSystem&);
    bool running;

};


#endif //PRAKTIKUMPR2_FSM_H
