//
// Created by flori on 25.11.2023.
//

#include "Motor.h"
#include "../festo-source/FestoTransferSystem.h"


Motor::Motor(FestoTransferSystem *festo) {this->festo = festo;}

Motor::~Motor() = default;

void Motor::motorStop() {festo->drive.setSpeed(CONVEYERBELT_STOP);}

void Motor::motorSlowLeft() {festo->drive.setSpeed(CONVEYERBELT_LEFT_SLOW);}

void Motor::motorFastLeft() {festo->drive.setSpeed(CONVEYERBELT_LEFT_FAST);}

void Motor::motorSlowRight() {festo->drive.setSpeed(CONVEYERBELT_RIGHT_SLOW);}

void Motor::motorFastRight() {festo->drive.setSpeed(CONVEYERBELT_RIGHT_FAST);}