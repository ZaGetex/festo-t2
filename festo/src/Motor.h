//
// Created by flori on 25.11.2023.
//

#ifndef PRAKTIKUMPR2_MOTOR_H
#define PRAKTIKUMPR2_MOTOR_H
#include "../festo-source/FestoTransferSystem.h"

class Motor {
private:
    static FestoTransferSystem *festo;

public:
    explicit Motor(FestoTransferSystem *festo); //konstruktor
    virtual ~Motor(); //destruktor

    static void motorStop();
    static void motorSlowLeft();
    static void motorFastLeft();
    static void motorSlowRight();
    static void motorFastRight();
};

#endif //PRAKTIKUMPR2_MOTOR_H
