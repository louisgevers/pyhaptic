#include <pybind11/pybind11.h>
#include <dhdc.h>

namespace py = pybind11;

template <typename Function>
struct ReturnType;

// Define a function that takes a char ID but can take an int from python with default argument -1.
template <typename Function>
void def_id(py::module &m, const char *name, Function &&function, const char *description)
{
    using OutputType = std::invoke_result_t<Function, int>;
    m.def(name, reinterpret_cast<OutputType (*)(int)>(function), description, py::arg("ID") = -1);
}

template <typename Function>
void def_get1d(py::module &m, const char *name, Function &&function, const char *description)
{
    using OutputType = std::invoke_result_t<Function, double *, int>;
    m.def(
        name, [=](int ID)
        {double arg0; function(&arg0, ID); return arg0; },
        description, py::arg("ID") = -1);
}

template <typename Function>
void def_get3d(py::module &m, const char *name, Function &&function, const char *description)
{
    using OutputType = std::invoke_result_t<Function, double *, double *, double *, int>;
    m.def(
        name, [=](int ID)
        {double arg0, arg1, arg2; function(&arg0, &arg1, &arg2, ID); return py::make_tuple(arg0, arg1, arg2); },
        description, py::arg("ID") = -1);
}

template <typename Function>
void def_get6d(py::module &m, const char *name, Function &&function, const char *description)
{
    using OutputType = std::invoke_result_t<Function, double *, double *, double *, double *, double *, double *, int>;
    m.def(
        name, [=](int ID)
        {double arg0, arg1, arg2, arg3, arg4, arg5; function(&arg0, &arg1, &arg2, &arg3, &arg4, &arg5, ID); return py::make_tuple(arg0, arg1, arg2, arg3, arg4, arg5); },
        description, py::arg("ID") = -1);
}

template <typename Function>
void def_get7d(py::module &m, const char *name, Function &&function, const char *description)
{
    using OutputType = std::invoke_result_t<Function, double *, double *, double *, double *, double *, double *,double *, int>;
    m.def(
        name, [=](int ID)
        {double arg0, arg1, arg2, arg3, arg4, arg5, arg6; function(&arg0, &arg1, &arg2, &arg3, &arg4, &arg5, &arg6, ID); return py::make_tuple(arg0, arg1, arg2, arg3, arg4, arg5, arg6); },
        description, py::arg("ID") = -1);
}

template <typename Function>
void def_set1b(py::module &m, const char *name, Function &&function, const char *arg0, const char *description)
{
    using OutputType = std::invoke_result_t<Function, bool, int>;
    m.def(name, reinterpret_cast<OutputType (*)(bool, int)>(function), description, py::arg(arg0), py::arg("ID") = -1);
}

template <typename Function>
void def_set1i(py::module &m, const char *name, Function &&function, const char *arg0, const char *description)
{
    using OutputType = std::invoke_result_t<Function, int, int>;
    m.def(name, reinterpret_cast<OutputType (*)(int, int)>(function), description, py::arg(arg0), py::arg("ID") = -1);
}

template <typename Function>
void def_set1d(py::module &m, const char *name, Function &&function, const char *arg0, const char *description)
{
    using OutputType = std::invoke_result_t<Function, double, int>;
    m.def(name, reinterpret_cast<OutputType (*)(double, int)>(function), description, py::arg(arg0), py::arg("ID") = -1);
}

template <typename Function>
void def_set3d(py::module &m, const char *name, Function &&function, const char *arg0, const char *arg1, const char *arg2, const char *description)
{
    using OutputType = std::invoke_result_t<Function, double, double, double, int>;
    m.def(name, reinterpret_cast<OutputType (*)(double, double, double, int)>(function), description, py::arg(arg0), py::arg(arg1), py::arg(arg2), py::arg("ID") = -1);
}

template <typename Function>
void def_set4d(py::module &m, const char *name, Function &&function, const char *arg0, const char *arg1, const char *arg2, const char *arg3, const char *description)
{
    using OutputType = std::invoke_result_t<Function, double, double, double, double, int>;
    m.def(name, reinterpret_cast<OutputType (*)(double, double, double, double, int)>(function), description, py::arg(arg0), py::arg(arg1), py::arg(arg2), py::arg(arg3), py::arg("ID") = -1);
}

template <typename Function>
void def_set6d(py::module &m, const char *name, Function &&function, const char *arg0, const char *arg1, const char *arg2, const char *arg3, const char *arg4, const char *arg5, const char *description)
{
    using OutputType = std::invoke_result_t<Function, double, double, double, double, double, double, int>;
    m.def(name, reinterpret_cast<OutputType (*)(double, double, double, double, double, double, int)>(function), description, py::arg(arg0), py::arg(arg1), py::arg(arg2), py::arg(arg3), py::arg(arg4), py::arg(arg5), py::arg("ID") = -1);
}

template <typename Function>
void def_set7d(py::module &m, const char *name, Function &&function, const char *arg0, const char *arg1, const char *arg2, const char *arg3, const char *arg4, const char *arg5, const char *arg6, const char *description)
{
    using OutputType = std::invoke_result_t<Function, double, double, double, double, double, double, double, int>;
    m.def(name, reinterpret_cast<OutputType (*)(double, double, double, double, double, double, double, int)>(function), description, py::arg(arg0), py::arg(arg1), py::arg(arg2), py::arg(arg3), py::arg(arg4), py::arg(arg5), py::arg(arg6), py::arg("ID") = -1);
}

PYBIND11_MODULE(dhd, m)
{
    m.attr("__name__") = "pyhaptic.dhd";
    m.doc() = "Python bindings for Force Dimension Haptic SDK.";

    // Connection management
    m.def("open", &dhdOpen, "This function opens a connection to the first available device connected to the system. The order in which devices are opened persists until devices are added or removed.");
    m.def("open_type", &dhdOpenType, "This function opens a connection to the first device of a given type connected to the system. The order in which devices are opened persists until devices are added or removed.");
    m.def("open_serial", &dhdOpenSerial, "This function opens a connection to the device with a given serial number (available on recent models only).");
    def_id(m, "open_id", &dhdOpenID, "This function opens a connection to one particular device connected to the system. The order in which devices are opened persists until devices are added or removed. If the device at the specified index is already opened, its device ID is returned.");
    def_id(m, "close", &dhdClose, "This function closes the connection to a particular device.");

    // Control
    def_get3d(m, "get_position", &dhdGetPosition, "This function retrieves the position of the end-effector in Cartesian coordinates. Please refer to your device user manual for more information on your device coordinate system.");
    def_get3d(m, "get_force", &dhdGetForce, "This function retrieves the force vector applied to the end-effector.");
    def_set3d(m, "set_force", &dhdSetForce, "fx", "fy", "fz", "This function sets the desired force vector in Cartesian coordinates to be applied to the end-effector of the device.");
    def_get3d(m, "get_orientation_rad", &dhdGetOrientationRad, "For devices with a wrist structure, this function retrieves individual angle of each joint, starting with the one located nearest to the wrist base plate. For the DHD_DEVICE_OMEGA6_RIGHT and DHD_DEVICE_OMEGA6_LEFT devices, angles are computed with respect to their internal reference frame, which is rotated 45 degrees around the Y axis. Please refer to your device user manual for more information on your device coordinate system.");
    def_get3d(m, "get_orientation_deg", &dhdGetOrientationDeg, "For devices with a wrist structure, this function retrieves individual angle of each joint, starting with the one located nearest to the wrist base plate. For the DHD_DEVICE_OMEGA6_RIGHT and DHD_DEVICE_OMEGA6_LEFT devices, angles are computed with respect to their internal reference frame, which is rotated 45 degrees around the Y axis. Please refer to your device user manual for more information on your device coordinate system.");
    def_get6d(m, "get_position_and_orientation_rad", &dhdGetPositionAndOrientationRad, "This function retrieves the position and orientation of the end-effector in Cartesian coordinates. For devices with a wrist structure, the orientation is expressed as the individual angle of each joint, starting with the one located nearest to the wrist base plate. For the DHD_DEVICE_OMEGA6_RIGHT and DHD_DEVICE_OMEGA6_LEFT devices, angles are computed with respect to their internal reference frame, which is rotated 45 degrees around the Y axis. Please refer to your device user manual for more information on your device coordinate system.");
    def_get6d(m, "get_position_and_orientation_deg", &dhdGetPositionAndOrientationDeg, "This function retrieves the position and orientation of the end-effector in Cartesian coordinates. For devices with a wrist structure, the orientation is expressed as the individual angle of each joint, starting with the one located nearest to the wrist base plate. For the DHD_DEVICE_OMEGA6_RIGHT and DHD_DEVICE_OMEGA6_LEFT devices, angles are computed with respect to their internal reference frame, which is rotated 45 degrees around the Y axis. Please refer to your device user manual for more information on your device coordinate system.");
    def_get6d(m, "get_force_and_torque", &dhdGetForceAndTorque, "This function retrieves the force and torque vectors applied to the device end-effector.");
    def_set6d(m, "set_force_and_torque", &dhdSetForceAndTorque, "fx", "fy", "fz", "tx", "ty", "tz", "This function sets the desired force and torque vectors to be applied to the device end-effector.");
    def_set4d(m, "set_force_and_gripper_force", &dhdSetForceAndGripperForce, "fx", "fy", "fz", "fg", "This function sets the desired force vector in Cartesian coordinates and the desired grasping force to be applied to the device end-effector and force gripper.");
    def_set7d(m, "set_force_and_torque_and_gripper_force", &dhdSetForceAndTorqueAndGripperForce, "fx", "fy", "fz", "tx", "ty", "tz", "fg", "This function sets the desired force and torque vectors in Cartesian coordinates and the desired grasping force to be applied to the device end-effector and force gripper.");
    def_get7d(m, "get_force_and_torque_and_gripper_force", &dhdGetForceAndTorqueAndGripperForce, "This function retrieves the force and torque vectors applied to the device end-effector, as well as the force applied to the gripper.");
    def_get3d(m, "get_linear_velocity", &dhdGetLinearVelocity, "This function retrieves the estimated instantaneous translational velocity. Velocity computation can be configured by calling dhdConfigLinearVelocity(). By default DHD_VELOCITY_WINDOW and DHD_VELOCITY_WINDOWING are used. See velocity estimator for details.");
    def_get3d(m, "get_angular_velocity_rad", &dhdGetAngularVelocityRad, "This function retrieves the estimated instantaneous angular velocity in [rad/s]. Velocity computation can be configured by calling dhdConfigAngularVelocity(). By default DHD_VELOCITY_WINDOW and DHD_VELOCITY_WINDOWING are used. See velocity estimator for details.");
    def_get3d(m, "get_angular_velocity_deg", &dhdGetAngularVelocityDeg, "This function retrieves the estimated instantaneous angular velocity in [deg/s]. Velocity computation can be configured by calling dhdConfigAngularVelocity(). By default DHD_VELOCITY_WINDOW and DHD_VELOCITY_WINDOWING are used. See velocity estimator for details.");
    def_get1d(m, "get_gripper_linear_velocity", &dhdGetGripperLinearVelocity, "This function retrieves the estimated instantaneous linear velocity of the gripper in [m/s]. Velocity computation can be configured by calling dhdConfigGripperVelocity(). By default DHD_VELOCITY_WINDOW and DHD_VELOCITY_WINDOWING are used. See velocity estimator for details.");
    def_get1d(m, "get_gripper_angular_velocity_rad", &dhdGetGripperAngularVelocityRad, "This function retrieves the estimated instantaneous angular velocity of the gripper in [rad/s]. Velocity computation can be configured by calling dhdConfigGripperVelocity(). By default DHD_VELOCITY_WINDOW and DHD_VELOCITY_WINDOWING are used. See velocity estimator for details.");
    def_get1d(m, "get_gripper_angular_velocity_deg", &dhdGetGripperAngularVelocityDeg, "This function retrieves the estimated instantaneous angular velocity of the gripper in [deg/s]. Velocity computation can be configured by calling dhdConfigGripperVelocity(). By default DHD_VELOCITY_WINDOW and DHD_VELOCITY_WINDOWING are used. See velocity estimator for details.");
    def_set1d(m, "set_max_force", &dhdSetMaxForce, "f", "This function defines a limit (in N) to the force magnitude that can be applied by the haptic device. The f N limit applies to all dhdSetForce() and related calls, and ensures that the force applied to the device end-effector remains below the requested value. If the f argument is negative, the limit is disabled and the full range of force available can be applied.");
    def_id(m, "get_max_force", &dhdGetMaxForce, "This function retrieves the current limit (in N) to the force magnitude that can be applied by the haptic device. If the return value is negative, the limit is disabled and the full range of force available can be applied.");
    def_set1d(m, "set_max_torque", &dhdSetMaxTorque, "t", "This function defines a limit (in Nm) to the torque magnitude that can be applied by the haptic device. The t Nm limit applies to all dhdSetForceAndTorque() and related calls, and ensures that the torque applied to the device end-effector remains below the requested value. If the t argument is negative, the limit is disabled and the full range of torque available can be applied.");
    def_id(m, "get_max_torque", &dhdGetMaxTorque, "This function retrieves the current limit (in Nm) to the torque magnitude that can be applied by the haptic device. If the return value is negative, the limit is disabled and the full range of torque available can be applied.");
    def_set1d(m, "set_max_gripper_force", &dhdSetMaxGripperForce, "f", "This function defines a limit (in N) to the force magnitude that can be applied by the haptic device gripper. The f N limit applies to dhdSetForceAndTorqueAndGripperForce() and related calls, and ensures that the force applied to the device gripper remains below the requested value. If the f argument is negative, the limit is disabled and the full range of gripper force available can be applied.");
    def_id(m, "get_max_gripper_force", &dhdGetMaxGripperForce, "This function retrieves the current limit (in N) to the force magnitude that can be applied by the haptic device gripper. If the return value is negative, the limit is disabled and the full range of gripper force available can be applied.");

    // Force mode
    def_set1b(m, "enable_force", &dhdEnableForce, "on", "This function enables the force mode in the device controller.");
    def_id(m, "stop", &dhdStop, "This function stops all forces on the device. This routine disables the force on the haptic device and puts it into BRAKE mode.");
    def_id(m, "reset", &dhdReset, "This function puts the device in RESET mode.");
    def_set1i(m, "wait_for_reset", &dhdWaitForReset, "timeout", "This function puts the device in RESET mode and wait for the user to calibrate the device. Optionally, a timeout can be defined after which the call returns even if calibration has not occurred.");
    def_set1d(m, "set_standard_gravity", &dhdSetStandardGravity, "g", "This function sets the standard gravity constant used in gravity compensation. By default, the constant is set to 9.81 m/s^2.");
    def_set1b(m, "set_gravity_compensation", &dhdSetGravityCompensation, "on", "This function toggles the use of the gravity compensation feature.");
    def_set1b(m, "set_brakes", &dhdSetBrakes, "on", "This function toggles the device electromagnetic brakes state.");

    // Buttons
    m.def("get_button", reinterpret_cast<int (*)(int, int)>(&dhdGetButton), "This function returns the status of the button located on the end-effector.");
    def_id(m, "get_button_mask", &dhdGetButtonMask, "This function returns the 32-bit binary mask of the device buttons.");

    // Gripper
    def_set1b(m, "enable_gripper_force", &dhdEnableGripperForce, "on", "This function enables the gripper force mode in the device controller. This function is only relevant to devices that have a gripper with a default closed or opened state. It does not apply to the sigma.x and omega.x range of devices, whose gripper does not have a default state. For those devices, the gripper force is enabled/disabled by dhdEnableForce().");
    def_get1d(m, "get_gripper_angle_deg", &dhdGetGripperAngleDeg, "This function retrieves the gripper opening angle in degrees.");
    def_get1d(m, "get_gripper_angle_rad", &dhdGetGripperAngleRad, "This function retrieves the gripper opening angle in radians.");
    def_get1d(m, "get_gripper_gap", &dhdGetGripperGap, "This function retrieves the gripper opening distance in meters.");
    def_get3d(m, "get_gripper_thumb_pos", &dhdGetGripperThumbPos, "This function retrieves the position in Cartesian coordinates of thumb rest location of the force gripper structure if present.");
    def_get3d(m, "get_gripper_finger_pos", &dhdGetGripperFingerPos, "This function retrieves the position in Cartesian coordinates of forefinger rest location of the force gripper structure if present.");

    // Device management
    m.def("get_device_count", &dhdGetDeviceCount, "This function returns the number of compatible Force Dimension devices connected to the system. This encompasses all devices connected locally, including devices already locked by other applications. Devices are given a unique identifier, as explained in the multiple devices section.");
    m.def("get_available_count", &dhdGetAvailableCount, "This function returns the number of available Force Dimension devices connected to the system. This encompasses all devices connected locally, but excludes devices already locked by other applications. Devices are given a unique identifier, as explained in the multiple devices section.");
    def_id(m, "set_device", &dhdSetDevice, "This function selects the default device that will receive the SDK commands. The SDK supports multiple devices. This routine allows the programmer to decide which device the SDK dhd_single_device_call single-device calls will address. Any subsequent SDK call that does not specifically mention the device ID in its parameter list will be sent to that device.");
    m.def("get_device_id", &dhdGetDeviceID, "This function returns the ID of the current default device.");
    def_id(m, "is_left_handed", &dhdIsLeftHanded, "This function returns true if the device is configured for left-handed use, false otherwise.");
    def_id(m, "get_com_freq", &dhdGetComFreq, "This function returns the communication refresh rate between the computer and the device. Refresh rate computation is based on function calls that apply a force on the device (e.g. dhdSetForce()).");

    // Device base
    def_get1d(m, "get_angle_rad", &dhdGetDeviceAngleRad, "This function retrieves the device base plate angle around the Y axis.");
    def_set1d(m, "set_angle_rad", &dhdSetDeviceAngleRad, "angle", "This function sets the device base plate angle around the (inverted) Y axis. Please refer to your device user manual for more information on your device coordinate system. An angle value of 0 corresponds to the device \"upright\" position, with its base plate perpendicular to axis X. An angle value of Pi/2 corresponds to the device base plate resting horizontally.");
    def_get1d(m, "get_angle_deg", &dhdGetDeviceAngleDeg, "This function retrieves the device base plate angle around the Y axis.");
    def_set1d(m, "set_angle_deg", &dhdSetDeviceAngleDeg, "angle", "This function sets the device base plate angle around the (inverted) Y axis. Please refer to your device user manual for more information on your device coordinate system. An angle value of 0 corresponds to the device \"upright\" position, with its base plate perpendicular to axis X. An angle value of 90 corresponds to the device base plate resting horizontally.");

    // Error management
    m.def("get_last_error", &dhdErrorGetLast, "Returns the last error code encountered in the running thread. See error management for details");
    m.def("get_last_error_str", &dhdErrorGetLastStr, "Returns a brief string describing the last error encountered in the running thread. See error management for details.");
    m.def("get_error_str", &dhdErrorGetStr, "Returns a brief string describing a given error code. See error management for details.");

    // SDK
    m.def("get_sdk_version", &dhdGetSDKVersion, "This function returns the SDK complete set of version numbers.");
    m.def("get_sdk_version_str", &dhdGetSDKVersionStr, "This function returns a string that fully describes the SDK version.");

    // - REMAINING FUNCTIONS TO BE IMPLEMENTED -
    // --- STANDARD SDK --
    // dhdEnableSimulator()
    // dhdGetSerialNumber()
    // dhdCheckControllerMemory()
    // dhdGetComMode()
    // dhdGetSystemType()
    // dhdGetSystemName()
    // dhdGetSystemRev()
    // dhdGetVersion()
    // dhdGetVersionStr()
    // dhdGetComponentVersionStr()
    // dhdGetStatus()
    // dhdGetEffectorMass()
    // dhdGetSystemCounter()
    // dhdSetOutput()
    // dhdHasBase()
    // dhdHasWrist()
    // dhdHasActiveWrist()
    // dhdHasGripper()
    // dhdHasActiveGripper()
    // dhdResetWrist()
    // dhdSetEffectorMass()
    // dhdGetPositionAndOrientationFrame()
    // dhdGetOrientationFrame()
    // dhdConfigLinearVelocity()
    // dhdConfigAngularVelocity()
    // dhdConfigGripperVelocity()
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

    // -- OS-independent SDK
    // dhdKbHit()
    // dhdKbGet()
    // dhdGetTime()
    // dhdSleep()
    // dhdStartThread()
}