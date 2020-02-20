#ifndef MTK3339_H_INCLUDED
#define MTK3339_H_INCLUDED

#include <sensors/sensor.h>
#include <libgpsmm.h>

namespace spartan
{
    class MTK3339 : public Sensor {
    public:
        MTK3339();
        bool pollData(DataPacket &dp);
        void printValues() const;
    private:
        gpsmm m_gps;
        double m_lat, m_lng, m_alt;
    };
} // namespace spartan

#endif // MTK3339_H_INCLUDED