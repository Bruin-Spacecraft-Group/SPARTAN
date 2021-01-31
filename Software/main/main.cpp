#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

#include <datapacket/datapacket.h>
#include <sensors/ads1115.h>
#include <sensors/lsm6ds33.h>
#include <utils/utils.h>
#include "decoder.h"

#define DEBUG true

using std::cout;
using std::endl;

int main() {
    std::vector<spartan::EncodedPacket> dataPackets;
    std::array<spartan::Sensor*, 1> sensors{};

    // TODO: Initialize Sensors
    sensors[0] = new spartan::LSM6DS33(1, 0);

    // Initialize sensors
    for (auto &sensor: sensors) {
	    sensor->powerOn();
    }

    std::ofstream fout;
    fout.open("data.txt");

    cout << spartan::data_id::LSM6DS33_DATA << endl;

    // TODO: flight loop
    for (int count  = 0; count < 1; count++) {
        for (auto &sensor: sensors) {
            if (sensor->pollData(dataPackets) != spartan::RESULT_SUCCESS) {
                sensor->printPollingError();
            }
        }

        for (auto &dataPacket : dataPackets) {
            if (DEBUG) {
                cout << "Packet size " << (int) dataPacket.length << endl;
                cout << spartan::format_encoded_packet(dataPacket) << endl;
            }

            fout << spartan::format_encoded_packet(dataPacket);
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    fout.close();

    // TODO: Send to comms (write to SD card and send to radio)
    /*
    std::cout << "Read from file" << std::endl;
    std::ifstream in;
    in.open("data.txt");
    for (int i=0; i<100; i++) {
        spartan::DataPacket * dp;
        in >> dp;
        std::cout << "Read: " << std::endl;
        std::cout << dp;
    } */
}
