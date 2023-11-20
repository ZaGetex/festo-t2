cmake_minimum_required(VERSION 3.17)
project(festo)

set(CMAKE_CXX_STANDARD 14)

## Compiler Defines hier mittels add_definition hinzufügen
##add_definitions(-DHOME -DSIMULATION) #Schaltet die Simulation an
##add_definitions(-DSIM_SHOW_TIMESTAMP) #Gibt die in der Simulation vergangene Zeit aus

## Eines der beiden folgenden Defined kann aktiviert werden, um einen anderen Simulationsablauf zu waehlen
#add_definitions(-DSIMLONGRUN) #Schaltet die Lange Simulation an
#add_definitions(-DSIMTESTS) #Schaltet die in simadapter_test.cpp definierte Simulation an

## In der folgenden Zeile alle .cpp- und .h-Dateien aus diesem Verzeichnis ergänzen.
add_executable(Festo_Praktikum main.cpp)


## Die folgenden Zeilen nicht ändern
#add_definitions(-DSIM_THREADED)
#Define Interface via minilab1008 USB-Adaptor
add_definitions(-DOLD_INTERFACE)

find_library(CBW_LIB cbw64 ./lib)
find_path (CBW_INCLUDES cbw.h ./lib)
include_directories(${CBW_INCLUDES})
if(${WIN32})
    add_definitions(-DWIN_SYS)
endif()

include_directories(festo-source simulationadapterbmt simulationcore src)
add_subdirectory(festo-source)
add_subdirectory(simulationadapterbmt)
add_subdirectory(simulationcore)
add_subdirectory(src)
add_subdirectory(tests)
IF(${WIN32})
    target_link_libraries(Festo_Praktikum festo-source simulationadapterbmt simulationcore src ${CBW_LIB})
ELSE()
    get_directory_property(MYDEFS COMPILE_DEFINITIONS)
    if(MYDEFS MATCHES "^HOME")
    else()
        message(WARNING "Compiling not on Windows. You can only use the Simulation here!")
    endif()
    target_link_libraries(Festo_Praktikum festo-source simulationadapterbmt simulationcore src)
ENDIF()
