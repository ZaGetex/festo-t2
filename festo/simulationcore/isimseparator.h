
/* 
 * File:   isimseparator.h
 * @author Lehmann
 * @date 21. Mai 2020
 */

#ifndef ISIMSEPARATOR_H
#define ISIMSEPARATOR_H

#include "simmasks.h"

#define SIM_BITMASK_FEEDSEPERATOR_ACTOR SIM_FEED_SEPARATOR
#define SIM_BITMASK_FEEDSEPERATOR_SENSOR SIM_JUNCTION_IS_OPEN

class ISimSeparator {
public:
    virtual ~ISimSeparator() {
    };
    /**
     * Translate register settings to opening state of switch or pusher
     * @return state (true if open, so item can pass)
     */
    virtual bool isModePassing() = 0;
    virtual double getPosition() = 0;
    virtual bool isPusher() = 0;
};

#endif /* ISIMSEPARATOR_H */

