/**
 * @author Niklas Dathe
 * @author Florian Czorniuk
 * @date   25.11.2023
 */

#include "FestoTransferSystem.h"
#include "FSM.h"

int main() {
    FestoTransferSystem festo;
    FSM fsm(festo);
    while(fsm.getRunning()) {
        festo.updateSensors();
        fsm.evalTransition();
        fsm.evalStates();
        festo.updateActuators();
    }
    return 0;
}