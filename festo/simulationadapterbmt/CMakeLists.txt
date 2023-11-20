project(simulationadapterbmt)

set(SOURCE_FILES
        simadapter.cpp simadapter.h
        simbase.h
        isimadapter.h
        simadapter_tests.cpp simadapter_tests.h
        )

add_library(simulationadapterbmt STATIC ${SOURCE_FILES})