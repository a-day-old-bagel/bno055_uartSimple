//
// Created by volundr on 7/19/16.
//

#include <iostream>
#include <iomanip>
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

    vec3_16 orient;
    vec3_f orientDeg;
    while(bno055.updateOrientation(&orient)) {
        orientDeg = orient.toFloatsDeg();
        std::cout << "-> ";
        std::cout << std::setiosflags(std::ios::right);
        std::cout << std::setiosflags(std::ios::fixed);
        std::cout << std::setw(10) << std::setprecision(4) << orientDeg.heading
                  << std::setw(10) << std::setprecision(4) << orientDeg.roll
                  << std::setw(10) << std::setprecision(4) << orientDeg.pitch;
        std::cout << std::endl;
    }

//    ImuData_16 imuData;
//    while(bno055.updateImuData(&imuData)) {
//        std::cout << "-> " << imuData.names.orient.heading << " "
//                  << imuData.names.orient.roll << " "
//                  << imuData.names.orient.pitch << std::endl;
//    }

    std::cout << "Data gathering halted, exiting!\n";

    return 0;
}

