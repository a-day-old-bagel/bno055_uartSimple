//
// Created by volundr on 7/19/16.
//

#include "Bno055Interface.h"

#define BNO055_DEVICE_FILE "/dev/ttyS0"

using namespace bno055;

int main() {
    Bno055Interface bno055;
    bno055.init(BNO055_DEVICE_FILE);
    if (bno055.isLive()) {
        printf("WORKED!!!\n");
    } else {
        printf("FAILED!!!\n");
    }
    fflush(stdout);
    return 0;
}

