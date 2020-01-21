#ifndef MDP_H
#define MDP_H   

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "../globals.h"

class MDP
{
public:

    void set_accel(short accel[3]) {
        d_accel = accel;
    }
    
    void set_gyro(short gyro[3]) {
        d_gyro = gyro;
    }

    char * print_as_JSON() {
        char * str = new char[50];
        std::sprintf(str, "{\"timestamp\": %d, \"d_accel\": [%d, %d, %d], \"d_gyro\": [%d, %d, %d]}", 
            timestamp, 
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
private: 
    short * d_accel;
    short * d_gyro;
    int timestamp;
};

#endif