cmake_minimum_required(VERSION 3.16)
project(pyhaptic)

add_subdirectory(pybind11)
pybind11_add_module(pyhaptic src/main.cpp)

target_compile_definitions(pyhaptic PRIVATE)