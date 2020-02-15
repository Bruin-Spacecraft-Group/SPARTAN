#ifndef MDP_H
#define MDP_H   

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "../globals.h"

class MDP
{
public:

    void set_accel(float accel[3]) {
        d_accel = accel;
    }
    
    void set_gyro(float gyro[3]) {
        d_gyro = gyro;
    }

    char * print_as_JSON() {
        char * str ;
        std::sprintf(str, "{\"timestamp\": %d, \"temp\": %.10f, \"d_accel\": [%.10f, %.10f, %.10f], \"d_gyro\": [%.10f, %.10f, %.10f]}", 
            timestamp, 
            temp_from_IMU,
            d_accel[0], 
            d_accel[1], 
            d_accel[2], 
            d_gyro[0], 
            d_gyro[1], 
            d_gyro[2]
        );
        return str;
    }

    

    MDP(int time) {
        timestamp = time;
    }
// private: 
    float * d_accel;
    float * d_gyro;
    float temp_from_IMU;
    int timestamp;
};

#endif