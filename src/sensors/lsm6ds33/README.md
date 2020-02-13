# LSM6DS33 Manual

## On the Agenda
1. Test different ODR with different filters
    * Try applying 400Hz on 

## Configuration of **LSM6**

### Accelerometer

1. Accelerometer range settings

Available ranges: ±2g, ±4g, ±8g, ±16g
```c++
enum AccelRange { 
    _2g=0b0000, 
    _4g=0b1000, 
    _8g=0b1100, 
    _16g=0b0100
}; 	
    // (00: ±2 g; 01: ±16 g; 10: ±4 g; 11: ±8 g)
```

2. Accelerometer Anti-aliasing frequency
    
    By factory setting, each ODR (output data rate) has their own corresponding anti-aliasing bandwidth. 

    To implement custom filter, change `XL_BW_SCAL_ODR` to 1 (default 0) at register `CTRL4_C(13h)`.

    **IMPORTANT**: Filter not used when accelerometer is in normal and low-power modes (`XL_HM_MODE=1`). Also not used `6.66 ~ 3.33 kHz`.
    
    ODR|Filter
    ---|---
    6.66 - 3.33 kHz|No filter
    1.66 kHz|400 Hz
    833 Hz|400 Hz
    416 Hz|200 Hz
    208 Hz|100 Hz
    104 - 12.5 Hz|50 Hz
```c++
enum AccelAAFreq { 
    _400hz=0b00, 
    _200hz=0b01, 
    _100hz=0b10, 
    _50hz=0b11 
};
```

3. Accelerometer performance

On startup, the accelerometer is set to high performance. `XL_HM_MODE=0` To switch to normal/low power mode, set `XL_HM_MODE=1`

ODR | Value
:---:|---:|
12.5hz| 0b0001
26Hz|0b0010
52Hz|0b0011
104Hz|0b0100
208Hz|0b0101
416Hz|0b0110
833Hz|0b0111
1.66kHz|0b1000
3.33kHz|0b1001
6.66kHz|0b1010
// Ignore for now.

### Gyroscope

1. Gyro Range Settings
```c++
enum GyroRange { 
    _125dps=0b0010, 
    _250dps=0b0000, 
    _500dps=0b0100, 
    _1000dps=0b1000, 
    _2000dps=0b1100
}; 	
```

