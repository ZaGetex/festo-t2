//
// Created by flori on 25.11.2023.
//

#ifndef PRAKTIKUMPR2_MOTOR_H
#define PRAKTIKUMPR2_MOTOR_H
#include "../festo-source/FestoTransferSystem.h"

class Motor {
private:

public:
    Motor();
    virtual ~Motor();

    static void motorStop(FestoTransferSystem&);
    static void motorSlowLeft(FestoTransferSystem&);
    static void motorFastLeft(FestoTransferSystem&);
    static void motorSlowRight(FestoTransferSystem&);
    static void motorFastRight(FestoTransferSystem&);
};

#endif //PRAKTIKUMPR2_MOTOR_H
