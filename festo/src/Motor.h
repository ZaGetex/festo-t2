//
// Created by flori on 25.11.2023.
//

#ifndef PRAKTIKUMPR2_MOTOR_H
#define PRAKTIKUMPR2_MOTOR_H
#include "../festo-source/FestoTransferSystem.h"

class Motor {
public:
    void motorStop(FestoTransferSystem&);
    void motorSlowLeft(FestoTransferSystem&);
    void motorFastLeft(FestoTransferSystem&);
    void motorSlowRight(FestoTransferSystem&);
    void motorFastRight(FestoTransferSystem&);
};

#endif //PRAKTIKUMPR2_MOTOR_H
