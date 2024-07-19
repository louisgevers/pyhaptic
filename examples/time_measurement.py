import time
import pyhaptic
import math

def rolling_avg_var(avg: float, var: float, old_sample: float, sample: float, n: int):
    new_avg = avg + (sample - old_sample) / n
    if n > 1:
        new_var = var + (sample - old_sample) * (sample - new_avg + old_sample - avg) / (n - 1)
    else:
        new_var = 0
    return new_avg, new_var

def measure_timings(device: pyhaptic.Device, duration: int):
    avg = 0
    var = 0
    last_diff = 0
    min, max = 1000, 0
    device.enable_force(True)
    for i in range(1_00 * duration):
        start = time.time()
        px, py, pz = device.get_position()
        device.set_force(0, 0, 0)
        diff = time.time() - start
        avg, var = rolling_avg_var(avg, var, last_diff, diff, n=i + 1)
        time.sleep(0.01)
        last_diff = diff
        if last_diff > max:
            max = last_diff
        if last_diff < min:
            min = last_diff
    device.enable_force(False)

    print(f"Call time (avg):\t{avg * 1_000}ms")
    print(f"Call time (std):\t{math.sqrt(var) * 1_000}ms")
    print(f"Call time (min):\t{min * 1_000}ms")
    print(f"Call time (max):\t{max * 1_000}ms")


if __name__ == "__main__":
    device = pyhaptic.Device()
    print("POSITION READINGS AND FORCE SETTINGS (python bindings)")
    measure_timings(device, duration=100)
    device.close()