cmake_minimum_required(VERSION 3.16)
project(dhd)

set (CMAKE_CXX_STANDARD 17)


set(pybinddir ${CMAKE_CURRENT_SOURCE_DIR}/include/pybind11)
# Use environment variable if it exists, otherwise local install
if (DEFINED ENV{FORCE_DIMENSION_SDK})
    set(sdkdir $ENV{FORCE_DIMENSION_SDK})
else()
    set(sdkdir ${CMAKE_CURRENT_SOURCE_DIR}/include/force-dimension-sdk)
endif()

message(STATUS "Force Dimension SDK: ${sdkdir}")

add_subdirectory(${pybinddir})

find_library(DHD REQUIRED
    NAMES dhd
    PATHS ${sdkdir}/lib/release/mac-arm64-clang/)

# These are derived from the MacOS MakeFile, check other libraries for other platforms.
find_library(IOKIT_LIB REQUIRED NAMES IOKit)
find_library(CORE_FOUNDATION_LIB REQUIRED NAMES CoreFoundation)

message(STATUS "pybind11: ${pybinddir}")
message(STATUS "Force Dimension dhd: ${DHD}")
message(STATUS "IOKit: ${IOKIT_LIB}")
message(STATUS "CoreFoundation: ${CORE_FOUNDATION_LIB}")

include_directories(${sdkdir}/include/)
link_directories(${sdkdir}/lib/release/mac-arm64-clang/)

pybind11_add_module(dhd src/bindings.cpp)
# set_target_properties(dhd PROPERTIES OUTPUT_NAME pyhaptic/dhd)
target_link_libraries(dhd PRIVATE ${DHD} ${IOKIT_LIB} ${CORE_FOUNDATION_LIB})

target_compile_definitions(dhd PRIVATE)