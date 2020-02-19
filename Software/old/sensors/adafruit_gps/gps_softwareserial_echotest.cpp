// // Test code for Adafruit GPS modules using MTK3329/MTK3339 driver
// //
// // This code just echos whatever is coming from the GPS unit to the
// // serial monitor, handy for debugging!
// //
// // Tested and works great with the Adafruit Ultimate GPS module
// // using MTK33x9 chipset
// //    ------> http://www.adafruit.com/products/746
// // Pick one up today at the Adafruit electronics shop
// // and help support open source hardware & software! -ada

// #include <iostream>
// #include <Adafruit_GPS.h>
// #include <SoftwareSerial.h>
// using namespace std;

// // Connect the GPS Power pin to 5V
// // Connect the GPS Ground pin to ground
// // Connect the GPS TX (transmit) pin to Digital 8
// // Connect the GPS RX (receive) pin to Digital 7

// // You can change the pin numbers to match your wiring:
// SoftwareSerial swSerial(8, 7);

// #define PMTK_SET_NMEA_UPDATE_1HZ  "$PMTK220,1000*1F"
// #define PMTK_SET_NMEA_UPDATE_5HZ  "$PMTK220,200*2C"
// #define PMTK_SET_NMEA_UPDATE_10HZ "$PMTK220,100*2F"

// // turn on only the second sentence (GPRMC)
// #define PMTK_SET_NMEA_OUTPUT_RMCONLY "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29"
// // turn on GPRMC and GGA
// #define PMTK_SET_NMEA_OUTPUT_RMCGGA "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
// // turn on ALL THE DATA
// #define PMTK_SET_NMEA_OUTPUT_ALLDATA "$PMTK314,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
// // turn off output
// #define PMTK_SET_NMEA_OUTPUT_OFF "$PMTK314,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"

// #define PMTK_Q_RELEASE "$PMTK605*31"

// int main()
// {
//   Adafruit_GPS gps(&swSerial);

//   gps.sendCommand(PMTK_SET_NMEA_UPDATE_5HZ);
//   gps.sendCommand(PMTK_SET_NMEA_UPDATE_5HZ);
//   gps.sendCommand(PMTK_SET_NMEA_OUTPUT_ALLDATA);
  
//   std::cout << "Input number of desired readings: " << std::endl;
//   unsigned int numOfReadings;
//   std::cin >> numOfReadings;

//   std::cout << "Total number of readings: " << numOfReadings << std::endl;

//   for (unsigned int i = 0; i < numOfReadings; i++)
//   {
//     cout << "================GPS Dump:================" << endl;
//     cout << gps.hour << endl;
//     cout << gps.minute << endl;
//     cout << gps.seconds << endl;
//     cout << gps.milleseconds << endl;
//     cout << gps.year << endl;
//     cout << gps.month << endl;
//     cout << gps.day << endl;
//     cout << gps.latitude << endl;
//     cout << gps.longitude << endl;
//     cout << gps.latitude_fixed << endl;   ///< Fixed point latitude in decimal degrees
//     cout << gps.longitude_fixed << endl;  ///< Fixed point longitude in decimal degrees
//     cout << gps.latitudeDegrees << endl;    ///< Latitude in decimal degrees
//     cout << gps.longitudeDegrees << endl;   ///< Longitude in decimal degrees
//     cout << gps.geoidheight << endl;        ///< Diff between geoid height and WGS84 height
//     cout << gps.altitude << endl;           ///< Altitude in meters above MSL
//     cout << gps.speed << endl;              ///< Current speed over ground in knots
//     cout << gps.angle << endl;              ///< Course in degrees from true north
//     cout << gps.magvariation << endl;       ///< Magnetic variation in degrees (vs. true north)
//     cout << gps.HDOP << endl;               ///< Horizontal Dilution of Precision - relative accuracy of horizontal position
//     cout << gps.lat << endl;                 ///< N/S
//     cout << gps.lon << endl;                 ///< E/W
//     cout << gps.mag << endl;                 ///< Magnetic variation direction
//     cout << gps.fix << endl;              ///< Have a fix?
//     cout << gps.fixquality << endl;       ///< Fix quality (0, 1, 2 = Invalid, GPS, DGPS)
//     cout << gps.satellites << endl;       ///< Number of satellites in use
//   }
// }