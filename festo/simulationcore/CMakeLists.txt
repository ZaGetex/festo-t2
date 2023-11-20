project(simulationcore)

set(SOURCE_FILES
        isimdrophandler.h
        isiminitcompleteobserver.h
        isimseparator.h
        isimulationcycleendhandler.h
        isimulationexecution.h
        isimulationimage.h
        isimulationreporthandler.h
        simconveyorbelt.cpp simconveyorbelt.h
        simctrlaction.cpp simctrlaction.h
        simctrlhandler.cpp simctrlhandler.h
        simdrive.cpp simdrive.h
        simexecuter.cpp simexecuter.h
        simfeedpusher.cpp simfeedpusher.h
        simfeedseparator.cpp simfeedseparator.h
        simhci.cpp simhci.h
        simhciaction.cpp simhciaction.h
        simheightsensor.cpp simheightsensor.h
        simioimage.h
        simitem.cpp simitem.h
        simitemhandling.cpp simitemhandling.h
        simitemhandlingaction.cpp simitemhandlingaction.h
        simitemmanager.cpp simitemmanager.h
        simjsonbase.cpp simjsonbase.h
        simjsonmessagehandler.cpp simjsonmessagehandler.h
        simlightbarrier.cpp simlightbarrier.h
        simlogger.cpp simlogger.h
        simmagneticsensor.cpp simmagneticsensor.h
        simmasks.h
        simsensors.cpp simsensors.h
        simshowstates.cpp simshowstates.h
        simslide.cpp simslide.h
        simulation.cpp simulation.h
        simulationimageaccesdummy.h
        simlbiaction.cpp simlbiaction.h
        simlbi.cpp simlbi.h)

add_library(simulationcore STATIC ${SOURCE_FILES})