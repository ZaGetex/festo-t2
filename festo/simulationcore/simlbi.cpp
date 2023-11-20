//
// Created by Tobias Jähnichen on 14.04.21.
//

#include "simlbi.h"
#include "simmasks.h"
#include "simlogger.h"
#include <iostream>

using namespace std;

SimLBI::SimLBI(SimulationIOImage *shadow) : shadow(shadow), lBBegin(nullptr), lBHight(nullptr), lBFeedseparator(nullptr),
                                            lbSlide(nullptr), lbEnd(nullptr) {
}

void SimLBI::setShadow(SimulationIOImage *shadow) {
    SimLBI::shadow = shadow;
}

void SimLBI::init() {
    std::lock_guard<std::mutex> lk(buffermutex);

    for (auto &it : actions) { // it is reference to action...
        it.executed = false;
    }
}

void SimLBI::evalTime(unsigned int simTime) {
    std::lock_guard<std::mutex> lk(buffermutex);
    //cout << "simTime" << simTime << endl;

    for (auto &it : actions) { // it is reference to action...
        if (!it.executed) {
            if (it.atTime <= simTime) {
                switch (it.lb){
                    case SimLBKind::lbBegin:
                        if(nullptr != lBBegin){
                            lBBegin->setManualInterrupted(it.manuallyInterrupted);
                        }
                        break;
                    case SimLBKind::lbHeightSensor:
                        if(nullptr != lBHight) {
                            lBHight->setManualInterrupted(it.manuallyInterrupted);
                        }
                        break;
                    case SimLBKind::lbFeedSeparator:
                        if(nullptr != lBFeedseparator) {
                            lBFeedseparator->setManualInterrupted(it.manuallyInterrupted);
                        }
                        break;
                    case SimLBKind::lbBufferFull:
                        if(nullptr != lbSlide) {
                            lbSlide->setManualInterrupted(it.manuallyInterrupted);
                        }
                        break;
                    case SimLBKind::lbEnd:
                        if(nullptr != lbEnd) {
                            lbEnd->setManualInterrupted(it.manuallyInterrupted);
                        }
                        break;
                    case SimLBKind::all:
                        if(nullptr != lBBegin){
                            lBBegin->setManualInterrupted(it.manuallyInterrupted);
                        }
                        if(nullptr != lBHight) {
                            lBHight->setManualInterrupted(it.manuallyInterrupted);
                        }
                        if(nullptr != lBFeedseparator) {
                            lBFeedseparator->setManualInterrupted(it.manuallyInterrupted);
                        }
                        if(nullptr != lbSlide) {
                            lbSlide->setManualInterrupted(it.manuallyInterrupted);
                        }
                        if(nullptr != lbEnd) {
                            lbEnd->setManualInterrupted(it.manuallyInterrupted);
                        }
                        break;
                    default:
                        if(nullptr != lBBegin){
                            lBBegin->setManualInterrupted(false);
                        }
                        if(nullptr != lBHight) {
                            lBHight->setManualInterrupted(false);
                        }
                        if(nullptr != lBFeedseparator) {
                            lBFeedseparator->setManualInterrupted(false);
                        }
                        if(nullptr != lbSlide) {
                            lbSlide->setManualInterrupted(false);
                        }
                        if(nullptr != lbEnd) {
                            lbEnd->setManualInterrupted(false);
                        }
                        break;
                }
#ifdef SIM_SHOW_ACTIONS
                LOGGER << "<SIM> new LBI ACTION: LB " << "0x" << hex << (int)it.lb << dec << " " << it.manuallyInterrupted << endl;
#endif
                it.executed = true;
            }
        }
    }
}

void SimLBI::addAction(const SimLBIAction &action) {
    std::lock_guard<std::mutex> lk(buffermutex);
    actions.push_back(action);
}

void SimLBI::setLbBegin(SimLightBarrier *lBBegin) {
    SimLBI::lBBegin = lBBegin;
}

void SimLBI::setLbHight(SimLightBarrier *lBHight) {
    SimLBI::lBHight = lBHight;
}

void SimLBI::setLbFeedseparator(SimLightBarrier *lBFeedseparator) {
    SimLBI::lBFeedseparator = lBFeedseparator;
}

void SimLBI::setLbEnd(SimLightBarrier *lbEnd) {
    SimLBI::lbEnd = lbEnd;
}

void SimLBI::setLbSlide(SimLightBarrierSlide *lbSlide) {
    SimLBI::lbSlide = lbSlide;
}

