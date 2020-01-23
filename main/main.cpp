#include <iostream>

#include <data/datapacket.h>
#include <sensors/sensor.h>
// #include <sensors/test.h>

int main() {
    spartan::DataPacket masterDP;
    spartan::IMUDataPacket hello;
    hello.populate(masterDP);
}