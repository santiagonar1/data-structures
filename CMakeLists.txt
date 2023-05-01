cmake_minimum_required(VERSION 3.22.0)
project(ds VERSION 0.1.0)

enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(CPack)

add_subdirectory(tests)
