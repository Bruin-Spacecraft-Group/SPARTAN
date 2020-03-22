#ifndef MTK3339_H_INCLUDED
#define MTK3339_H_INCLUDED

#include <string>

#include <sensors/sensor.h>

namespace spartan
{
    namespace mtk3339
    {
        const int MAXLINELENGTH = 120;        // how long are max NMEA lines to parse?
        const int NMEA_MAX_SENTENCE_ID = 20;  // maximum length of a sentence ID name, including terminating 0
        const int NMEA_MAX_SOURCE_ID = 3;     // maximum length of a source ID name, including terminating 0
        const int MAXWAITSENTENCE = 10;       // how long to wait when we're looking for a response

        // Note that these only control the rate at which the position is echoed; to actually speed up
        // the position fix you must also send one of the position fix rate commands below too.
        const std::string PMTK_SET_NMEA_UPDATE_100_MILLIHERTZ = "$PMTK220,10000*2F";
        const std::string PMTK_SET_NMEA_UPDATE_200_MILLIHERTZ = "$PMTK220,5000*1B";
        const std::string PMTK_SET_NMEA_UPDATE_1HZ = "$PMTK220,1000*1F";
        const std::string PMTK_SET_NMEA_UPDATE_2HZ = "$PMTK220,500*2B";
        const std::string PMTK_SET_NMEA_UPDATE_5HZ = "$PMTK220,200*2C";
        const std::string PMTK_SET_NMEA_UPDATE_10HZ = "$PMTK220,100*2F";

        // Position fix update rate commands.
        const std::string PMTK_API_SET_FIX_CTL_100_MILLIHERTZ = "$PMTK300,10000,0,0,0,0*2C";
        const std::string PMTK_API_SET_FIX_CTL_200_MILLIHERTZ = "$PMTK300,5000,0,0,0,0*18";
        const std::string PMTK_API_SET_FIX_CTL_1HZ = "$PMTK300,1000,0,0,0,0*1C";
        const std::string PMTK_API_SET_FIX_CTL_5HZ = "$PMTK300,200,0,0,0,0*2F";
        // Can't fix position faster than 5 times a second!

        const std::string PMTK_SET_BAUD_115200 = "$PMTK251,115200*1F";
        const std::string PMTK_SET_BAUD_57600 = "$PMTK251,57600*2C";
        const std::string PMTK_SET_BAUD_9600 = "$PMTK251,9600*17";

        const std::string PMTK_SET_NMEA_OUTPUT_GLLONLY = "$PMTK314,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29";
        const std::string PMTK_SET_NMEA_OUTPUT_RMCONLY = "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29";
        const std::string PMTK_SET_NMEA_OUTPUT_VTGONLY = "$PMTK314,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29";
        const std::string PMTK_SET_NMEA_OUTPUT_GGAONLY = "$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29";
        const std::string PMTK_SET_NMEA_OUTPUT_GSAONLY = "$PMTK314,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29";
        const std::string PMTK_SET_NMEA_OUTPUT_GSVONLY = "$PMTK314,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0*29";

        // GPRMC and GPGGA
        const std::string PMTK_SET_NMEA_OUTPUT_RMCGGA = "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28";
        // GPRMC, GPGGA and GPGSA
        const std::string PMTK_SET_NMEA_OUTPUT_RMCGGAGSA = "$PMTK314,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29";
        // Full output
        const std::string PMTK_SET_NMEA_OUTPUT_ALLDATA = "$PMTK314,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0*28";
        // No output
        const std::string PMTK_SET_NMEA_OUTPUT_OFF = "$PMTK314,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28";

        // to generate your own sentences, check out the MTK command datasheet and use a
        // checksum calculator such as the awesome http://www.hhhh.org/wiml/proj/nmeaxor.html

        const std::string PMTK_LOCUS_STOPLOG = "$PMTK185,1*23";           // Stop logging data
        const std::string PMTK_LOCUS_STARTSTOPACK = "$PMTK001,185,3*3C";  // Acknowledge the start or stop command

        // Enable search for SBAS satellite (only works with 1Hz output rate)
        const std::string PMTK_ENABLE_SBAS = "$PMTK313,1*2E";
        // Use WAAS for DGPS correction data
        const std::string PMTK_ENABLE_WAAS = "$PMTK301,2*2E";

        const std::string PMTK_STANDBY = "$PMTK161,0*28";              // standby command & boot successful message
        const std::string PMTK_STANDBY_SUCCESS = "$PMTK001,161,3*36";  // Not needed currently
        const std::string PMTK_AWAKE = "$PMTK010,002*2D";              // Wake up

        const std::string PMTK_Q_RELEASE = "$PMTK605*31";  // ask for the release and version

        const std::string PGCMD_ANTENNA = "$PGCMD,33,1*6C";    // request for updates on antenna status
        const std::string PGCMD_NOANTENNA = "$PGCMD,33,0*6D";  // don't show antenna status messages

        /// type for resulting code from running check()
        enum nmea_check_t {
            NMEA_BAD = 0,             // passed none of the checks
            NMEA_HAS_DOLLAR = 1,      // has a dollar sign in the first position
            NMEA_HAS_CHECKSUM = 2,    // has a valid checksum at the end
            NMEA_HAS_NAME = 4,        // there is a token after the $ followed by a comma
            NMEA_HAS_SOURCE = 10,     // has a recognized source ID
            NMEA_HAS_SENTENCE = 20,   // has a recognized sentence ID
            NMEA_HAS_SENTENCE_P = 40  // has a recognized parseable sentence ID
        };
    } // namespace mtk3339

    class MTK3339 : public Sensor {
    public:
        bool begin(uint32_t baud_or_i2caddr);

        char *lastNMEA(void);
        bool newNMEAreceived();
        void common_init(void);

        void sendCommand(const char *);

        void pause(bool b);

        uint8_t parseHex(char c);

        char read(void);
        size_t write(uint8_t);
        size_t available(void);

        bool check(char *nmea);
        bool parse(char *);
        void addChecksum(char *buff);
        float secondsSinceFix();
        float secondsSinceTime();
        float secondsSinceDate();

        bool wakeup(void);
        bool standby(void);

        // the results of the check on the current sentence
        int thisCheck = 0;
        // the first two letters of the current sentence, e.g. WI, GP
        char thisSource[mtk3339::NMEA_MAX_SOURCE_ID] = {0};
        // the next three letters of the current sentence, e.g. GLL, RMC
        char thisSentence[mtk3339::NMEA_MAX_SENTENCE_ID] = {0};
        // the results of the check on the most recent successfully parsed sentence
        char lastSource[mtk3339::NMEA_MAX_SOURCE_ID] = {0};
        // the next three letters of the most recent successfully parsed sentence, e.g. GLL, RMC
        char lastSentence[mtk3339::NMEA_MAX_SENTENCE_ID] = {0};

        uint8_t hour;           // GMT hours
        uint8_t minute;         // GMT minutes
        uint8_t seconds;        // GMT seconds
        uint16_t milliseconds;  // GMT milliseconds
        uint8_t year;           // GMT year
        uint8_t month;          // GMT month
        uint8_t day;            // GMT day

        float latitude;   // Floating point latitude value in degrees/minutes as received from the GPS (DDMM.MMMM)
        float longitude;  // Floating point longitude value in degrees/minutes as received from the GPS (DDDMM.MMMM)

        // Fixed point latitude and longitude value with degrees stored in units of 1/100000 degrees,
        // and minutes stored in units of 1/100000 degrees.  See pull #13 for more details:
        // https://github.com/adafruit/Adafruit-GPS-Library/pull/13
        int32_t latitude_fixed;   // Fixed point latitude in decimal degrees
        int32_t longitude_fixed;  // Fixed point longitude in decimal degrees

        float latitudeDegrees;   // Latitude in decimal degrees
        float longitudeDegrees;  // Longitude in decimal degrees
        float geoidheight;       // Diff between geoid height and WGS84 height
        float altitude;          // Altitude in meters above MSL
        float speed;             // Current speed over ground in knots
        float angle;             // Course in degrees from true north
        float magvariation;      // Magnetic variation in degrees (vs. true north)
        float HDOP;  // Horizontal Dilution of Precision - relative accuracy of horizontal position
        float VDOP;  // Vertical Dilution of Precision - relative accuracy of vertical position
        float PDOP;  // Position Dilution of Precision - single number encompassing both kinds of DOP
        char lat = 'X';  // N/S
        char lon = 'X';  // E/W
        char mag = 'X';  // Magnetic variation direction
        bool fix;  // Have a fix?
        uint8_t fixquality;     // Fix quality (0, 1, 2 = Invalid, GPS, DGPS)
        uint8_t fixquality_3d;  // 3D fix quality (1, 3, 3 = Nofix, 2D fix, 3D fix)
        uint8_t satellites;     // Number of satellites in use

        bool waitForSentence(const char *wait, uint8_t max = mtk3339::MAXWAITSENTENCE, bool usingInterrupts = false);
        bool LOCUS_StopLogger(void);

        // NMEA additional public functions
        char *build(char *nmea, const char *thisSource, const char *thisSentence, char ref = 'R');
        void resetSentTime();

        // NMEA additional public variables
        char txtTXT[63] = {0}; ///< text content from most recent TXT sentence
        int txtTot = 0;        ///< total TXT sentences in group
        int txtID = 0;         ///< id of the text message
        int txtN = 0;          ///< the TXT sentence number

    private:
        const char *tokenOnList(char *token, const char **list);
        char *parseStr(char *buff, char *p, int n);
        bool isEmpty(char *pStart);
        void parseTime(char *);
        void parseLat(char *);
        bool parseLatDir(char *);
        void parseLon(char *);
        bool parseLonDir(char *);
        bool parseFix(char *);
        // used by check() for validity tests, room for future expansion
        const char *sources[5] = {"II", "WI", "GP", "GN", "ZZZ"};  // valid source ids
        const char *sentences_parsed[5] = {"GGA", "GLL", "GSA", "RMC", "ZZZ"};  // parseable sentence ids
        const char *sentences_known[1] = {"ZZZ"};  // known, but not parseable sentence ids

        // Make all of these times far in the past by setting them near the middle of
        // the millis() range. Timing assumes that sentences are parsed promptly.
        uint32_t lastUpdate = 2000000000L;  // millis() when last full sentence successfully parsed
        uint32_t lastFix = 2000000000L;     // millis() when last fix received
        uint32_t lastTime = 2000000000L;    // millis() when last time received
        uint32_t lastDate = 2000000000L;    // millis() when last date received
        uint32_t recvdTime = 2000000000L;   // millis() when last full sentence received
        uint32_t sentTime = 2000000000L;    // millis() when first character of last full sentence received
        bool paused;

        uint8_t parseResponse(char *response);
        int8_t _buff_max = -1, _buff_idx = 0;
        char last_char = 0;

        // We double buffer: read one line in and leave one for the main program
        volatile char line1[mtk3339::MAXLINELENGTH];
        volatile char line2[mtk3339::MAXLINELENGTH];
        volatile uint8_t lineidx = 0;  // our index into filling the current line
        volatile char *currentline;    // Pointer to current line buffer
        volatile char *lastline;       // Pointer to previous line buffer
        volatile bool recvdflag;       // Received flag
        volatile bool inStandbyMode;   // In standby flag
    }; // class MTK3339
} // namespace spartan

#endif // MTK3339_H_INCLUDED
