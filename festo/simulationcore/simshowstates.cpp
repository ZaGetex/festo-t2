/* 
 * File:   simshowstates.cpp
 * @author Lehmann
 * @date 29. März 2020
 */

#include "simshowstates.h"
#include "simmasks.h"
#include "simlogger.h"
#include <iostream>
using namespace std;

void SimShowStates::showFullOut() {
    unsigned short out = state->out;
    unsigned diff = 0x0fff;

    showOut(out, diff);

    last.out = state->out;
};

void SimShowStates::showDiffOut() {
    unsigned short out = state->out;
    unsigned diff = out ^ last.out;

    showOut(out, diff);

    last.out = state->out;
}

void SimShowStates::showFullIn() {
    unsigned short in = state->in;
    unsigned diff = 0x0fff;

    showIn(in, diff);

    last.in = state->in;
};

void SimShowStates::showDiffIn() {
    unsigned short in = state->in;
    unsigned diff = in ^ last.in;

    showIn(in, diff);

    last.in = state->in;
}

void SimShowStates::showOut(unsigned short out, unsigned short diff) {
    unsigned short drive_mask = SIM_DRIVE_DIRECTION_RIGHT | SIM_DRIVE_DIRECTION_LEFT | SIM_DRIVE_SLOW | SIM_DRIVE_STOP;

    if ((diff & drive_mask) != 0) {
#ifdef SIM_SHOW_ACTUATORS
        if ((out & drive_mask) == 0 || (out & SIM_DRIVE_STOP) == SIM_DRIVE_STOP) {
            LOGGER << "<SIM> Belt stopped" << endl;
        } else {
            if (out & SIM_DRIVE_DIRECTION_RIGHT) {
                LOGGER << "<SIM> Belt moves right";
            }
            if (out & SIM_DRIVE_DIRECTION_LEFT) {
                LOGGER << "<SIM> Belt moves left";
            }
            if (out & SIM_DRIVE_SLOW) {
                LOGGER << ", slow" << endl;
            } else {
                LOGGER << ", fast" << endl;

            }
        }
    }
    if (diff & SIM_FEED_SEPARATOR) {
        if (out & SIM_FEED_SEPARATOR) {
            LOGGER << "<SIM> Feeder: commanded open" << endl;
        } else {
            LOGGER << "<SIM> Feeder: commanded closed" << endl;
        }
    }
    if (diff & SIM_ALARM_LAMP_RED) {
        if (out & SIM_ALARM_LAMP_RED) {
            LOGGER << "<SIM> Red:    on" << endl;
        } else {
            LOGGER << "<SIM> Red:    off" << endl;
        }
    }
    if (diff & SIM_ALARM_LAMP_YELLOW) {
        if (out & SIM_ALARM_LAMP_YELLOW) {
            LOGGER << "<SIM> Yellow: on" << endl;
        } else {
            LOGGER << "<SIM> Yellow: off" << endl;
        }
    }
    if (diff & SIM_ALARM_LAMP_GREEN) {
        if (out & SIM_ALARM_LAMP_GREEN) {
            LOGGER << "<SIM> Green:  on" << endl;
        } else {
            LOGGER << "<SIM> Green:  off" << endl;
        }
    }
    if (diff & SIM_LED_START_BUTTON) {
        if (out & SIM_LED_START_BUTTON) {
            LOGGER << "<SIM> LED start: on" << endl;
        } else {
            LOGGER << "<SIM> LED start: off" << endl;
        }
    }
    if (diff & SIM_LED_RESET_BUTTON) {
        if (out & SIM_LED_RESET_BUTTON) {
            LOGGER << "<SIM> LED Reset: on" << endl;
        } else {
            LOGGER << "<SIM> LED Reset: off" << endl;
        }
    }
    if (diff & SIM_LED_Q1) {
        if (out & SIM_LED_Q1) {
            LOGGER << "<SIM> LED q1:    on" << endl;
        } else {
            LOGGER << "<SIM> LED q1:    off" << endl;
        }
    }
    if (diff & SIM_LED_Q2) {
        if (out & SIM_LED_Q2) {
            LOGGER << "<SIM> LED Q2:    on" << endl;
        } else {
            LOGGER << "<SIM> LED Q2:    off" << endl;
        }
#endif
    }
};

void SimShowStates::showIn(unsigned short in, unsigned short diff) {
#ifdef SIM_SHOW_SENSORS
    if (diff & SIM_ITEM_DETECTED) {
        if (in & SIM_ITEM_DETECTED) {
            LOGGER << "<SIM> LB Begin: closed" << endl;
        } else {
            LOGGER << "<SIM> LB Begin: interrupted" << endl;
        }
    }
    if (diff & SIM_ITEM_AT_HEIGHT_SENSOR) {
        if (in & SIM_ITEM_AT_HEIGHT_SENSOR) {
            LOGGER << "<SIM> LB Height: closed" << endl;
        } else {
            LOGGER << "<SIM> LB Height: interrupted" << endl;
        }
    }
    if (diff & SIM_ITEM_AT_JUNCTION) {
        if (in & SIM_ITEM_AT_JUNCTION) {
            LOGGER << "<SIM> LB Feed Separator: closed" << endl;
        } else {
            LOGGER << "<SIM> LB Feed Separator: interrupted" << endl;
        }
    }
    if (diff & SIM_BUFFER_IS_FULL) {
        if (in & SIM_BUFFER_IS_FULL) {
            LOGGER << "<SIM> LB Slide: closed" << endl;
        } else {
            LOGGER << "<SIM> LB Slide: interrupted" << endl;
        }
    }
    if (diff & SIM_ITEM_AT_END) {
        if (in & SIM_ITEM_AT_END) {
            LOGGER << "<SIM> LB End: closed" << endl;
        } else {
            LOGGER << "<SIM> LB End: interrupted" << endl;
        }
    }
    if (diff & SIM_ITEM_HEIGHT_FITS) {
        if (in & SIM_ITEM_HEIGHT_FITS) {
            LOGGER << "<SIM> Height okay" << endl;
        } else {
            LOGGER << "<SIM> Height not okay" << endl;
        }
    }
    if (diff & SIM_ITEM_IS_METTAL) {
        if (in & SIM_ITEM_IS_METTAL) {
            LOGGER << "<SIM> Metal detected" << endl;
        } else {
            LOGGER << "<SIM> Metal not detected" << endl;
        }
    }
    if (diff & SIM_JUNCTION_IS_OPEN) {
        if (in & SIM_JUNCTION_IS_OPEN) {
            LOGGER << "<SIM> Feed Separator: pass" << endl;
        } else {
            LOGGER << "<SIM> Feed Separator: slide" << endl;
        }
    }

    if (diff & SIM_BUTTON_START) {
        if (in & SIM_BUTTON_START) {
            LOGGER << "<SIM> Button Start: pressed" << endl;
        } else {
            LOGGER << "<SIM> Button Start: released" << endl;
        }
    }
    if (diff & SIM_BUTTON_STOP) {
        if (in & SIM_BUTTON_STOP) {  // active low
            LOGGER << "<SIM> Button Stop: released" << endl;
        } else {
            LOGGER << "<SIM> Button Stop: pressed" << endl;
        }
    }
    if (diff & SIM_BUTTON_RESET) {
        if (in & SIM_BUTTON_RESET) {
            LOGGER << "<SIM> Button Reset: pressed" << endl;
        } else {
            LOGGER << "<SIM> Button Reset: released" << endl;
        }
    }
    if (diff & SIM_EMERGENCY_STOP) {
        if (in & SIM_EMERGENCY_STOP) {  // active low
            LOGGER << "<SIM> Emergency: not active" << endl;
        } else {
            LOGGER << "<SIM> Emergency: active" << endl;
        }
    }
#endif
}
