#include "mdp.h"
#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>



uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void write_to_disk(char * str) {    
    FILE *fp;
    fp = fopen("tmp/data.txt", "w+");
    fprintf(fp, str);
}

int main() {
    // flight loop
    
    uint64_t start_time = timeSinceEpochMillisec();

    std::thread file_thread;
    char * first_line = "=======Start of data logging=======";
    file_thread = std::thread(write_to_disk, first_line);

    while (true) {

        // Initalize MDP
        int timestamp = timeSinceEpochMillisec() - start_time;
        MDP mdp(timestamp);
        short arr[3] = {1,2,3};
        mdp.set_accel(arr);
        mdp.set_gyro(arr);
        // std::cout << mdp.print_as_JSON() << std::endl;

        char * write_string  = mdp.print_as_JSON();

        // Wait for previous write to finish
        file_thread.join();

        file_thread = std::thread(write_to_disk, write_string);


    }
    return 0;
} 