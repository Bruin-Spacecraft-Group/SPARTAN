#include <iostream>
#include "sensors.h"
#include "lsm6ds33.h"

int main()
{
	LSM6DS33 lsm6(0, 1);

	lsm6.powerOn();

	std::cout << "Input number of desired readings: " << std::endl;
	unsigned int numOfReadings;
	std::cin >> numOfReadings;

	std::cout << "Total number of readings: " << numOfReadings << std::endl;

	for (unsigned int i = 0; i < numOfReadings; i++)
	{
		lsm6.poll();
		lsm6.printValues();
	}

	lsm6.printSensorInfo();

	// std::cout << std::endl << std::endl;
	// std::cout << "getBusID: " << lsm6.getBusID() << std::endl;
	// //std::cout << "getStatus: " << lsm6.getStatus() << std::endl;
	// std::cout << "getInstance: " << lsm6.getInstance() << std::endl;
	// //std::cout << "getI2C: " << lsm6.getI2C() << std::endl;

	lsm6.powerOff();

	return 0;
}