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
    std::cout << "Testing absolute orientation...\n";
    usleep(1000000);

    Vec3_16 orient;
    Vec3_f orientDeg;
    while(bno055.queryVec3(&orient, EULER_ORIENT)) {
        orientDeg = orient.toFusionEulerOrientation();
        std::cout << "-> ";
        std::cout << std::setiosflags(std::ios::right);
        std::cout << std::setiosflags(std::ios::fixed);
        std::cout << std::setw(10) << std::setprecision(4) << orientDeg.heading
                  << std::setw(10) << std::setprecision(4) << orientDeg.roll
                  << std::setw(10) << std::setprecision(4) << orientDeg.pitch;
        std::cout << std::endl;
    }

    std::cout << "Data gathering halted, exiting!\n";

    return 0;
}

