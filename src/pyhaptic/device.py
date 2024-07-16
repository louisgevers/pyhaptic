import pyhaptic.dhd as dhd

from typing import Optional, Tuple


class Device:
    def __init__(self, id: Optional[int] = None, auto_init: bool = True) -> None:
        if id is None:
            self._id = dhd.open()
        else:
            self._id = dhd.open_id(id)
        if self._id < 0:
            raise ConnectionError(f"Could not connect to device (ID: {id})")

        if auto_init and not self.is_initialized():
            self.auto_init() 

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
            self.close()
            raise PermissionError("Setting time guard requires expert mode!")
        dhd.set_time_guard(ms * 1000, self._id)

    def is_initialized(self) -> bool:
        return dhd.is_initialized(self._id)

    def move_to_pos(self, px: int, py: int, pz: int, blocking: bool = True):
        if not dhd.drd_is_supported(self._id):
            self.close()
            raise RuntimeError(f"DRD not supported out of the box on device with id {self._id}. Needs configuration, refer to DRD documentation.")
        if not self.is_initialized():
            self.auto_init()
        dhd.drd_start(self._id)
        dhd.drd_move_to_pos(px, py, pz, blocking, self._id)
        if blocking:
            dhd.drd_stop(self._id)

    def is_moving(self) -> bool:
        return dhd.drd_is_moving(self._id)

    def stop_tracking(self):
        dhd.drd_stop(True, self._id)

    def auto_init(self):
        dhd.auto_init(self._id)

    def set_base_z_angle(self, rad: float):
        dhd.set_angle_z_rad(rad, self._id)

    def get_base_z_angle(self, rad: float):
        return dhd.get_angle_z_rad(self._id)

    def close(self) -> None:
        dhd.close(self._id)
