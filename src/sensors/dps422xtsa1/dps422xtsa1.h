//
//  dps422xtsa1.h
//  Altimeter
//
//  Created by Connor Chin on 1/9/20.
//  Copyright © 2020 Connor Chin. All rights reserved.
//

#ifndef dps422xtsa1_h
#define dps422xtsa1_h

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "../sensors.h"
#include "../../globals.h"

#define BUFFER_SIZE 9
#define DATA_SIZE 9
#define PSR_BUFF_SIZE 20
#define PSR_SIZE 20
#define TMP_BUFF_SIZE 3
#define TMP_SIZE 3

#define DPS422XTSA1_I2C_ADDR            0x77
#define DPS422XTSA1_RESET               0x0D

#define DPS422XTSA1_PSR_MSB             0x00
#define DPS422XTSA1_PSR_LSB             0x01
#define DPS422XTSA1_PSR_XLSB            0x02

#define DPS422XTSA1_TMP_MSB             0x03
#define DPS422XTSA1_TMP_LSB             0x04
#define DPS422XTSA1_TMP_XLSB            0x05

#define DPS422XTSA1_PSR_CFG             0x06
#define DPS422XTSA1_TMP_CFG             0x07
#define DPS422XTSA1_MEAS_CFG            0x08
/*
 b7 (init. complete): status bit set when initialisation procedure complete
 b6 (cont. mode flag): status bit set when DPS422 in continuous meas. mode
 b5 (temp. data ready): status bit set when new temp. meas. data is avail. Cleared when register 0x05 is read
 b4 (psr. data ready): status bit set when new psr. meas. data is avail. Cleared when register 0x02 is read
 b<2:0> (meas. control):
 Configuration register controlling measurement mode:
 • 000 - Idle / Stop Background
 • 001 - Pressure Measurement
 • 010 - Temperature Measurement
 • 011 - Pressure and Temperature Measurement one shot
 • 100 - Idle / Stop Background
 • 101 - Continuous Pressure Measurement
 • 110 - Continuous Temperature Measurement
 • 111 - Continuous Pressure and Temperature Measurement
 */

/*
 Temperature Constants: all constants in two's complement
 T_gain: 8 bit
 T_dVbe: 7 bit
 T_Vbe:  9 bit
 */
#define DPS422XTSA1_T_GAIN_COEFF      0x20 // b<7:0>: T_gain<7:0>
#define DPS422XTSA1_T_dVBE_COEFF      0x21 // b<7:1>: T_dVbe<6:0>   b<0>: T_Vbe<0>
#define DPS422XTSA1_T_VBE_COEFF       0x22 // b<7:0>: T_Vbe<8:1>

/*
 Pressure Constants: all constants in two's complement
 C00: 20 bit
 C01: 20 bit
 C02: 20 bit
 C10: 20 bit
 C11: 17 bit
 C12: 17 bit
 C20: 15 bit
 C21: 14 bit
 C30: 12 bit
 */
#define DPS422XTSA1_PSR_COEFF_1         0x26 // b<7:0>: C00 <19:12>
#define DPS422XTSA1_PSR_COEFF_2         0x27 // b<7:0>: C00 <11:4>
#define DPS422XTSA1_PSR_COEFF_3         0x28 // b<7:4>: C00 <3:0>   b<3:0>: C10<19:16>
#define DPS422XTSA1_PSR_COEFF_4         0x29 // b<7:0>: C10<15:8>
#define DPS422XTSA1_PSR_COEFF_5         0x2A // b<7:0>: C10<7:0>
#define DPS422XTSA1_PSR_COEFF_6         0x2B // b<7:0>: C01<19:12>
#define DPS422XTSA1_PSR_COEFF_7         0x2C // b<7:0>: C01<11:4>
#define DPS422XTSA1_PSR_COEFF_8         0x2D // b<7:4>: C01<3:0>    b<3:0>: C02<19:16>
#define DPS422XTSA1_PSR_COEFF_9         0x2E // b<7:0>: C02<15:8>
#define DPS422XTSA1_PSR_COEFF_10        0x2F // b<7:0>: C02<7:0>
#define DPS422XTSA1_PSR_COEFF_11        0x30 // b<7>: empty         b<6:0>: C20<14:8>
#define DPS422XTSA1_PSR_COEFF_12        0x31 // b<7:0>: C20<7:0>
#define DPS422XTSA1_PSR_COEFF_13        0x32 // b<7:4>: empty       b<3:0>: C30<11:8>
#define DPS422XTSA1_PSR_COEFF_14        0x33 // b<7:0>: C30<7:0>
#define DPS422XTSA1_PSR_COEFF_15        0x34 // b<7:0>: C11<16:9>
#define DPS422XTSA1_PSR_COEFF_16        0x35 // b<7:0>: C11<8:1>
#define DPS422XTSA1_PSR_COEFF_17        0x36 // b<7>: C11<0>        b<6:1>: C12<16:10>
#define DPS422XTSA1_PSR_COEFF_18        0x37 // b<7:0>: C12<9:2>
#define DPS422XTSA1_PSR_COEFF_19        0x38 // b<7:6>: C12<1:0>    b<5:0>: C21<13:8>
#define DPS422XTSA1_PSR_COEFF_20        0x39 // b<7:0>: C21<7:0>

// Constants needed in temperatur calculation (units listed on the right)
#define T_REF               27          // Celcius
#define VBE_TARGET          0.687027    // Volts
#define ALPHA               9.45        // None
#define TC_VBE              -0.001735   // Volts
#define KPTAT_CORNER        -0.8        // None
#define KPTAT_CURVATURE     0.039       // None
#define A0                  5030        // Kelvins

using namespace std;

class DPS422XTSA1 : public Sensor {
public:
    DPS422XTSA1(int busID, int instance, uint8_t p_rate, uint8_t p_resolution, uint8_t t_rate, uint8_t t_resolution): Sensor(busID, instance), m_i2c(busID, true) {
        // wait at least 8ms before writing and reading from registers
        sleep(0.02);
        m_status = STATUS_IDLE;
        psr_rate = p_rate;
        psr_resolution = p_resolution;
        tmp_rate = t_rate;
        tmp_resolution = t_resolution;

        // set pressure measurement rate and resolution
        uint8_t p_meas = (p_rate << 4) | p_resolution;
        if (m_i2c.writeReg(DPS422XTSA1_PSR_CFG, p_meas) != mraa::SUCCESS) {
            cerr << "Unable to set pressure measurement rates." << endl;
        }

        // set temperature measurement rate and resolution
        uint8_t t_meas = (t_rate << 4) | t_resolution;
        if (m_i2c.writeReg(DPS422XTSA1_TMP_CFG, t_meas) != mraa::SUCCESS) {
            cerr << "Unable to set temperature measurement rates." << endl;
        }
        // attempt to read bytes into buffer
        if (m_i2c.readBytesReg(DPS422XTSA1_PSR_MSB, m_buffer, DATA_SIZE) == -1) {
            cerr << "Unable to read bytes from registers. Please wait 8ms from startup before attempting to read from registers." << endl;
        }
        if (m_i2c.readBytesReg(DPS422XTSA1_PSR_COEFF_1, p_constants, PSR_SIZE) == -1) {
            cerr << "Unable to read bytes from pressure constants registers. Please wait 8ms from startup before attempting to read from registers." << endl;
        }
        if (m_i2c.readBytesReg(DPS422XTSA1_T_GAIN_COEFF, t_constants, TMP_SIZE) == -1) {
            cerr << "Unable to read bytes from temperature constants registers. Please wait 8ms from startup before attempting to read from registers." << endl;
        }

        // organize pressure constants into variables from p_constants array
        C00 = (((p_constants[0] << 8) | p_constants[1]) << 4) | ((p_constants[2] >> 4) & 0x0F);                 // 20 bit
        C10 = ((((p_constants[2] & 0x0F) << 8) | p_constants[3]) << 8) | p_constants[4];                        // 20 bit
        C01 = (((p_constants[5] << 8) | p_constants[6]) << 4) | ((p_constants[7] >> 4) & 0x0F);                 // 20 bit
        C02 = ((((p_constants[7] & 0x0F) << 8) | p_constants[8]) << 8) | p_constants[9];                        // 20 bit
        C20 = ((p_constants[10] & 0x7F) << 8) | p_constants[11];                                                // 15 bit
        C30 = ((p_constants[12] & 0x0F) << 8) | p_constants[13];                                                // 12 bit
        C11 = (((p_constants[14] << 8) | p_constants[15]) << 1) | (((p_constants[16] & 0x80) >> 7) & 0x1);      // 17 bit
        C12 = ((((p_constants[16] & 0x7F) << 8) | p_constants[17]) << 2) | ((p_constants[18] >> 6) & 0x3);      // 17 bit
        C21 = ((p_constants[18] & 0x3F) << 8) | p_constants[19];                                                // 14 bit

        // organize temperature constants
        T_gain = t_constants[0];                                    // 8 bit
        T_dVbe = t_constants[1] & 0xFE;                             // 7 bit
        T_Vbe = ((t_constants[1] & 0x1) << 8) | t_constants[2];     // 9 bit
    }

    virtual int powerOn() { return RESULT_SUCCESS; }
    virtual int powerOff() { return RESULT_FALSE; }

/*
 Soft reset: b<3:0>
 Two soft reset options are available, depending on the value
 sent to this bit field.
 • 0b1000: Reset configuration registers without eFuse refresh.
 Duration ~0.7ms.
 • 0b1001: Full reset. Similar to power-on-reset, all registers
 are reset and eFuses refresh is carried out. Duration ~3ms.
 */
    void toggleSoftReset(uint8_t rst) {
        if (m_i2c.writeReg(DPS422XTSA1_RESET, rst & 0x0F) != mraa::SUCCESS) {
            cerr << "Unable to toggle reset." << endl;
        }
        psr_rate = 0;
        psr_resolution = 0;
        tmp_rate = 0;
        tmp_resolution = 0;
        m_pres = 0;
        m_tmp = 0;
    }

/*
 Following register layout is for both PSR and TMP configurations
 NOTE: for TMP_CFG, b7 MUST be set to 1 to configure measurements correctly
 | b7 | PSR/TMP meas. rate [2:0] | b3 | PSR/TMP meas. resolution [2:0] |
 PSR/TMP measurement rate:         PSR/TMP measurement resolution:
  • 000 - 1 sample/sec              • 000 - 256 samples - 1x decimation
  • 001 - 2 samples/sec             • 001 - 512 samples - 2x decimation
  • 010 - 4 samples/sec             • 010 - 1024 samples - 4x decimation
  • 011 - 8 samples/sec             • 011 - 2048 samples - 8x decimation
  • 100 - 16 samples/sec            • 100 - 4096 samples - 16x decimation
  • 101 - 32 samples/sec            • 101 - 8192 samples - 32x decimation
  • 110 - 64 samples/sec            • 110 - 16384 samples - 64x decimation
  • 111 - 128 samples/sec           • 111 - 32768 samples - 128x decimation
*/
    void configurePressureRate(uint8_t rate) {
        if (m_i2c.writeReg(DPS422XTSA1_PSR_CFG, (m_buffer[6] & 0x8F) | ((rate & 0x07) << 4)) != mraa::SUCCESS) {
            cerr << "Unable to configure pressure rate." << endl;
            return;
        }
        // update the buffer after successful change
        m_buffer[6] = (m_buffer[6] & 0x8F) | ((rate & 0x07) << 4);
        psr_rate = rate & 0x07;
    }
    
    void configurePressureResolution(uint8_t resolution) {
        if (m_i2c.writeReg(DPS422XTSA1_PSR_CFG, (m_buffer[6] & 0xF8) | (resolution & 0x07)) != mraa::SUCCESS) {
            cerr << "Unable to configure pressure resolution." << endl;
            return;
        }
        m_buffer[7] = (m_buffer[7] & 0xF8) | (resolution & 0x07);
        psr_resolution = resolution & 0x07;
    }

    void configureTemperatureRate(uint8_t rate) {
        if (m_i2c.writeReg(DPS422XTSA1_TMP_CFG, (m_buffer[7] & 0x8F) | ((rate & 0x07) << 4)) != mraa::SUCCESS) {
            cerr << "Unable to configure temperature measurement." << endl;
            return;
        }
        m_buffer[7] = (m_buffer[7] & 0x8F) | ((rate & 0x07) << 4);
        tmp_rate = rate & 0x07;
    }    

    void configureTemperatureResolution(uint8_t resolution) {
        uint8_t meas = (tmp_rate << 4) | (resolution & 0x07);
        if (m_i2c.writeReg(DPS422XTSA1_TMP_CFG, (m_buffer[7] & 0xF8) | (resolution & 0x07)) != mraa::SUCCESS) {
            cerr << "Unable to configure temperature measurement." << endl;
            return;
        }
        m_buffer[7] = (m_buffer[7] & 0xF8) | (resolution & 0x07);
        tmp_resolution = resolution & 0x07;
    }
/*
 Configuration register controlling measurement mode:
 • 000 - Idle / Stop Background
 • 001 - Pressure Measurement
 • 010 - Temperature Measurement
 • 011 - Pressure and Temperature Measurement one shot
 • 100 - Idle / Stop Background
 • 101 - Continuous Pressure Measurement
 • 110 - Continuous Temperature Measurement
 • 111 - Continuous Pressure and Temperature Measurement
 */
    void configureOperatingModes(uint8_t mode) {
        if (m_i2c.writeReg(DPS422XTSA1_MEAS_CFG, (m_buffer[8] & 0xF8) | (mode & 0x07)) != mraa::SUCCESS) {
            cerr << "Unable to configure operating modes." << endl;
        }
    }

    virtual bool poll() {
        if (m_status != STATUS_IDLE) { return ERROR_INVALID_STATUS; }
        
        // read data values from registers
        if (m_i2c.readBytesReg(DPS422XTSA1_PSR_MSB, m_buffer, DATA_SIZE) == -1) {
            cerr << "Unable to read bytes from registers. Please wait 8ms from startup before attempting to read from registers." << endl;
            return ERROR_POLL;
        }

        // Pressure calculations
        float pres_raw = ((((m_buffer[0] << 8) | m_buffer[1]) << 8) | m_buffer[2]);
        float temp_raw = ((((m_buffer[3] << 8) | m_buffer[4]) << 8) | m_buffer[5]);
        float pres_scaled = pres_raw / getkP();
        float temp_x = temp_raw / 1048576;
        float temp_scaled = (8.5 * temp_x) / (1 + 8.8 * temp_x);
        m_pres = C00 + (C10 * pres_scaled) + (C01 * temp_scaled) + (C20 * pow(pres_scaled, 2)) + (C02 * pow(temp_scaled, 2)) + (C30 * pow(pres_scaled, 3)) + (C11 * pres_scaled * temp_scaled) + (C12 * pres_scaled * pow(temp_scaled, 2)) + (C21 * pow(pres_scaled, 2) * temp_scaled);

        // Temperature calculations
        float Vbe = T_Vbe * 1.05031 * pow(10, -4) + 0.463232422;
        float dVbe = T_dVbe × 1.25885 * pow(10, -5) + 0.04027621;
        float adc = T_gain * 8.4375 * pow(10, -5) + 0.675;
        float Vbe_cal = Vbe / adc;
        float dVbe_cal = dVbe / adc;
        float T_calib = A0 * dVbe_cal - 273.15;
        float Tref_Vbe_cal = Vbe_cal - (T_calib - T_REF) * TC_VBE;
        float kPTAT = (VBE_TARGET - Tref_Vbe_cal) * KPTAT_CORNER + KPTAT_CURVATURE;
        
        float A = A0 * (Vbe_cal + ALPHA * dVbe_cal) * (1 + kPTAT);
        float B = -273.15 * (1 + kPTAT) - kPTAT * T_calib;

        float T_cal = temp_raw / 1048576;
        float mu = T_cal / (1 + ALPHA * T_cal);
        m_temp = (A * mu) + B;

        return RESULT_SUCCESS;
    }
    
    virtual int getStatus() const {
        if (m_status == STATUS_OFF) { return STATUS_OFF; }
        if (m_status == STATUS_ERROR) { return STATUS_ERROR; }

        // read data value from register
        uint8_t* stat;
        if (m_i2c.readBytesReg(DPS422XTSA1_MEAS_CFG, stat, 1) == -1) {
            cerr << "Unable to read byte from measurements register." << endl;
            return STATUS_ERROR;
        }
        
        switch(*stat & 0x7) {
            case 0x0:
            case 0x4:
                cout << "Altimeter in Standby Mode. No measurements being taken." << endl;
                continue;
            case 0x1:
                cout << "Altimeter in Command Mode. One Pressure measurement being performed according to the selected precision." << endl;
                continue;
            case 0x2:
                cout << "Altimeter in Command Mode. One Temperature measurement being performed according to the selected precision." << endl;
                continue;
            case 0x3:
                cout << "Altimeter in Command Mode. One Temperature and one Pressure measurement being performed according to the selected precision." << endl;
                continue;
            case 0x5:
                cout << "Altimeter in Background Mode. Continuous Pressure measurements being taken according to the selected precision." << endl;
                continue;
            case 0x6:
                cout << "Altimeter in Background Mode. Continuous Temperature measurements being taken according to the selected precision." << endl;
                continue;
            case 0x7:
                cout << "Altimeter in Background Mode. Continuous Temperature and Pressure measurements being taken according to the selected precision." << endl;
                continue;
            default:
                return STATUS_ERROR;
        }
        return STATUS_IDLE;
    }
    
    virtual void printSensorInfo() const {
        cout << "Name: DPS422XTSA1" << endl;
        cout << "Status: " << getStatus() << endl;
    }

    virtual void printValues() const {
        cout << "Temperature: " << m_temp << endl;
        cout << "Pressure: " << m_pres << endl;
        cout << "Configuration Registers: " << endl;
        cout << "              Pressure: " << m_buffer[6] << endl;
        cout << "              Temperature: " << m_buffer[7] << endl;
        cout << "              Measurements: " << m_buffer[8] << endl;
    }
/* 
 kp corresponds to pressure resolution bits
   bit - Samples - kP
 • 000 -  256    - 524288
 • 001 -  512    - 1572864
 • 010 -  1024   - 3670016
 • 011 -  2048   - 7864320
 • 100 -  4096   - 253952
 • 101 -  8192   - 516096
 • 110 -  16384  - 1040384
 • 111 -  32768  - 2088960
 */
    int getkP() const { return m_kp[psr_resolution]; }

    void getPressureRate() const { return psr_rate; }
    void getPressureResolution() const { return psr_resolution; }
    void getTemperatureRate() const { return tmp_rate; }
    void getTemperatureResolution() const { return tmp_resolution; }

private:
    uint8_t psr_rate = 0, psr_resolution = 0;
    uint8_t tmp_rate = 0, tmp_resolution = 0;
    float m_pres = 0, m_temp = 0;
    float C00, C01, C02, C10, C11, C12, C20, C21, C30;
    float T_Vbe, T_dVbe, T_gain;
    const float m_kp[8] = [524288, 1572864, 3670016, 7864320, 253952, 516096, 1040384, 2088960];
    uint8_t m_buffer[BUFFER_SIZE];
    uint8_t p_constants[PSR_BUFF_SIZE];
    uint8_t t_constants[TMP_BUFF_SIZE];
}

#endif /* dps422xtsa1_h */
