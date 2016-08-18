//
// Created by volundr on 7/19/16.
//

#ifndef BNO055_BNO055INTERFACE_H
#define BNO055_BNO055INTERFACE_H

#include "UartInterface.h"
#include "bno055DataSheet.h"
#include "bno055DataStructures.h"

namespace bno055 {

    enum availableVec3sToQuery {
        ACCELERATION = ACC_DATA_X_LSB,
        MAGNETOMETER = MAG_DATA_X_LSB,
        GYROSCOPE    = GYR_DATA_X_LSB,
        EULER_ORIENT = EUL_Heading_LSB,
        LINEAR_ACCEL = LIA_Data_X_LSB,
        GRAVITY_VEC  = GRV_Data_X_LSB,
    };
    enum availableVec4sToQuery {
        QUATERNION_ORIENT = QUA_Data_w_LSB,
    };
    class Bno055Interface {
        UartInterface uart;
        bool hasInit = false;

        bool write(uint8_t regAddr, uint8_t length, uint8_t* data);
        bool writeByte(uint8_t regAddr, uint8_t data);
    public:
        bool init(const char* bno055File);
        bool isLive();
        bool queryImuData(ImuData_16* out);
        bool queryVec3(Vec3_16* vec3Out, availableVec3sToQuery regBegin);
        bool queryVec4(Vec4_16* vec4Out, availableVec4sToQuery regBegin);
    };
}

#endif //BNO055_BNO055INTERFACE_H
