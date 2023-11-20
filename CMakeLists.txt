cmake_minimum_required(VERSION 3.17)
project(PraktikumPR2)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory("festo" "festo/make_festo_output")
add_subdirectory("googletest" "googletest/make_googletest_output")