/**
 * @author Niklas Dathe
 * @author Florian Czorniuk
 * @date   25.11.2023
 */

#include "FestoTransferSystem.h"
#include "FSM.h"

int main() {
    FestoTransferSystem festo;
    FSM fsm;
    while(fsm.isRunning()) {
        festo.updateSensors();
        fsm.evalStates(festo);
        fsm.evalTransition(festo);
        festo.updateActuators();
    }
    return 0;
}