import time
import pyhaptic

K = 200

def springmodel():
    if (id := pyhaptic.open()) < 0:
        print("Cannot connect to device.")
        return
    else:
        print(f"Connected to device ID = {id}")

    print("Running springmodel")
    pyhaptic.enable_force(True, id)
    for _ in range(1_000):
        px, py, pz = pyhaptic.get_position(id)
        fx = -K * px
        fy = -K * py
        fz = -K * pz
        pyhaptic.set_force(fx, fy, fz, id)
        time.sleep(0.01)

    print("Disconnecting device")
    pyhaptic.enable_force(False, id)
    pyhaptic.close(id)


if __name__ == "__main__":
    springmodel()