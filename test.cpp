//
// Created by volundr on 7/19/16.
//

#include <vector>
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

    std::vector<int16_t> dataRecieved(10);
    while(bno055.queryChunk_16(dataRecieved.data(), QUA_Data_w_LSB, 20)) {
        std::cout << "GRAVITY -> ";
        std::cout << std::setiosflags(std::ios::right);
        std::cout << std::setiosflags(std::ios::fixed);
        std::cout << std::setw(10) << std::setprecision(4) <<  dataRecieved[7]
                  << std::setw(10) << std::setprecision(4) <<  dataRecieved[8]
                  << std::setw(10) << std::setprecision(4) <<  dataRecieved[9];
        std::cout << std::endl;
    }

    std::cout << "Data gathering halted, exiting!\n";

    return 0;
}

