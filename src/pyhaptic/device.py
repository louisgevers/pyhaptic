import pyhaptic.dhd as dhd

from typing import Optional, Tuple


class Device:
    def __init__(self, id: Optional[int] = None) -> None:
        if id is None:
            self._id = dhd.open()
        else:
            self._id = dhd.open_id(id)
        if self._id is None:
            raise ConnectionError(f"Could not connect to device (ID: {id})")

    def get_position(self) -> Tuple[float, float, float]:
        return dhd.get_position(self._id)

    def get_force(self) -> Tuple[float, float, float]:
        return dhd.get_force(self._id)

    def set_force(self, fx: float, fy: float, fz: float) -> None:
        dhd.set_force(fx, fy, fz, self._id)

    def enable_force(self, on: bool = True) -> None:
        dhd.enable_force(on, self._id)

    def close(self) -> None:
        dhd.close(self._id)
