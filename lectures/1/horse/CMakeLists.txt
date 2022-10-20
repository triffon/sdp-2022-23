cmake_minimum_required(VERSION 3.0.0)
project(horse VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(horse main.cpp horsewalker.cpp recursive_horsewalker.cpp)
include_directories(../common ../stack)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
