/** 
 * File:   FestoTransferSystem.h
 * @author Thomas Lehmann
 * @date 2016-09-17
 * @version 1
 * Initial version
 */

#ifndef FESTOTRANSFERSYSTEM_H
#define FESTOTRANSFERSYSTEM_H

#include "minilab1008.h"
#include "LightBarrier.h"
#include "HeightSensor.h"
#include "MetalDetector.h"
#include "PushButton.h"
#include "LED.h"
#include "FeedSeparator.h"
#include "AlarmLamp.h"
#include "BeltDrive.h"

// set the define to get more information...
#define FESTO_VERBOSE

#ifdef __cplusplus
extern "C" {
#endif

    class FestoTransferSystem {
        friend class LightBarrier;
        friend class HeightSensor;
        friend class MetalDetector;
        friend class PushButton;
        friend class LED;
        friend class FeedSeparator;
        friend class AlarmLamp;
        friend class BeltDrive;
    private:
        static MiniLab1008* access;
        static unsigned int objectCounter;
        FestoTransferSystem& operator=(const FestoTransferSystem& f) = delete;
    public:
        LightBarrier lightbarrierBegin;
        LightBarrier lightbarrierHeightSensor;
        LightBarrier lightbarrierFeedSeparator;
        LightBarrier lightbarrierBufferFull;
        LightBarrier lightbarrierEnd;
        HeightSensor heightcheck;
        MetalDetector metalcheck;
        PushButton pushbuttonStart;
        PushButton pushbuttonStop;
        PushButton pushbuttonReset;
        PushButton switchEmergency;
        LED ledStart;
        LED ledReset;
        LED ledQ1;
        LED ledQ2;
        FeedSeparator feedSeparator;
        AlarmLamp lampRed;
        AlarmLamp lampYellow;
        AlarmLamp lampGreen;
        BeltDrive drive;
        
    public:
        FestoTransferSystem();
        FestoTransferSystem(FestoTransferSystem& other);
        void updateSensors();
        void updateActuators();
    };

#ifdef __cplusplus
}
#endif

#endif /* FESTOTRANSFERSYSTEM_H */

