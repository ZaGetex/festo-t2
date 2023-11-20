/* 
 * File:   simbase.h
 * Variant: BMT - Praktikum 1
 * @author Lehmann
 * @date 3. April 2020
 */

#ifndef SIMBASE_H
#define SIMBASE_H

// common definitions
#define SPEED_X_NORMAL  150  /* [mm/s] */
#define SPEED_Y_NORMAL   10  /* [mm/s] */

// base show settings
#define SIM_SHOW_ACTIONS
#define SIM_SHOW_ROI
#define SIM_SHOW_ACTUATORS
#define SIM_SHOW_SENSORS
#define SIM_SHOW_POSITIONS

class SimulationBase {
public:
    static constexpr unsigned int timeslice = 20;       // Simulate this time in each cycle
    static constexpr unsigned int realTimeSlice = 20;   // Do step only if this time has expired since last call
    static constexpr unsigned int simVersionCode = 15;
    static constexpr unsigned int displayEachNCycle = 10;
};

#endif /* SIMBASE_H */

