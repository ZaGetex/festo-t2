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
        ANFANGSZUSTAND,
        BETRIEBSBEREIT,
        TRANSPORT,
        HOEHENMESSUNG,
        HOEHE_OK,
        DREHEN,
        TRANSPORT_GEDREHT,
        HOEHE_NOT_OK,
        WEICHE,
        NOT_METALLIC,
        METALLIC,
        BUFFER,
        BUFFER_FREE,
        END,
        END_FREE,
        };

    States state;
    Motor motor;
    FestoTransferSystem& festo;
    bool running;
public:
    FSM(FestoTransferSystem& f);
    bool evalTransition();
    void evalStates();
    bool getRunning() const;
    void emergency();
};


#endif //PRAKTIKUMPR2_FSM_H
