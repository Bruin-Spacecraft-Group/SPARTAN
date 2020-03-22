#include <iostream>
#include "mtk3339.h"

static bool strStartsWith(const char *str, const char *prefix);

// Parse a NMEA string
// @param nmea Pointer to the NMEA string
// @return True if we parsed it, false if it has an invalid checksum or invalid data
bool spartan::MTK3339::parse(char *nmea) {
    // do checksum check
    if (!check(nmea))
        return false;
    // passed the check, so there's a valid source in thisSource and a valid sentence in thisSentence

    // look for a few common sentences
    char *p = nmea; // Pointer to move through the sentence -- good parsers are
    // non-destructive
    p = strchr(p, ',') + 1; // Skip to the character after the next comma, then check sentence.

    if (!strcmp(thisSentence, "GGA")) {
        // found GGA
        // get time
        parseTime(p);

        // parse out latitude
        p = strchr(p, ',') + 1;
        parseLat(p);
        p = strchr(p, ',') + 1;
        if (!parseLatDir(p))
            return false;

        // parse out longitude
        p = strchr(p, ',') + 1;
        parseLon(p);
        p = strchr(p, ',') + 1;
        if (!parseLonDir(p))
            return false;

        p = strchr(p, ',') + 1;
        if (!isEmpty(p)) {
            fixquality = atoi(p);
            if (fixquality > 0) {
                fix = true;
                lastFix = sentTime;
            } else
                fix = false;
        }

        p = strchr(p, ',') + 1;
        if (!isEmpty(p)) {
            satellites = atoi(p);
        }

        p = strchr(p, ',') + 1;
        if (!isEmpty(p)) {
            HDOP = atof(p);
        }

        p = strchr(p, ',') + 1;
        if (!isEmpty(p)) {
            altitude = atof(p);
        }

        p = strchr(p, ',') + 1;
        p = strchr(p, ',') + 1;
        if (!isEmpty(p)) {
            geoidheight = atof(p);
        }

    } else if (!strcmp(thisSentence, "RMC")) {
        // found RMC
        // get time
        parseTime(p);

        // fix or no fix
        p = strchr(p, ',') + 1;
        if (!parseFix(p))
            return false;

        // parse out latitude
        p = strchr(p, ',') + 1;
        parseLat(p);
        p = strchr(p, ',') + 1;
        if (!parseLatDir(p))
            return false;

        // parse out longitude
        p = strchr(p, ',') + 1;
        parseLon(p);
        p = strchr(p, ',') + 1;
        if (!parseLonDir(p))
            return false;

        // speed
        p = strchr(p, ',') + 1;
        if (!isEmpty(p)) {
            speed = atof(p);
        }

        // angle
        p = strchr(p, ',') + 1;
        if (!isEmpty(p)) {
            angle = atof(p);
        }

        p = strchr(p, ',') + 1;
        if (!isEmpty(p)) {
            uint32_t fulldate = atof(p);
            day = fulldate / 10000;
            month = (fulldate % 10000) / 100;
            year = (fulldate % 100);
            lastDate = sentTime;
        }

    } else if (!strcmp(thisSentence, "GLL")) {
        // found GLL
        // parse out latitude
        parseLat(p);
        p = strchr(p, ',') + 1;
        if (!parseLatDir(p))
            return false;

        // parse out longitude
        p = strchr(p, ',') + 1;
        parseLon(p);
        p = strchr(p, ',') + 1;
        if (!parseLonDir(p))
            return false;

        // get time
        p = strchr(p, ',') + 1;
        parseTime(p);

        // fix or no fix
        p = strchr(p, ',') + 1;
        if (!parseFix(p))
            return false;

    } else if (!strcmp(thisSentence, "GSA")) {
        // found GSA
        // parse out Auto selection, but ignore them
        // parse out 3d fixquality
        p = strchr(p, ',') + 1;
        if (!isEmpty(p)) {
            fixquality_3d = atoi(p);
        }
        // skip 12 Satellite PDNs without interpreting them
        for (int i = 0; i < 12; i++)
        p = strchr(p, ',') + 1;

        // parse out PDOP
        p = strchr(p, ',') + 1;
        if (!isEmpty(p)) {
            PDOP = atof(p);
        }
        // parse out HDOP, we also parse this from the GGA sentence. Chipset should
        // report the same for both
        p = strchr(p, ',') + 1;
        if (!isEmpty(p)) {
            HDOP = atof(p);
        }
        // parse out VDOP
        p = strchr(p, ',') + 1;
        if (!isEmpty(p)) {
            VDOP = atof(p);
        }

    } else if (!strcmp(thisSentence, "TXT")) { //*******************************TXT
        if (!isEmpty(p))
            txtTot = atoi(p);
        p = strchr(p, ',') + 1;
        if (!isEmpty(p))
            txtN = atoi(p);
        p = strchr(p, ',') + 1;
        if (!isEmpty(p))
            txtID = atoi(p);
        p = strchr(p, ',') + 1;
        if (!isEmpty(p))
            parseStr(txtTXT, p, 61); // copy the text to NMEA TXT max of 61 characters

    } else {
        // we dont parse the remaining, yet!
        return false;
    }

    // Record the successful parsing of where the last data came from and when
    strcpy(lastSource, thisSource);
    strcpy(lastSentence, thisSentence);
    lastUpdate = millis();
    return true;
}

// Check an NMEA string for basic format, valid source ID and valid and valid sentence ID.
// Update the values of thisCheck, thisSource and thisSentence.
// @param nmea Pointer to the NMEA string
// @return True if well formed, false if it has problems
bool spartan::MTK3339::check(char *nmea) {
    thisCheck = 0; // new check
    if (*nmea != '$') {
        return false; // doesn't start with $
    } else {
        thisCheck += spartan::mtk3339::NMEA_HAS_DOLLAR;
    }
    // do checksum check -- first look if we even have one -- ignore all but last
    // *
    char *ast = nmea; // not strchr(nmea,'*'); for first *
    while (*ast)
        ast++; // go to the end
    while (*ast != '*' && ast > nmea)
        ast--; // then back to * if it's there
    if (*ast != '*') {
        return false; // there is no asterisk
    } else {
        uint16_t sum = parseHex(*(ast + 1)) * 16; // extract checksum
        sum += parseHex(*(ast + 2));
        char *p = nmea; // check checksum
        for (char *p1 = p + 1; p1 < ast; p1++)
        sum ^= *p1;
        if (sum != 0)
        return false; // bad checksum :(
        else
        thisCheck += spartan::mtk3339::NMEA_HAS_CHECKSUM;
    }
    // extract source of variable length
    char *p = nmea + 1;
    const char *src = tokenOnList(p, sources);
    if (src) {
        strcpy(thisSource, src);
        thisCheck += spartan::mtk3339::NMEA_HAS_SOURCE;
    } else {
        return false;
    }
    p += strlen(src);
    // extract sentence id and check if parsed
    const char *snc = tokenOnList(p, sentences_parsed);
    if (snc) {
        strcpy(thisSentence, snc);
        thisCheck += spartan::mtk3339::NMEA_HAS_SENTENCE_P + spartan::mtk3339::NMEA_HAS_SENTENCE;
    } else { // check if known
        snc = tokenOnList(p, sentences_known);
        if (snc) {
            strcpy(thisSentence, snc);
            thisCheck += spartan::mtk3339::NMEA_HAS_SENTENCE;
            return false;
        }
    }
    return true; // passed all the tests
}

// Check if a token at the start of a string is on a list.
// @param token Pointer to the string
// @param list A list of strings, with the final entry starting "ZZ"
// @return Pointer to the found token, or NULL if it fails
const char *spartan::MTK3339::tokenOnList(char *token, const char **list) {
    int i = 0; // index in the list
    while (strncmp(list[i], "ZZ", 2) && i < 1000) { // stop at terminator and don't crash without it
        // test for a match on the sentence name
        if (!strncmp((const char *)list[i], (const char *)token, strlen(list[i])))
            return list[i];
        i++;
    }
    return NULL; // couldn't find a match
}

// Parse a string token from pointer p to the next comma, asterisk or end of string.
// @param buff Pointer to the buffer to store the string in
// @param p Pointer into a string
// @param n Max permitted size of string including terminating 0
// @return Pointer to the string buffer
char *spartan::MTK3339::parseStr(char *buff, char *p, int n) {
    char *e = strchr(p, ',');
    int len = 0;
    if (e) {
        len = min(e - p, n - 1);
        strncpy(buff, p, len); // copy up to the comma
        buff[len] = 0;
    } else {
        e = strchr(p, '*');
        if (e) {
            len = min(e - p, n - 1);
            strncpy(buff, p, len); // or up to the *
            buff[e - p] = 0;
        } else {
            len = min((int)strlen(p), n - 1);
            strncpy(buff, p, len); // or to the end or max capacity
        }
    }
    return buff;
}

// Is the field empty, or should we try conversion? Won't work for a text field that starts
// with an asterisk or a comma, but that probably violates the NMEA-183 standard.
// @param pStart Pointer to the location of the token in the NMEA string
// @return true if empty field, false if something there
bool spartan::MTK3339::isEmpty(char *pStart) {
    if (',' != *pStart && '*' != *pStart && pStart != NULL)
        return false;
    else
        return true;
}

// Add *CS where CS is the two character hex checksum for all but the first character in the string.
// The checksum is the result of an exclusive or of all the characters in the string. Also useful if you
// are creating new PMTK strings for controlling a GPS module and need a checksum added.
// @param buff Pointer to the string, which must be long enough
void spartan::MTK3339::addChecksum(char *buff) {
    char cs = 0;
    int i = 1;
    while (buff[i]) {
        cs ^= buff[i];
        i++;
    }
    sprintf(buff, "%s*%02X", buff, cs);
}

// Parse a part of an NMEA string for time
// @param p Pointer to the location of the token in the NMEA string
void spartan::MTK3339::parseTime(char *p) {
    // get time
    uint32_t time = atol(p);
    hour = time / 10000;
    minute = (time % 10000) / 100;
    seconds = (time % 100);

    p = strchr(p, '.') + 1;
    milliseconds = atoi(p);
    lastTime = sentTime;
}

// Parse a part of an NMEA string for latitude angle
// @param p Pointer to the location of the token in the NMEA string
void spartan::MTK3339::parseLat(char *p) {
    int32_t degree;
    long minutes;
    char degreebuff[10];
    if (!isEmpty(p)) {
        strncpy(degreebuff, p, 2);
        p += 2;
        degreebuff[2] = '\0';
        long degree = atol(degreebuff) * 10000000;
        strncpy(degreebuff, p, 2); // minutes
        p += 3;                    // skip decimal point
        strncpy(degreebuff + 2, p, 4);
        degreebuff[6] = '\0';
        long minutes = 50 * atol(degreebuff) / 3;
        latitude_fixed = degree + minutes;
        latitude = degree / 100000 + minutes * 0.000006F;
        latitudeDegrees = (latitude - 100 * int(latitude / 100)) / 60.0;
        latitudeDegrees += int(latitude / 100);
    }
}

// Parse a part of an NMEA string for latitude direction
// @param p Pointer to the location of the token in the NMEA string
// @return True if we parsed it, false if it has invalid data
bool spartan::MTK3339::parseLatDir(char *p) {
    if (p[0] == 'S') {
        lat = 'S';
        latitudeDegrees *= -1.0;
        latitude_fixed *= -1;
    } else if (p[0] == 'N') {
        lat = 'N';
    } else if (p[0] == ',') {
        lat = 0;
    } else {
        return false;
    }
    return true;
}

// Parse a part of an NMEA string for longitude angle
// @param p Pointer to the location of the token in the NMEA string
void spartan::MTK3339::parseLon(char *p) {
    int32_t degree;
    long minutes;
    char degreebuff[10];
    if (!isEmpty(p)) {
        strncpy(degreebuff, p, 3);
        p += 3;
        degreebuff[3] = '\0';
        degree = atol(degreebuff) * 10000000;
        strncpy(degreebuff, p, 2); // minutes
        p += 3;                    // skip decimal point
        strncpy(degreebuff + 2, p, 4);
        degreebuff[6] = '\0';
        minutes = 50 * atol(degreebuff) / 3;
        longitude_fixed = degree + minutes;
        longitude = degree / 100000 + minutes * 0.000006F;
        longitudeDegrees = (longitude - 100 * int(longitude / 100)) / 60.0;
        longitudeDegrees += int(longitude / 100);
    }
}

// Parse a part of an NMEA string for longitude direction
// @param p Pointer to the location of the token in the NMEA string
// @return True if we parsed it, false if it has invalid data
bool spartan::MTK3339::parseLonDir(char *p) {
    if (!isEmpty(p)) {
        if (p[0] == 'W') {
            lon = 'W';
            longitudeDegrees *= -1.0;
            longitude_fixed *= -1;
        } else if (p[0] == 'E') {
            lon = 'E';
        } else if (p[0] == ',') {
            lon = 0;
        } else {
            return false;
        }
    }
    return true;
}

// Parse a part of an NMEA string for whether there is a fix
// @param p Pointer to the location of the token in the NMEA string
// @return True if we parsed it, false if it has invalid data
bool spartan::MTK3339::parseFix(char *p) {
    if (p[0] == 'A') {
        fix = true;
        lastFix = sentTime;
    } else if (p[0] == 'V') {
        fix = false;
    } else {
        return false;
    }
    return true;
}

// Time in seconds since the last position fix was obtained. Will fail by rolling over to zero
// after one millis() cycle, about 6-1/2 weeks.
// @return float value in seconds since last fix.
float spartan::MTK3339::secondsSinceFix() {
    return (millis() - lastFix) / 1000;
}

// Time in seconds since the last GPS time was obtained. Will fail by rolling over to zero after
// one millis() cycle, about 6-1/2 weeks.
// @return float value in seconds since last GPS time.
float spartan::MTK3339::secondsSinceTime() {
    return (millis() - lastTime) / 1000.;
}

// Time in seconds since the last GPS date was obtained. Will fail by rolling over to zero after
// one millis() cycle, about 6-1/2 weeks.
// @return float value in seconds since last GPS date.
float spartan::MTK3339::secondsSinceDate() {
    return (millis() - lastDate) / 1000.;
}

// How many bytes are available to read - part of 'Print'-class functionality
// @return Bytes available, 0 if none
size_t spartan::MTK3339::available(void) {
    if (paused)
        return 0;
    return gpsHwSerial->available();
}

// Write a byte to the underlying transport - part of 'Print'-class functionality
// @param c A single byte to send
// @return Bytes written - 1 on success, 0 on failure
size_t spartan::MTK3339::write(uint8_t c) {
    return gpsHwSerial->write(c);
}

// Read one character from the GPS device
// @return The character that we received, or 0 if nothing was available
char spartan::MTK3339::read(void) {
    static uint32_t firstChar = 0; // first character received in current sentence
    uint32_t tStart = millis();    // as close as we can get to time char was sent
    char c = 0;

    if (paused)
        return c;
    if (!gpsHwSerial->available())
        return c;
    c = gpsHwSerial->read();

    // Serial.print(c);

    currentline[lineidx++] = c;
    if (lineidx >= spartan::mtk3339::MAXLINELENGTH)
        lineidx = spartan::mtk3339::MAXLINELENGTH - 1; // ensure there is someplace to put the next received character
    if (c == '\n') {
        currentline[lineidx] = 0;
        if (currentline == line1) {
            currentline = line2;
            lastline = line1;
        } else {
            currentline = line1;
            lastline = line2;
        }

        // Serial.println("----");
        // Serial.println((char *)lastline);
        // Serial.println("----");
        lineidx = 0;
        recvdflag = true;
        recvdTime = millis(); // time we got the end of the string
        sentTime = firstChar;
        firstChar = 0; // there are no characters yet
        return c;      // wait until next character to set time
    }

    if (firstChar == 0)
        firstChar = tStart;
    return c;
}

// Constructor when using HardwareSerial
// @param ser Pointer to a HardwareSerial object
spartan::MTK3339::MTK3339(HardwareSerial *ser) {
    common_init();     // Set everything to common state, then...
    gpsHwSerial = ser; // ...override gpsHwSerial with value passed.
}

// Initialization code used by all constructor types
void spartan::MTK3339::common_init(void) {
    gpsHwSerial = NULL; // port pointer in corresponding constructor
    recvdflag = false;
    paused = false;
    lineidx = 0;
    currentline = line1;
    lastline = line2;

    hour = minute = seconds = year = month = day = fixquality = fixquality_3d = satellites = 0;  // uint8_t
    lat = lon = mag = 0; // char
    fix = false;         // boolean
    milliseconds = 0;    // uint16_t
    latitude = longitude = geoidheight = altitude = speed = angle = magvariation = HDOP = VDOP = PDOP = 0.0; // float
}

// Start the HW or SW serial port
// @param baud_or_i2caddr Baud rate if using serial, I2C address if using I2C
// @returns True on successful hardware init, False on failure
bool spartan::MTK3339::begin(uint32_t baud_or_i2caddr) {
    gpsHwSerial->begin(baud_or_i2caddr);
    delay(10);
    return true;
}

// Send a command to the GPS device
// @param str Pointer to a string holding the command to send
void spartan::MTK3339::sendCommand(const char *str) {
    println(str);
}

// Check to see if a new NMEA line has been received
// @return True if received, false if not
bool spartan::MTK3339::newNMEAreceived(void) {
    return recvdflag;
}

// Pause/unpause receiving new data
// @param p True = pause, false = unpause
void spartan::MTK3339::pause(bool p) {
    paused = p;
}

// Returns the last NMEA line received and unsets the received flag
// @return Pointer to the last line string
char *spartan::MTK3339::lastNMEA(void) {
    recvdflag = false;
    return (char *)lastline;
}

// Parse a hex character and return the appropriate decimal value
// @param c Hex character, e.g. '0' or 'B'
// @return Integer value of the hex character. Returns 0 if c is not a proper character
uint8_t spartan::MTK3339::parseHex(char c) {
    if (c < '0')
        return 0;
    if (c <= '9')
        return c - '0';
    if (c < 'A')
        return 0;
    if (c <= 'F')
        return (c - 'A') + 10;
    // if (c > 'F')
    return 0;
}

// Wait for a specified sentence from the device
// @param wait4me Pointer to a string holding the desired response
// @param max How long to wait, default is MAXWAITSENTENCE
// @param usingInterrupts True if using interrupts to read from the GPS (default is false)
// @return True if we got what we wanted, false otherwise
bool spartan::MTK3339::waitForSentence(const char *wait4me, uint8_t max, bool usingInterrupts) {
    uint8_t i = 0;
    while (i < max) {
    if (!usingInterrupts)
        read();

        if (newNMEAreceived()) {
            char *nmea = lastNMEA();
            i++;
            if (strStartsWith(nmea, wait4me))
                return true;
        }
    }
    return false;
}

// Stop the LOCUS logger
// @return True on success, false if it failed
bool spartan::MTK3339::LOCUS_StopLogger(void) {
    sendCommand(spartan::mtk3339::PMTK_LOCUS_STOPLOG);
    recvdflag = false;
    return waitForSentence(spartan::mtk3339::PMTK_LOCUS_STARTSTOPACK);
}

// Standby Mode Switches
// @return False if already in standby, true if it entered standby
bool spartan::MTK3339::standby(void) {
    if (inStandbyMode) {
        return false; // Returns false if already in standby mode, so that you do
        // not wake it up by sending commands to GPS
    } else {
        inStandbyMode = true;
        sendCommand(spartan::mtk3339::PMTK_STANDBY);
        // return waitForSentence(PMTK_STANDBY_SUCCESS);
        // don't seem to be fast enough to catch the message, or something else just is not working
        return true;
    }
}

// Wake the sensor up
// @return True if woken up, false if not in standby or failed to wake
bool spartan::MTK3339::wakeup(void) {
    if (inStandbyMode) {
        inStandbyMode = false;
        sendCommand(""); // send byte to wake it up
        return waitForSentence(spartan::mtk3339::PMTK_AWAKE);
    } else {
        return false; // Returns false if not in standby mode, nothing to wakeup
    }
}

// Checks whether a string starts with a specified prefix
// @param str Pointer to a string
// @param prefix Pointer to the prefix
// @return True if str starts with prefix, false otherwise
static bool strStartsWith(const char *str, const char *prefix) {
    while (*prefix) {
    if (*prefix++ != *str++)
        return false;
    }
    return true;
}
