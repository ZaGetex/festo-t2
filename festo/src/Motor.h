//
// Created by flori on 25.11.2023.
//

#ifndef PRAKTIKUMPR2_MOTOR_H
#define PRAKTIKUMPR2_MOTOR_H
#include "../festo-source/FestoTransferSystem.h"

class Motor {
private:
    FestoTransferSystem& f;


public:
    Motor(FestoTransferSystem& fts);
    void motorStop();
    void motorSlowLeft();
    void motorFastLeft();
    void motorSlowRight();
    void motorFastRight();
};

#endif //PRAKTIKUMPR2_MOTOR_H
