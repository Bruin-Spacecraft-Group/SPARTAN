#include <iostream>
#include "../sensors.h"
#include "lsm6ds33.h"
#include <unistd.h>
int main(int argc, char * argv[])
{
	LSM6DS33 lsm6(1, 1);

	std::cout<<"lsm instance created" << std::endl;

	lsm6.powerOn();
    
	std::cout << "Input number of desired readings: " << std::endl;

	unsigned int numOfReadings;
	std::cin >> numOfReadings;

	std::cout << "Total number of readings: " << numOfReadings << std::endl;
/*    
	for (unsigned int i = 0; i < numOfReadings; i++)
	{
		lsm6.poll();
		lsm6.printRawValues();
        lsm6.printValues();
		usleep(1000000);
	} 
*/
    lsm6.calibrate(numOfReadings);
    std::cout << lsm6.avg[0] << std::endl;
    std::cout << lsm6.avg[1] << std::endl;
    std::cout << lsm6.avg[2] << std::endl;

	lsm6.printSensorInfo();

	// std::cout << std::endl << std::endl;
	// std::cout << "getBusID: " << lsm6.getBusID() << std::endl;
	// //std::cout << "getStatus: " << lsm6.getStatus() << std::endl;
	// std::cout << "getInstance: " << lsm6.getInstance() << std::endl;
	// //std::cout << "getI2C: " << lsm6.getI2C() << std::endl;

	lsm6.powerOff();

	return 0;
}
