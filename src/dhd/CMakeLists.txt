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

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(dhddir ${sdkdir}/lib/release/mac-arm64-clang/)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(dhddir ${sdkdir}/lib/release/lin-x86_64-gcc/)
else()
    message(FATAL_ERROR "Platform '${CMAKE_SYSTEM_NAME}' not supported.")
endif()

find_library(DHD REQUIRED
    NAMES dhd
    PATHS ${dhddir})
# Need DRD to connect with Sigma
find_library(DRD REQUIRED
    NAMES drd
    PATHS ${dhddir})

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # These are derived from the MacOS MakeFile, check other libraries for other platforms.
    find_library(IOKIT_LIB REQUIRED NAMES IOKit)
    find_library(CORE_FOUNDATION_LIB REQUIRED NAMES CoreFoundation)
    message(STATUS "IOKit: ${IOKIT_LIB}")
    message(STATUS "CoreFoundation: ${CORE_FOUNDATION_LIB}")
    set(LINK_LIBS ${IOKIT_LIB} ${CORE_FOUNDATION_LIB})
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_library(USB_LIB REQUIRED NAMES usb-1.0)
    set(LINK_LIBS ${USB_LIB})
endif()

message(STATUS "pybind11: ${pybinddir}")
message(STATUS "Force Dimension dhd: ${DHD}")
message(STATUS "Force Dimension drd: ${DRD}")

include_directories(${sdkdir}/include/)
link_directories(${dhddir})

pybind11_add_module(dhd src/bindings.cpp)
# set_target_properties(dhd PROPERTIES OUTPUT_NAME pyhaptic/dhd)
target_link_libraries(dhd PRIVATE ${DHD} ${DRD} ${LINK_LIBS})

target_compile_definitions(dhd PRIVATE)