// based on some example I copied off the internet
// https://gist.github.com/elimpnick/8313815ac387e6757f751dc8960f03d7

#include <iostream>
#include <libgpsmm.h>

#include "mtk3339.h"

spartan::MTK3339::MTK3339() : m_gps("localhost", DEFAULT_GPSD_PORT) {}

bool spartan::MTK3339::pollData(DataPacket &dp) {
    if (m_gps.stream(WATCH_ENABLE | WATCH_JSON) == NULL) {
        std::cerr << "No GPSD running" << std::endl;
        return false;
    }
    struct gps_data_t *gpsd_data = m_gps.read();

    if (gpsd_data == NULL) {
        std::cerr << "GPSD read error" << std::endl;
        return false;
    }
    if (gpsd_data->fix.mode < MODE_2D) {
        std::cerr << "No GPS fix" << std::endl;
        return false;
    }

    dp.latitude = m_lat = gpsd_data->fix.latitude;
    dp.longitude = m_lng = gpsd_data->fix.longitude;
    if (gpsd_data->fix.mode >= MODE_3D) {
        dp.gps_altitude = m_alt = gpsd_data->fix.altitude;
    } else {
        dp.gps_altitude = m_alt = -6.371e6; // R_EARTH
    }
    return true;
}

void spartan::MTK3339::printValues() const {
    std::cout << "Latitude: " << m_lat << std::endl;
    std::cout << "Longitude: " << m_lng << std::endl;
    std::cout << "Altitude: " << m_alt << std::endl;
}