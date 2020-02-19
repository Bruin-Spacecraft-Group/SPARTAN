#include <array>
#include <iostream>

#include <data/datapacket.h>
#include <sensors/ads1115.h>

int main() {
    std::array<spartan::PacketType*, 2> dataPackets;
    std::array<spartan::Sensor*, 1> sensors;

    // TODO: Initialize Sensors
    sensors[0] = new spartan::ADS1115(0, 0);

    // TODO: Initialize DataPackets
    spartan::DataPacket masterPacket;
    dataPackets[0] = new spartan::IMUDataPacket;
    dataPackets[1] = new spartan::AltimeterDataPacket;

    // TODO: flight loop
    for (int i = 0; i < sensors.size(); ++i) {
        sensors[i]->pollData(masterPacket);
    }
    for (int i = 0; i < dataPackets.size(); ++i) {
        dataPackets[i]->populate(masterPacket);
    }

    // TODO: Send to comms (write to SD card and send to radio)
}