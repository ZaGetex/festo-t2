//
// Created by Tobias De Gasperis on 07.05.22.
//

#include "simadapter_tests.h"
#include "simmasks.h"
#include "simexecuter.h"
#include <functional>

SimAdapterTests::SimAdapterTests() : handler(nullptr), hci(nullptr), lbi(nullptr) {

    //Fuegt nach 5 Sekunden ein Werkstück mit Metall nach oben auf das Band (an den Band Anfang).
    handler.addAction(SimItemHandlingAction(5000, ItemKinds::metalup));
    //Entfernt nach 15 Sekunden alle Werkstücke vom Band
    handler.addAction(SimItemHandlingAction(15000, SimItemHandlingActionKind::removeall));

    //Nach 0 Sekunden werden alle Tastet (PushButtons, E-Stop) losgelassen/sind nicht mehr gedrueckt
    hci.addAction(SimHCIAction(    0, SimHCIActionKind::releaseAll));
    //Nach 2 Sekunden wird nur der Start-PushButton gedrueckt. Alle anderen Taster wuerden losgelassen/waren nicht mehr gedrueckt
    hci.addAction(SimHCIAction( 2000, SimHCIActionKind::pressStartOnly));
    //Nach 30 Sekunden wird zusaetzlich der E-Stop gedrueckt. (PushButtonStart ist weiterhin gedrueckt.)
    hci.addAction(SimHCIAction(30000, SimHCIActionKind::pressEStop));
    sim = new Simulation(&handler, &hci, &lbi);
#ifdef SIM_THREADED
    simrunner = new SimulationExecuter(sim, 100);
    simthread = new std::thread(*simrunner);
#endif
}


void SimAdapterTests::init() {
    if (sim != nullptr) {
        sim->init();
    }
}

unsigned short SimAdapterTests::read() {
    unsigned short result = 0;

    if (sim != nullptr) {
        result = sim->readIn();
    }
    return result;
};

void SimAdapterTests::write(unsigned short value) {
    if (sim != nullptr) {
        sim->writeOut(value);
    }
};

void SimAdapterTests::update_in() {
    if (sim != nullptr) {
#ifndef SIM_THREADED
        sim->evaluateRealTimeStep();
#endif
    }
}

void SimAdapterTests::update_out() {
    if (sim != nullptr) {
        sim->show_out();
    }
}

Simulation *SimAdapterTests::getSim() const {
    return sim;
};