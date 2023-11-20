/** 
 * File:   BeltDrive.cpp
 * @author Thomas Lehmann
 * @date 2016-09-17
 * @version 1
 * Initial version
 */

#include <cstdio>
#include <iostream>
#include "BeltDrive.h"
#include "iomasks.h"
#include "FestoTransferSystem.h"

unsigned int BeltDrive::objectCounter = 0;

BeltDrive::BeltDrive() {
    BeltDrive::objectCounter++;
#ifdef FESTO_VERBOSE
    if (objectCounter > 1) {
        std::cerr << "Warning, multiple object of BeltDrive, counter:" << objectCounter << std::endl;
    }
#endif
};

void BeltDrive::setSpeed(unsigned char mode) {
    MiniLab1008* io = FestoTransferSystem::access;

    if (io != NULL) {
        switch (mode) {
            case CONVEYERBELT_STOP: // stop
                io->setBitInOutput(DRIVE_STOP);
                io->clearBitInOutput(DRIVE_DIRECTION_RIGHT | DRIVE_DIRECTION_LEFT | DRIVE_SLOW);
                break;
            case CONVEYERBELT_LEFT_SLOW:
                io->setBitInOutput(DRIVE_DIRECTION_LEFT | DRIVE_SLOW);
                io->clearBitInOutput(DRIVE_STOP | DRIVE_DIRECTION_RIGHT);
                break;
            case CONVEYERBELT_LEFT_FAST:
                io->setBitInOutput(DRIVE_DIRECTION_LEFT);
                io->clearBitInOutput(DRIVE_STOP | DRIVE_DIRECTION_RIGHT | DRIVE_SLOW);
                break;
            case CONVEYERBELT_RIGHT_SLOW: // stop
                io->setBitInOutput(DRIVE_DIRECTION_RIGHT | DRIVE_SLOW);
                io->clearBitInOutput(DRIVE_STOP | DRIVE_DIRECTION_LEFT);
                break;
            case CONVEYERBELT_RIGHT_FAST:
                io->setBitInOutput(DRIVE_DIRECTION_RIGHT);
                io->clearBitInOutput(DRIVE_STOP | DRIVE_DIRECTION_LEFT | DRIVE_SLOW);
                break;
            default:
                io->setBitInOutput(DRIVE_STOP);
                io->clearBitInOutput(DRIVE_DIRECTION_RIGHT | DRIVE_DIRECTION_LEFT | DRIVE_SLOW);

        }
    }
};


