//
// Created by Tobias Jähnichen on 05.05.21.
//

#ifndef PRAKTIKUMPR2_ISIMADAPTER_H
#define PRAKTIKUMPR2_ISIMADAPTER_H

#include "simulation.h"

class ISimAdapter {
public:
    virtual ~ISimAdapter(){};
    virtual void init()=0;
    virtual void update_in()=0;
    virtual void update_out()=0;

    virtual unsigned short read()=0;
    virtual void write(unsigned short value)=0;

    virtual void setSimulation(Simulation *sim)=0;
    virtual Simulation *getSim() const = 0;
};

#endif //PRAKTIKUMPR2_ISIMADAPTER_H
