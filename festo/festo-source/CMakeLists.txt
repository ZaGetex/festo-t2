project(festo-source)

set(SOURCE_FILES
        AlarmLamp.cpp AlarmLamp.h
        BeltDrive.cpp BeltDrive.h
        FeedSeparator.cpp FeedSeparator.h
        FestoTransferSystem.cpp FestoTransferSystem.h
        BeltDrive.h BeltDrive.cpp
        iomasks.h
        LED.cpp LED.h
        LightBarrier.cpp LightBarrier.h
        minilab1008.cpp minilab1008.h
        PushButton.cpp PushButton.h
        TimeHelper.cpp TimeHelper.h
        HeightSensor.cpp HeightSensor.h
        MetalDetector.cpp MetalDetector.h
        AlarmClock.cpp AlarmClock.h
        )

add_library(festo-source STATIC ${SOURCE_FILES})