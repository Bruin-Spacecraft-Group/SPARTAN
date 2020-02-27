#include "dps422xtsa1.h"
#include <iostream>
#include <unistd.h>

int main() {
    DPS422XTSA1 test(1,1,3,3,3,3);
    test.configureOperatingModes(7);
    printf("%d", test.poll());
    test.printSensorInfo();
    for(int i = 0; i < 50; i++) {
        test.poll();
        usleep(1000000);
        test.printValues();
    }
    cout << test.getkP() << endl;
}
