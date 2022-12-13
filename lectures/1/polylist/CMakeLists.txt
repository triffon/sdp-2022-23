cmake_minimum_required(VERSION 3.0.0)
project(polylist VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(../common ../stack ../queue ../list)
add_executable(polylist main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
