// some example I copied off the internet
// https://gist.github.com/elimpnick/8313815ac387e6757f751dc8960f03d7

//  Has no actual purpose other than output some of libgpsmm struct variables of
//  your choosing.
//  reference declarations: https://fossies.org/dox/gpsd-3.20/index.html
//
//  compiles without warning as follows:
//  g++ -Wall -std=c++14 -pedantic $(pkg-config --cflags --libs libgps) example.cpp -o example
//  Free for the taking.
//  Version 1.4

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

#include <libgpsmm.h>

int main()
{
  gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);

  if (gps_rec.stream(WATCH_ENABLE | WATCH_JSON) == NULL) {
    std::cerr << "No GPSD running.\n";
    return 1;
  }

  for (;;) {
    if (!gps_rec.waiting(1000000)) continue;

    struct gps_data_t *gpsd_data;

    if ((gpsd_data = gps_rec.read()) == NULL) {
      std::cerr << "GPSD read error.\n";
      return 1;
    } else {
      while (((gpsd_data = gps_rec.read()) == NULL) ||
             (gpsd_data->fix.mode < MODE_2D)) {
        // Do nothing until fix
      }
      timestamp_t ts { gpsd_data->fix.time };
      auto latitude  { gpsd_data->fix.latitude };
      auto longitude { gpsd_data->fix.longitude };

      // convert GPSD's timestamp_t into time_t
      time_t seconds { (time_t)ts };
      auto   tm = *std::localtime(&seconds);

      std::ostringstream oss;
      oss << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
      auto time_str { oss.str() };

      // set decimal precision
      std::cout.precision(6);
      std::cout.setf(std::ios::fixed, std::ios::floatfield);
      std::cout << time_str << "," << latitude << "," << longitude << std::endl;
    }
  }
  return 0;
}