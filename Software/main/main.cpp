#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

#include <data/mdp.h>
#include <data/datapacket.h>
#include <sensors/ads1115.h>
#include <sensors/lsm6ds33.h>

#define DEBUG true

int main() {
    std::array<spartan::PacketType*, 1> dataPackets;
    std::array<spartan::Sensor*, 2> sensors;

    // TODO: Initialize Sensors
    sensors[0] = new spartan::LSM6DS33(1, 0);
    sensors[1] = new spartan::ADS1115(1, 1);

    // TODO: Initialize DataPackets
    spartan::MasterDataPacket mdp;
    dataPackets[0] = new spartan::IMUDataPacket;

    // Initialization of sensors
    for (int i = 0; i < sensors.size(); i++) {
	    sensors[i]->powerOn();
    }
    std::ofstream fout;
    fout.open("data.txt");

    // TODO: flight loop
    for (int count  = 0; count < 100; count++) {
        for (int i = 0; i < sensors.size(); i++) {
            if (sensors[i]->poll(mdp) != spartan::RESULT_SUCCESS) {
                std::cerr << "Sensor name: " << sensors[i]->name() << " instance; " << sensors[i]->getInstance()
                    << " poll data error!" << std::endl;
            }
        }
        for (int i = 0; i < dataPackets.size(); i++) {
            dataPackets[i]->populate(mdp);
            if (DEBUG) {
                std::cout << "Packet size " << dataPackets[i]->getSize() << std::endl;
                std::cout << dataPackets[i]->format() << std::endl;
            }
            fout << dataPackets[i]->format();
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
