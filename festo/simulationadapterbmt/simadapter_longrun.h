//
// Created by Tobias Jähnichen on 05.05.21.
//

#ifndef PRAKTIKUMPR2_SIMADAPTER_LONGRUN_H
#define PRAKTIKUMPR2_SIMADAPTER_LONGRUN_H
#include "simulation.h"
#include "simexecuter.h"
#include "isimadapter.h"
#include <thread>

class SimAdapterLongrun : public ISimAdapter{
private:
    Simulation* sim = nullptr;
    SimulationExecuter *simrunner = nullptr;
    SimItemHandling handler;
    SimHCI hci;
    SimLBI lbi;
    std::thread *simthread = nullptr;
public:
    SimAdapterLongrun();
    SimAdapterLongrun(Simulation *sim) : sim(sim), handler(nullptr), hci(nullptr), lbi(nullptr) {
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

#endif //PRAKTIKUMPR2_SIMADAPTER_LONGRUN_H
