#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

#include <dhdc.h>

void rolling_avg_var(double& avg, double& var, double old_sample, double sample, int n) {
    double new_avg = avg + (sample - old_sample) / n;
    if (n > 1) {
        var += (sample - old_sample) * (sample - new_avg + old_sample - avg) / (n - 1);
    } else {
        var = 0;
    }
    avg = new_avg;
}

void measure_timings(int deviceId, int duration) {
    double avg = 0;
    double var = 0;
    double last_diff = 0;
    double min = 10000;
    double max = 0;

    dhdEnableForce(DHD_ON, deviceId);
    for (int i = 0; i < duration * 100; ++i) {
        auto start = std::chrono::high_resolution_clock::now();

        double px, py, pz;
        dhdGetPosition(&px, &py, &pz, deviceId);
        dhdSetForce(0, 0, 0, deviceId);

        auto end = std::chrono::high_resolution_clock::now();
        const std::chrono::microseconds diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        rolling_avg_var(avg, var, last_diff, diff.count(), i + 1);

        last_diff = diff.count();

        if (last_diff < min) {
            min = last_diff;
        } 
        if (last_diff > max) {
            max = last_diff;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    dhdEnableForce(DHD_OFF, deviceId);

    std::cout << "Call time (avg):\t" << avg / 1000 << "ms" << std::endl;
    std::cout << "Call time (std):\t" << std::sqrt(var) / 1000 << "ms" << std::endl;
    std::cout << "Call time (min):\t" << min / 1000 << "ms" << std::endl;
    std::cout << "Call time (max):\t" << max / 1000 << "ms" << std::endl;
}

int main() {
    const int id = dhdOpen();
    std::cout << "POSITION READINGS AND FORCE SETTING (native functions)" << std::endl;
    measure_timings(id, 100);
    dhdClose(id);
}