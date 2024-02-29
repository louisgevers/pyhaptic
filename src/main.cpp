#include <pybind11/pybind11.h>

int add(int a, int b) {
    return a + b;
}

PYBIND11_MODULE(pyhaptic, m) {
    m.doc() = "Python bindings for Force Dimension Haptic SDK.";

    m.def("add", &add, "Test function.");
}