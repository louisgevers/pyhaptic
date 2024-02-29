#include <pybind11/pybind11.h>
#include <dhdc.h>

PYBIND11_MODULE(pyhaptic, m)
{
    m.doc() = "Python bindings for Force Dimension Haptic SDK.";

    m.def("open", &dhdOpen, "This function opens a connection to the first available device connected to the system. The order in which devices are opened persists until devices are added or removed.");
    m.def("open_type", &dhdOpenType, "This function opens a connection to the first device of a given type connected to the system. The order in which devices are opened persists until devices are added or removed.");
    m.def("open_serial", &dhdOpenSerial, "This function opens a connection to the device with a given serial number (available on recent models only).");
    m.def("open_id", &dhdOpenID, "This function opens a connection to one particular device connected to the system. The order in which devices are opened persists until devices are added or removed. If the device at the specified index is already opened, its device ID is returned.");
    m.def("close", &dhdClose, "This function closes the connection to a particular device.");

    // TODO add other functions here

}