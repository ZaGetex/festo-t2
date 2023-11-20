//
// Created by Tobias Jähnichen on 14.04.21.
//

#ifndef SIMLBI_H
#define SIMLBI_H

#include "simbase.h"
#include "simioimage.h"
#include "simlbiaction.h"
#include "simlightbarrier.h"
#include <mutex>
#include <vector>

class SimLBI {
private:
    SimulationIOImage* shadow;
    SimLightBarrier *lBBegin;
    SimLightBarrier *lBHight;
    SimLightBarrier *lBFeedseparator;
    SimLightBarrier *lbEnd;
    SimLightBarrierSlide *lbSlide;
    std::vector<SimLBIAction> actions;
    std::mutex buffermutex;
public:
    explicit SimLBI(SimulationIOImage* shadow = nullptr);
    void init();
    void evalTime(unsigned int simTime);
    void addAction(const SimLBIAction &action);

    void setShadow(SimulationIOImage* shadow);

    void setLbBegin(SimLightBarrier *lBBegin);

    void setLbHight(SimLightBarrier *lBHight);

    void setLbFeedseparator(SimLightBarrier *lBFeedseparator);

    void setLbEnd(SimLightBarrier *lbEnd);

    void setLbSlide(SimLightBarrierSlide *lbSlide);
};


#endif //SIMLBI_H
