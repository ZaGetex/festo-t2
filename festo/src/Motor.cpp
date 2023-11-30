//
// Created by flori on 25.11.2023.
//

#include "Motor.h"

void Motor::motorStop() {f.drive.setSpeed(CONVEYERBELT_STOP);}
void Motor::motorSlowLeft() {f.drive.setSpeed(CONVEYERBELT_LEFT_SLOW);}
void Motor::motorFastLeft() {f.drive.setSpeed(CONVEYERBELT_LEFT_FAST);}
void Motor::motorSlowRight() {f.drive.setSpeed(CONVEYERBELT_RIGHT_SLOW);}
void Motor::motorFastRight() {f.drive.setSpeed(CONVEYERBELT_RIGHT_FAST);}

Motor::Motor(FestoTransferSystem &fts)
: f(fts)
{
}
