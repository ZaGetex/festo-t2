# 'festo_test' is the subproject name
project(festo_tests)

# 'googletest' is the folder with Google Test sources
include_directories(../src  ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
add_executable(Festo_gTests_run test1.cpp)

# Ad Linkage for Festo Transfer System
IF(${WIN32})
    target_link_libraries(Festo_gTests_run festo-source simulationadapterbmt simulationcore src ${CBW_LIB})
ELSE()
    get_directory_property(MYDEFS COMPILE_DEFINITIONS)
    if(MYDEFS MATCHES "^HOME")
    else()
        message(WARNING "Compiling not on Windows. You can only use the Simulation here!")
    endif()
    target_link_libraries(Festo_gTests_run festo-source simulationadapterbmt simulationcore src)
ENDIF()

target_link_libraries(Festo_gTests_run gtest gtest_main)