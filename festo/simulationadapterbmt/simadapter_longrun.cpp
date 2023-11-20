/* 
 * File:   simadapter.cpp
 * @author Lehmann
 * @date 28. März 2020
 */

#include "simadapter_longrun.h"
#include "simmasks.h"
#include "simexecuter.h"
#include <functional>

SimAdapterLongrun::SimAdapterLongrun() : handler(nullptr), hci(nullptr), lbi(nullptr) {

    handler.addAction(SimItemHandlingAction(11000, ItemKinds::metalup));
    handler.addAction(SimItemHandlingAction(20000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(21000, ItemKinds::holedown));
    handler.addAction(SimItemHandlingAction(30000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(31000, ItemKinds::holedown));
    handler.addAction(SimItemHandlingAction(40000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(41000, ItemKinds::holeup));
    handler.addAction(SimItemHandlingAction(50000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(51000, ItemKinds::metalup));
    handler.addAction(SimItemHandlingAction(60000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(61000, ItemKinds::metaldown));
    handler.addAction(SimItemHandlingAction(70000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(71000, ItemKinds::metalup));
    handler.addAction(SimItemHandlingAction(80000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(81000, ItemKinds::flat));
    handler.addAction(SimItemHandlingAction(90000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(91000, ItemKinds::holeup));
    handler.addAction(SimItemHandlingAction(10000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(10100, ItemKinds::metaldown));
    handler.addAction(SimItemHandlingAction(110000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(111000, ItemKinds::metalup));
    handler.addAction(SimItemHandlingAction(120000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(121000, ItemKinds::holeup));
    handler.addAction(SimItemHandlingAction(130000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(131000, ItemKinds::flat));
    handler.addAction(SimItemHandlingAction(140000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(141000, ItemKinds::holedown));
    handler.addAction(SimItemHandlingAction(150000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(151000, ItemKinds::holedown));
    handler.addAction(SimItemHandlingAction(160000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(162000, ItemKinds::metalup));
    handler.addAction(SimItemHandlingAction(170000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(171000, ItemKinds::flat));
    handler.addAction(SimItemHandlingAction(180000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(181000, ItemKinds::metalup));
    handler.addAction(SimItemHandlingAction(190000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(191000, ItemKinds::flat));
    handler.addAction(SimItemHandlingAction(200000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(201000, ItemKinds::metaldown));
    handler.addAction(SimItemHandlingAction(210000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(211000, ItemKinds::holeup));
    handler.addAction(SimItemHandlingAction(220000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(221000, ItemKinds::metalup));
    handler.addAction(SimItemHandlingAction(230000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(231000, ItemKinds::flat));
    handler.addAction(SimItemHandlingAction(240000, SimItemHandlingActionKind::removeall));
    handler.addAction(SimItemHandlingAction(241000, ItemKinds::metalup));
    handler.addAction(SimItemHandlingAction(250000, SimItemHandlingActionKind::removeall));

    hci.addAction(SimHCIAction(0, SimHCIActionKind::releaseAll));
    hci.addAction(SimHCIAction(2000, SimHCIActionKind::pressStartOnly));
    hci.addAction(SimHCIAction(3000, SimHCIActionKind::releaseAll));

    hci.addAction(SimHCIAction(260000, SimHCIActionKind::pressStartOnly));
    hci.addAction(SimHCIAction(261000, SimHCIActionKind::releaseAll));
    hci.addAction(SimHCIAction(271000, SimHCIActionKind::pressEStopOnly));
    hci.addAction(SimHCIAction(272000, SimHCIActionKind::releaseAll));

    sim = new Simulation(&handler, &hci, &lbi);
#ifdef SIM_THREADED
    simrunner = new SimulationExecuter(sim, 100);
    simthread = new std::thread(*simrunner);
#endif
}

void SimAdapterLongrun::init() {
    if (sim != nullptr) {
        sim->init();
    }
}

unsigned short SimAdapterLongrun::read() {
    unsigned short result = 0;

    if (sim != nullptr) {
        result = sim->readIn();
    }
    return result;
};

void SimAdapterLongrun::write(unsigned short value) {
    if (sim != nullptr) {
        sim->writeOut(value);
    }
};

void SimAdapterLongrun::update_in() {
    if (sim != nullptr) {
#ifndef SIM_THREADED
        sim->evaluateRealTimeStep();
#endif
    }
}

void SimAdapterLongrun::update_out() {
    if (sim != nullptr) {
        sim->show_out();
    }
};

Simulation* SimAdapterLongrun::getSim() const {
    return sim;
};
