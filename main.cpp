//
// Created by volundr on 7/19/16.
//

#include <iostream>
#include "Bno055Interface.h"
#include "bno055DataSheet.h"

#define BNO055_DEVICE_FILE "/dev/ttyS0"

using namespace bno055;

int main() {
    Bno055Interface bno055;
    bno055.init(BNO055_DEVICE_FILE);
    if (bno055.isLive()) {
        std::cout << "BNO055 is live.\n";
    } else {
        std::cout << "Could not contact BNO055!\n";
        return 1;
    }

    ImuData imuData;
    while(bno055.updateImuData(&imuData)) {
        std::cout << "-> " << imuData.names.head << " " << imuData.names.roll << " " << imuData.names.pitc << std::endl;
    }

    std::cout << "Data gathering halted, exiting!\n";

    return 0;
}

