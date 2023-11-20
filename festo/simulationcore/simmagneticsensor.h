/* 
 * File:   simmagneticsensor.h
 * @author Lehmann
 * @date 3. April 2020
 */

#ifndef SIMMAGNETICSENSOR_H
#define SIMMAGNETICSENSOR_H

#include "simioimage.h"
#include <vector>
#include <memory>
#include "simitem.h"

/** 
 * Evaluate an item, whether it interrupts the light barrier or not.
 */

class SimMagneticSensor {
protected:
    std::vector<std::shared_ptr<SimItem>> *allitems;
    double position;
    SimulationIOImage* state;
    unsigned short bitmask;
public:
    SimMagneticSensor(std::vector<std::shared_ptr<SimItem>> *items, double position, SimulationIOImage* regs, unsigned short bitmask);
    virtual ~SimMagneticSensor(){};
    virtual void evalTimeStep(unsigned int simTime);
};

#endif /* SIMMAGNETICSENSOR_H */

