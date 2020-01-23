#ifndef AVIONICS_H

#define AVIONICS_H

#include "systems.h"

//avionics board
class Avionics: public System
{
public:
	Avionics(int busID, mraa::I2cMode frequency):System("I2C"), m_i2c(busID), m_frequency(frequency) {/*...*/}
	//connection type parameter currently set to a string input, but probably easier to simply map to global constant
	//dataRate of connection; do not currently know exact connection types, and therefore might not be needed

	bool setFrequency(mraa::I2cMode mode)
	{
		if (m_i2c.frequency(mode) == mraa::SUCCESS)
		{
			m_frequency = mode;
			return true;
		}
		else
			return false;
	}
	//sets the data rate for all sensors on the I2C bus

	mraa::I2cMode getFrequency() const
	{
		return m_frequency;
	}
	//sets the inputted I2CMode parameter to the current data rate for the I2c bus
 
private:
	mraa::I2c m_i2c;
	mraa::I2cMode m_frequency;
}

#endif