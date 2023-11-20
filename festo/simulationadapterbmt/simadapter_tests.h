//
// Created by Tobias De Gasperis on 07.05.22.
//

#ifndef PRAKTIKUMPR2_SIMADAPTER_TESTS_H
#define PRAKTIKUMPR2_SIMADAPTER_TESTS_H
#include "simulation.h"
#include "simexecuter.h"
#include "isimadapter.h"
#include <thread>

class SimAdapterTests : public ISimAdapter {
private:
    Simulation* sim = nullptr;
    SimulationExecuter *simrunner = nullptr;
    SimItemHandling handler;
    SimHCI hci;
    SimLBI lbi;
    std::thread *simthread = nullptr;
public:
    SimAdapterTests();
    SimAdapterTests(Simulation *sim) : sim(sim), handler(nullptr), hci(nullptr), lbi(nullptr) {
    };
    void init();
    void update_in();
    void update_out();

    unsigned short read();
    void write(unsigned short value);

    void setSimulation(Simulation *sim) {
        this->sim = sim;
    };
    Simulation *getSim() const;

};


#endif //PRAKTIKUMPR2_SIMADAPTER_TESTS_H
