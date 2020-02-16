#include <array>
#include <iostream>

#include <data/datapacket.h>
#include <sensors/ads1115.h>
#include <sensors/lsm6ds33.h>

int main() {
    std::array<spartan::DataPacket*, 2> dataPackets;
    std::array<spartan::Sensor*, 1> sensors;

    // TODO: Initialize Sensors
    sensors[0] = new spartan::LSM6DS33(1, 0);

    // TODO: Initialize DataPackets
    // spartan::DataPacket masterPacket;
    // dataPackets[0] = new spartan::IMUDataPacket;

spartan::LSM6DS33 * l6 = dynamic_cast<spartan::LSM6DS33 *>(sensors[0]);
l6->powerOn();
l6->poll();
l6->printValues();
spartan::DataPacket * dp;
std::cout << l6->pollData(dp) << std::endl;
std::cout << * dp << std::endl;
std::cout << "DIVIDER" << std::endl;

sensors[0]->powerOn();
sensors[0]->poll();
sensors[0]->printValues();
spartan::DataPacket * dp;
std::cout << sensors[0]->pollData(dp) << std::endl;

//std::cout << *dp << std::endl;
std::cout << dp->getSize() << std::endl;
    // Initialization of sensors
    for (int i = 0; i < sensors.size(); i++) {
	//sensors[i]->powerOn();
    }
    // TODO: flight loop
    for (int i = 0; i < sensors.size(); i++) {
        bool result = sensors[i]->pollData(dataPackets[i]);
	if (!result)
	    std::cerr << "Sensor name: " << sensors[i]->name() << " instance; " << sensors[i]->getInstance() << " poll data error!" << std::endl;
    }

    std::cout << dataPackets[0]->getSize() << std::endl;
    std::cout << *dataPackets[0] << std::endl;
    /*
    for (int i = 0; i < dataPackets.size(); i++) {
        dataPackets[i]->populate(masterPacket);
    }
    */

    // TODO: Send to comms (write to SD card and send to radio)
}
