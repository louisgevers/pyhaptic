import time
import pyhaptic

K = 200

def springmodel():
    device = pyhaptic.Device()

    device.enable_force(True)
    for _ in range(1_000):
        px, py, pz = device.get_position()
        fx = -K * px
        fy = -K * py
        fz = -K * pz
        device.set_force(fx, fy, fz)
        time.sleep(0.01)

    device.enable_force(False)
    device.close()


if __name__ == "__main__":
    springmodel()