#ifndef DATAPACKET_H

#define DATAPACKET_H

#include "sensors.h" //include for sensors polling and status functionality

//FOR SD CARD OPERATIONS; LEARNING HOW THEY WORK
#include <SPI.h>
#include <SD.h>

struct datapacket {
  unsigned long timestamp;
  float accel_x;
  float accel_y;
  float accel_z;
  float gyro_x;
  float gyro_y;
  float gyro_z;
  float mag_x;
  //float mag_y;
  //float mag_z;
  //float mag_heading; 
  float temp_tempC;
  float baro_pressure; // in mmHg
  float baro_altitude; // in meters
};

bool init(datapacket& dp); {/*...*/}
//initializes data packet's values to 0...?

bool print(const datapacket& dp) {
  std::cout << "";
}
//prints all of datapacket struct's data members to output screen

bool construct(datapacket& dp) {/*...*/}
//passing in data packet to construct
//call "preprocess"ing function on all active sensors, and assign the return values to the data packet's members
//active sensors can be determined by #define constants, and putting true/false as the value
//i.e.  #define ACCEL1_IN_USE true
//....  #define ACCEL2_IN_USE false
//....  if (ACCEL1_IN_USE) {...}


/************************************************OPERATION WITH SD CARD FUNCTIONS*************************************************/

bool writeSD(const datapacket& dp) {/*...*/}
//returns true if successfully wrote datapacket to SD card through serial connection; returns false if SD card not avaiable (i.e. doesnt have space, or not connected)
//return type can always be changed to an int to allow for more error returns (i.e. 1 for being out of space, and 2 for being not connected, etc.)

bool readSD(datapacket& dp) {/*...*/}
//returns true if successfully wrote datapacket to SD card through serial connection; returns false if SD card not avaiable (i.e. doesnt have space, or not connected)
//return type can always be changed to an int to allow for more error returns (i.e. 1 for being out of space, and 2 for being not connected, etc.)

/*********************************************************************************************************************************/

#endif