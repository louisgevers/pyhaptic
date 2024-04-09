import pyhaptic.dhd as dhd

from typing import Optional, Tuple


class Device:
    def __init__(self, id: Optional[int] = None) -> None:
        if id is None:
            self._id = dhd.open()
        else:
            self._id = dhd.open_id(id)
        if self._id < 0:
            raise ConnectionError(f"Could not connect to device (ID: {id})")

        self._expert_mode = False

    def get_position(self) -> Tuple[float, float, float]:
        return dhd.get_position(self._id)

    def get_orientation(self) -> Tuple[float, float, float]:
        return dhd.get_orientation_rad(self._id)

    def get_position_and_orientation(self) -> Tuple[float, float, float]:
        return dhd.get_position_and_orientation_rad(self._id)

    def get_force(self) -> Tuple[float, float, float]:
        return dhd.get_force(self._id)
    
    def set_force(self, fx: float, fy: float, fz: float) -> None:
        dhd.set_force(fx, fy, fz, self._id)

    def get_force_and_torque(self) -> Tuple[float, float, float, float, float, float]:
        return dhd.get_force_and_torque(self._id)

    def set_force_and_torque(self, fx: float, fy: float, fz: float, tx: float, ty: float, tz: float) -> None:
        dhd.set_force_and_torque(fx, fy, fz, tx, ty, tz, self._id)

    def enable_force(self, on: bool = True) -> None:
        dhd.enable_force(on, self._id)

    def enable_gravity_compensation(self, on: bool = True) -> None:
        dhd.set_gravity_compensation(on, self._id)

    def get_frequency(self) -> float:
        return dhd.get_com_freq(self._id)

    def set_expert_mode(self, on: bool) -> None:
        dhd.enable_expert_mode() if on else dhd.disable_expert_mode()
        self._expert_mode = on

    def set_time_guard(self, ms: int) -> None:
        if not self._expert_mode:
            raise PermissionError("Setting time guard requires expert mode!")
        dhd.set_time_guard(ms * 1000)


    def close(self) -> None:
        dhd.close(self._id)
