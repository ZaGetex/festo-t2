/* 
 * File:   simadapter.cpp
 * @author Lehmann
 * @date 28. März 2020
 */

#include "simadapter.h"
#include "simmasks.h"
#include "simexecuter.h"
#include <functional>

#define STARTTIME 500
#define OFFSET 1000
#define START_HCI_ACTIONS 19000

SimAdapter::SimAdapter() : handler(nullptr), hci(nullptr), lbi(nullptr) {
    int time = STARTTIME;
    handler.addAction(SimItemHandlingAction(5000, ItemKinds::metalup));
    handler.addAction(SimItemHandlingAction(15000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(16000, ItemKinds::holedown));
    handler.addAction(SimItemHandlingAction(22000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(22500, ItemKinds::holeup));
    handler.addAction(SimItemHandlingAction(30000, SimItemHandlingActionKind::removeall));


    hci.addAction(SimHCIAction(    0, SimHCIActionKind::releaseAll));
    hci.addAction(SimHCIAction( 2000, SimHCIActionKind::pressStartOnly));
    hci.addAction(SimHCIAction( 3000, SimHCIActionKind::releaseAll));

    hci.addAction(SimHCIAction( 23000, SimHCIActionKind::pressResetOnly));
    hci.addAction(SimHCIAction( 23500, SimHCIActionKind::releaseAll));

    hci.addAction(SimHCIAction(30000, SimHCIActionKind::pressStartOnly));
    hci.addAction(SimHCIAction(31000, SimHCIActionKind::releaseAll));
    hci.addAction(SimHCIAction(32000, SimHCIActionKind::pressEStopOnly));
    hci.addAction(SimHCIAction(33000, SimHCIActionKind::releaseAll));

    sim = new Simulation(&handler, &hci, &lbi);
#ifdef SIM_THREADED
    simrunner = new SimulationExecuter(sim, 200);
    simthread = new std::thread(*simrunner);
#endif
}

void SimAdapter::init() {
    if (sim != nullptr) {
        sim->init();
    }
}

unsigned short SimAdapter::read() {
    unsigned short result = 0;

    if (sim != nullptr) {
        result = sim->readIn();
    }
    return result;
};

void SimAdapter::write(unsigned short value) {
    if (sim != nullptr) {
        sim->writeOut(value);
    }
};

void SimAdapter::update_in() {
    if (sim != nullptr) {
#ifndef SIM_THREADED
        sim->evaluateRealTimeStep();
#endif
    }
}

void SimAdapter::update_out() {
    if (sim != nullptr) {
        sim->show_out();
    }
}

Simulation *SimAdapter::getSim() const {
    return sim;
};
