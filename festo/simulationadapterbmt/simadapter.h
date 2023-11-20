
/* 
 * File:   simadapter.h
 * @author Lehmann
 * @date 28. März 2020
 * modified by Tobias Jaehnichen
 * 22.04.2020
 */

#ifndef SIMADAPTER_H
#define SIMADAPTER_H

#include "simulation.h"
#include "simexecuter.h"
#include "isimadapter.h"
#include <thread>

class SimAdapter : public ISimAdapter{
private:
    Simulation* sim = nullptr;
    SimulationExecuter *simrunner = nullptr;
    SimItemHandling handler;
    SimHCI hci;
    SimLBI lbi;
    std::thread *simthread = nullptr;
public:
    SimAdapter();
    SimAdapter(Simulation *sim) : sim(sim), handler(nullptr), hci(nullptr), lbi(nullptr) {
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

#endif /* SIMADAPTER_H */

