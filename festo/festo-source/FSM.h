//
// Created by nikla on 21.11.2023.
//

#ifndef PRAKTIKUMPR2_FSM_H
#define PRAKTIKUMPR2_FSM_H

#include "FestoTransferSystem.h"

class FSM {
private:
    enum class States {ANFANGSZUSTAND = 0, BETRIEBSBEREIT};
    bool running;
    States state;
public:
    FSM();
    FestoTransferSystem festo;
    bool getRunning() const;
    bool evalTransition();
    void evalStates();
};


#endif //PRAKTIKUMPR2_FSM_H
