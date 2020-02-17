# Sensor Class musts & must nots

## Must implement functions

1. Identification

```c++ 
virtual const char * name() const = 0;
virtual void printSensorInfo() = 0;
// for example
virtual const char * name() const {
	const char * str = "LSM6DS33";
	return str;
}
```

2. Sensor control

```c++
virtual int powerOn() = 0;
virtual int powerOff() = 0;
// Update sensor data buffer
virtual bool poll() = 0; 
virtual bool pollData(DataPacket * & dp) = 0;
```

3. Debugging & printing
```c++
virtual int printValues() const = 0; // Return the number of lines printed.
void printEscapedValues(bool normalize) const {} // This do not need to be implemented 
```

## Generic function implementation for sensor class
These functions are implemented at `sensor.h`.
```c++
// Generic function implementation for the sensor class
int getBusID() const { return m_busID; }
//return status (operate with interfaced constants described in globals.h)
virtual int getStatus() const { return m_status; }
int getInstance() const { return m_instance; }
mraa::I2c getI2C() const { return m_i2c; }
```
