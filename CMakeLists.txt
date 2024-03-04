cmake_minimum_required(VERSION 3.16)
project(pyhaptic)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory(pybind11)

set(sdkdir ${CMAKE_CURRENT_SOURCE_DIR}/external/force-dimension-sdk)

find_library(DHD REQUIRED
    NAMES dhd
    PATHS ${sdkdir}/lib/release/mac-arm64-clang/)

# These are derived from the MacOS MakeFile, check other libraries for other platforms.
find_library(IOKIT_LIB REQUIRED NAMES IOKit)
find_library(CORE_FOUNDATION_LIB REQUIRED NAMES CoreFoundation)

message(STATUS "Force Dimension dhd: ${DHD}")
message(STATUS "IOKit: ${IOKIT_LIB}")
message(STATUS "CoreFoundation: ${CORE_FOUNDATION_LIB}")

include_directories(${sdkdir}/include/)
link_directories(${sdkdir}/lib/release/mac-arm64-clang/)

pybind11_add_module(pyhaptic src/pyhaptic.cpp)
target_link_libraries(pyhaptic PRIVATE ${DHD} ${IOKIT_LIB} ${CORE_FOUNDATION_LIB})

target_compile_definitions(pyhaptic PRIVATE)