#include <array>
#include <iostream>
#include <fstream>

#include <data/datapacket.h>
#include <sensors/ads1115.h>
#include <sensors/lsm6ds33.h>

int main() {
    // Initialize Sensors
    spartan::LSM6DS33 *imu = new spartan::LSM6DS33(1, 0);

    // Initialize DataPackets
    spartan::MasterDataPacket mdp;
    spartan::IMUDataPacket *imuPacket = new spartan::IMUDataPacket(0);

    imu->powerOn();
    imu->poll();
    imu->printValues();
    std::cout << "DIVIDER" << std::endl;

    std::ofstream fout;
    fout.open("data.txt");

    for (int count = 0; count++; count < 100) {
        // Polls data from IMU
        if (!(imu->pollData(mdp))) {
            std::cerr << "Sensor name: " << imu->name() << " instance; " << imu->getInstance()
                << " poll data error!" << std::endl;
        }
        imuPacket->populate(mdp);
        std::cout << "Packet size " << imuPacket->getSize() << std::endl;
        std::cout << *imuPacket << std::endl;

        fout << *imuPacket;
        std::cout << *imuPacket << std::endl;
        std::cout << "DIVIDER" << std::endl;
    }
    fout.close();
}
