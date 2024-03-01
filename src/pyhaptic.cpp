#include <pybind11/pybind11.h>
#include <dhdc.h>

namespace py = pybind11;

// Define a function that takes a char ID but can take an int from python with default argument -1.
#define ID_DEF(m, name, function, out, description) m.def(name, reinterpret_cast<out (*)(int)>(function), py::arg("ID") = -1, description);

PYBIND11_MODULE(pyhaptic, m)
{
    m.doc() = "Python bindings for Force Dimension Haptic SDK.";

    // Connection management
    m.def("open", &dhdOpen, "This function opens a connection to the first available device connected to the system. The order in which devices are opened persists until devices are added or removed.");
    m.def("open_type", &dhdOpenType, "This function opens a connection to the first device of a given type connected to the system. The order in which devices are opened persists until devices are added or removed.");
    m.def("open_serial", &dhdOpenSerial, "This function opens a connection to the device with a given serial number (available on recent models only).");
    ID_DEF(m, "open_id", &dhdOpenID, int, "This function opens a connection to one particular device connected to the system. The order in which devices are opened persists until devices are added or removed. If the device at the specified index is already opened, its device ID is returned.");
    ID_DEF(m, "close", &dhdClose, int, "This function closes the connection to a particular device.");

    // Control
    m.def(
        "get_position", [](int ID)
        { double px, py, pz; dhdGetPosition(&px, &py, &pz, ID); return py::make_tuple(px, py, pz); },
        "This function retrieves the position of the end-effector in Cartesian coordinates. Please refer to your device user manual for more information on your device coordinate system.",
        py::arg("ID") = -1);
    m.def("set_force", reinterpret_cast<int (*)(double, double, double, int)>(&dhdSetForce), "This function sets the desired force vector in Cartesian coordinates to be applied to the end-effector of the device.", py::arg("fx"), py::arg("fy"), py::arg("fz"), py::arg("ID") = -1);

    // Force mode
    m.def("enable_force", reinterpret_cast<int (*)(bool, int)>(&dhdEnableForce), "This function enables the force mode in the device controller.", py::arg("on") = 1, py::arg("ID") = -1);

    // --- STANDARD SDK --
    // dhdEnableSimulator()
    // dhdGetDeviceCount()
    // dhdGetAvailableCount()
    // dhdSetDevice()
    // dhdGetDeviceID()
    // dhdGetSerialNumber()
    // dhdCheckControllerMemory()
    // dhdStop()
    // dhdGetComMode()
    // dhdEnableGripperForce()
    // dhdGetSystemType()
    // dhdGetSystemName()
    // dhdGetSystemRev()
    // dhdGetVersion()
    // dhdGetVersionStr()
    // dhdGetSDKVersion()
    // dhdGetSDKVersionStr()
    // dhdGetComponentVersionStr()
    // dhdGetStatus()
    // dhdGetDeviceAngleRad()
    // dhdGetDeviceAngleDeg()
    // dhdGetEffectorMass()
    // dhdGetSystemCounter()
    // dhdGetButton()
    // dhdGetButtonMask()
    // dhdSetOutput()
    // dhdIsLeftHanded()
    // dhdHasBase()
    // dhdHasWrist()
    // dhdHasActiveWrist()
    // dhdHasGripper()
    // dhdHasActiveGripper()
    // dhdReset()
    // dhdResetWrist()
    // dhdWaitForReset()
    // dhdSetStandardGravity()
    // dhdSetGravityCompensation()
    // dhdSetBrakes()
    // dhdSetDeviceAngleRad()
    // dhdSetDeviceAngleDeg()
    // dhdSetEffectorMass()
    // dhdGetForce()
    // dhdGetOrientationRad()
    // dhdGetOrientationDeg()
    // dhdGetPositionAndOrientationRad()
    // dhdGetPositionAndOrientationDeg()
    // dhdGetPositionAndOrientationFrame()
    // dhdGetForceAndTorque()
    // dhdSetForceAndTorque()
    // dhdGetOrientationFrame()
    // dhdGetGripperAngleDeg()
    // dhdGetGripperAngleRad()
    // dhdGetGripperGap()
    // dhdGetGripperThumbPos()
    // dhdGetGripperFingerPos()
    // dhdGetComFreq()
    // dhdSetForceAndGripperForce()
    // dhdSetForceAndTorqueAndGripperForce()
    // dhdGetForceAndTorqueAndGripperForce()
    // dhdConfigLinearVelocity()
    // dhdGetLinearVelocity()
    // dhdConfigAngularVelocity()
    // dhdGetAngularVelocityRad()
    // dhdGetAngularVelocityDeg()
    // dhdConfigGripperVelocity()
    // dhdGetGripperLinearVelocity()
    // dhdGetGripperAngularVelocityRad()
    // dhdGetGripperAngularVelocityDeg()
    // dhdEmulateButton()
    // dhdGetBaseAngleXRad()
    // dhdGetBaseAngleXDeg()
    // dhdSetBaseAngleXRad()
    // dhdSetBaseAngleXDeg()
    // dhdGetBaseAngleZRad()
    // dhdGetBaseAngleZDeg()
    // dhdSetBaseAngleZRad()
    // dhdSetBaseAngleZDeg()
    // dhdSetVibration()
    // dhdSetMaxForce()
    // dhdSetMaxTorque()
    // dhdSetMaxGripperForce()
    // dhdGetMaxForce()
    // dhdGetMaxTorque()
    // dhdGetMaxGripperForce()

    // -- ERROR MANAGEMENT --
    // dhdErrorGetLast()
    // dhdErrorGetLastStr()
    // dhdErrorGetStr()

    // -- OS-independent SDK
    // dhdKbHit()
    // dhdKbGet()
    // dhdGetTime()
    // dhdSleep()
    // dhdStartThread()
}