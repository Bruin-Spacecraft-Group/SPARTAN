# SPARTAN-Flight-Software

A sensor driver library and main flight loop implemented by the Bruinspace Project Reach Software team. Based on
Intel's [MRAA library](https://github.com/eclipse/mraa) for low level I2C communications.

Table of contents
=================

<!--ts-->
* [Build instructions](#build-instructions)
* [Sensor docs](#sensor-documentations)
    * [LSM6 Inertial Measurement Unit](spartan/src/docs/lsm6.md)
<!--te-->

# Build instructions

If you're lazy:

```shell
./build.sh
```

If you like typing stuff:
```shell
cmake -B _build
cd _build
cmake --build .
./main/flight_software
```

Note that after running either command once, for all future builds you only have to run
```shell
cmake --build .
```

# Sensor documentations
* [Sensor Abstract class requirements](spartan/src/docs/sensor.md) *(Must Read!)*
* [LSM6DS33](spartan/src/docs/lsm6.md)

# Data packet documentation
* [Data packet structure and implementation examples](spartan/src/docs/dp.md)
