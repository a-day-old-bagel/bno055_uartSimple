//
// Created by volundr on 7/19/16.
//

#ifndef BNO055_BNO055INTERFACE_H
#define BNO055_BNO055INTERFACE_H

#include "UartInterface.h"
#include "bno055DataSheet.h"

namespace bno055 {
    class Bno055Interface {
        UartInterface uart;
        bool hasInit = false;

        bool write(uint8_t regAddr, uint8_t length, uint8_t* data);
        bool writeByte(uint8_t regAddr, uint8_t data);
    public:
        bool init(const char* bno055File);
        bool isLive();
        bool updateImuData(ImuData_16* out);
        bool updateOrientation(vec3_16* orient);
    };
}

#endif //BNO055_BNO055INTERFACE_H
