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
    
    //spartan::LSM6DS33 lsm6(1, 0);
    //lsm6.powerOn();
    //lsm6.poll();
    //lsm6.printEscapedRawValues(9);

sensors[0]->powerOn();
sensors[0]->poll();
sensors[0]->printValues();
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
