# SPARTAN-Flight-Software

A sensor driver library and main flight loop implemented by the Bruinspace Project Reach Software team. Based on Intel's mraa library for low level i2c communications. 

Table of contents
=================

<!--ts-->
* [Build instructions](#build-instructions)
* [Installation](#installation)
* [Sensor docs](#sensor-documentations)
    * [LSM6 Inertial Measurement Unit]()

<!--te-->

# Build instructions

```
cmake -B _build
cd _build
cmake --build .
./main/flight_software
```

# Sensor documentations
* [LSM6DS33](spartan/src/docs/lsm6.md)