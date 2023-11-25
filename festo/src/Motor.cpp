//
// Created by flori on 25.11.2023.
//

#include "Motor.h"

void Motor::motorStop(FestoTransferSystem& festo) {festo.drive.setSpeed(CONVEYERBELT_STOP);}
void Motor::motorSlowLeft(FestoTransferSystem& festo) {festo.drive.setSpeed(CONVEYERBELT_LEFT_SLOW);}
void Motor::motorFastLeft(FestoTransferSystem& festo) {festo.drive.setSpeed(CONVEYERBELT_LEFT_FAST);}
void Motor::motorSlowRight(FestoTransferSystem& festo) {festo.drive.setSpeed(CONVEYERBELT_RIGHT_SLOW);}
void Motor::motorFastRight(FestoTransferSystem& festo) {festo.drive.setSpeed(CONVEYERBELT_RIGHT_FAST);}