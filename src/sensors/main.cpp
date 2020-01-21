#include "mdp.h"
#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>



uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

int main() {
    // flight loop
    
    uint64_t start_time = timeSinceEpochMillisec();
    while (true) {
        // Initalize MDP
        int timestamp = timeSinceEpochMillisec() - start_time;
        MDP mdp(timestamp);
        short arr[3] = {1,2,3};
        mdp.set_accel(arr);
        mdp.set_gyro(arr);
        std::cout << mdp.print_as_JSON() << std::endl;
    }
    return 0;
} 