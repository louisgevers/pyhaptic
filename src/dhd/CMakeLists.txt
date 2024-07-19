cmake_minimum_required(VERSION 3.16)
project(dhd)

set(CMAKE_CXX_STANDARD 17)

#  Detect OS
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(OS "mac")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(OS "lin")
else()
    message(FATAL_ERROR "Platform '${CMAKE_SYSTEM_NAME}' not supported.")
endif()

# Detect architecture
set(ARCH ${CMAKE_SYSTEM_PROCESSOR})

# Detect compiler
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILER "gcc")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    set(COMPILER "clang")
else()
    message(FATAL_ERROR "Compiler '${CMAKE_CXX_COMPILER_ID}' not supported.")
endif()

# Fetch the location of DHD library
# 1. Check Chai3D installation (compatible with older sigma devices)
if(DEFINED ENV{CHAI3D} AND NOT ${ARCH} STREQUAL "arm64") # No support for arm
    set(sdkdir $ENV{CHAI3D}/external/DHD)
    set(libdir lib)
# 2. Check force dimension SDK installation 
elseif(DEFINED ENV{FORCE_DIMENSION_SDK})
    set(sdkdir $ENV{FORCE_DIMENSION_SDK})
    set(libdir lib/release)
# 3. Fall back to local install
else()
    set(sdkdir ${CMAKE_CURRENT_SOURCE_DIR}/include/force-dimension-sdk)
    set(libdir lib/release)
endif()

# Fetch dhd library location
if (EXISTS "${sdkdir}/${libdir}/${OS}-${ARCH}-${COMPILER}")
    set(dhddir "${sdkdir}/${libdir}/${OS}-${ARCH}-${COMPILER}")
elseif (EXISTS "${sdkdir}/${libdir}/${OS}-${ARCH}")
    set(dhddir "${sdkdir}/${libdir}/${OS}-${ARCH}")
else()
    message(FATAL_ERROR "Could not find DHD library in ${sdkdir}/${libdir} (${OS}-${ARCH}-${COMPILER})")
endif()
message(STATUS "Using DHD library in: ${dhddir}")


# DHD is included in DRD
find_library(DRD REQUIRED
    NAMES drd
    PATHS ${dhddir})

# Dependencies for Haptic SDK
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    find_library(IOKIT_LIB REQUIRED NAMES IOKit)
    find_library(CORE_FOUNDATION_LIB REQUIRED NAMES CoreFoundation)
    message(STATUS "IOKit: ${IOKIT_LIB}")
    message(STATUS "CoreFoundation: ${CORE_FOUNDATION_LIB}")
    set(LINK_LIBS ${IOKIT_LIB} ${CORE_FOUNDATION_LIB})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_library(USB_LIB REQUIRED NAMES usb-1.0)
    set(LINK_LIBS ${USB_LIB})
endif()

# Python bindings
set(pybinddir ${CMAKE_CURRENT_SOURCE_DIR}/include/pybind11)
add_subdirectory(${pybinddir})

message(STATUS "pybind11: ${pybinddir}")
message(STATUS "Force Dimension DRD: ${DRD}")

include_directories(${sdkdir}/include/)
link_directories(${dhddir})

pybind11_add_module(dhd src/bindings.cpp)

target_link_libraries(dhd PRIVATE ${DHD} ${DRD} ${LINK_LIBS})

target_compile_definitions(dhd PRIVATE)

add_executable(time_measurement ${CMAKE_CURRENT_SOURCE_DIR}/src/time_measurement.cpp)
target_link_libraries(time_measurement PRIVATE ${DHD} ${DRD} ${LINK_LIBS})