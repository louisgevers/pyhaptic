#include <iostream>
#include <chrono>
#include <thread>

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

void measure_position(int deviceId, int duration) {
    double avg = 0;
    double var = 0;
    double last_diff = 0;

    for (int i = 0; i < duration * 1000; ++i) {
        auto start = std::chrono::high_resolution_clock::now();

        double px, py, pz;
        dhdGetPosition(&px, &py, &pz, deviceId);

        auto end = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> diff = end - start;

        rolling_avg_var(avg, var, last_diff, diff.count(), i + 1);

        last_diff = diff.count();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    std::cout << "Call time (avg):\t" << avg * 1000 << "ms" << std::endl;
    std::cout << "Call time (std):\t" << std::sqrt(var) * 1000 << "ms" << std::endl;
}

void measure_force(int deviceId, int duration) {
    double avg = 0;
    double var = 0;
    double last_diff = 0;

    dhdEnableForce(DHD_ON, deviceId);
    for (int i = 0; i < duration * 1000; ++i) {
        auto start = std::chrono::high_resolution_clock::now();

        dhdSetForce(0, 0, 0, deviceId);

        auto end = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> diff = end - start;

        rolling_avg_var(avg, var, last_diff, diff.count(), i + 1);

        last_diff = diff.count();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    dhdEnableForce(DHD_OFF, deviceId);

    std::cout << "Call time (avg):\t" << avg * 1000 << "ms" << std::endl;
    std::cout << "Call time (std):\t" << std::sqrt(var) * 1000 << "ms" << std::endl;
}

int main() {
    const int id = dhdOpen();
    std::cout << "POSITION READINGS (native functions)" << std::endl;
    measure_position(id, 100);
    std::cout << "FORCE SETTING (native functions)" << std::endl;
    measure_force(id, 100);
    dhdClose(id);
}