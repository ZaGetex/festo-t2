/* 
 * File:   simlightbarrier.h
 * @author Lehmann
 * @date 3. April 2020
 */

#ifndef SIMLIGHTBARRIER_H
#define SIMLIGHTBARRIER_H

#include "simioimage.h"
#include <vector>
#include <memory>
#include "simitem.h"

/** 
 * Evaluate an item, whether it interrupts the light barrier or not.
 */

class SimLightBarrier {
protected:
    std::vector<std::shared_ptr<SimItem>> *allitems;
    double position;
    SimulationIOImage* state;
    unsigned short bitmask;
    bool manualInterrupted;
public:
    SimLightBarrier(std::vector<std::shared_ptr<SimItem>> *items, double position, SimulationIOImage* regs, unsigned short bitmask);
    virtual ~SimLightBarrier(){};
    virtual void evalTimeStep(unsigned int simTime);
    void setManualInterrupted(bool state);
protected:
    virtual void setStateInImage(bool interrupted);
};

class SimLightBarrierSlide:public SimLightBarrier{
public:
    SimLightBarrierSlide(std::vector<std::shared_ptr<SimItem>> *items, double position, SimulationIOImage* regs, unsigned short bitmask);
    virtual ~SimLightBarrierSlide(){};
    void evalTimeStep(unsigned int simTime) override;
};

#endif /* SIMLIGHTBARRIER_H */

