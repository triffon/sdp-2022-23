cmake_minimum_required(VERSION 3.0.0)
project(dictionary VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(dictionary main.cpp)

include_directories( ../common ../list ../tree)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
