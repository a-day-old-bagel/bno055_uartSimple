//
// Created by volundr on 7/6/16.
//

#ifndef BNO055_BNO055ENUM_H
#define BNO055_BNO055ENUM_H

#include <stdint.h>

namespace bno055 {

    enum RegistersPage0 {

        CHIP_ID=0,
        ACC_ID,
        MAG_ID,
        GYR_ID,
        SW_REV_ID_LSB,
        SW_REV_ID_MSB,
        BL_Rev_ID,
        Page_ID,
        ACC_DATA_X_LSB,
        ACC_DATA_X_MSB,
        ACC_DATA_Y_LSB,
        ACC_DATA_Y_MSB,
        ACC_DATA_Z_LSB,
        ACC_DATA_Z_MSB,
        MAG_DATA_X_LSB,
        MAG_DATA_X_MSB,
        MAG_DATA_Y_LSB,
        MAG_DATA_Y_MSB,
        MAG_DATA_Z_LSB,
        MAG_DATA_Z_MSB,
        GYR_DATA_X_LSB,
        GYR_DATA_X_MSB,
        GYR_DATA_Y_LSB,
        GYR_DATA_Y_MSB,
        GYR_DATA_Z_LSB,
        GYR_DATA_Z_MSB,
        EUL_Heading_LSB,
        EUL_Heading_MSB,
        EUL_Roll_LSB,
        EUL_Roll_MSB,
        EUL_Pitch_LSB,
        EUL_Pitch_MSB,
        QUA_Data_w_LSB,
        QUA_Data_w_MSB,
        QUA_Data_x_LSB,
        QUA_Data_x_MSB,
        QUA_Data_y_LSB,
        QUA_Data_y_MSB,
        QUA_Data_z_LSB,
        QUA_Data_z_MSB,
        LIA_Data_X_LSB,
        LIA_Data_X_MSB,
        LIA_Data_Y_LSB,
        LIA_Data_Y_MSB,
        LIA_Data_Z_LSB,
        LIA_Data_Z_MBS,
        GRV_Data_X_LSB,
        GRV_Data_X_MSB,
        GRV_Data_Y_LSB,
        GRV_Data_Y_MSB,
        GRV_Data_Z_LSB,
        GRV_Data_Z_MSB,
        TEMP,
        CALIB_STAT,
        ST_RESULT,
        INT_STA,
        SYS_CLK_STATUS,
        SYS_STATUS,
        SYS_ERR,
        UNIT_SEL,
        Reserved,
        OPR_MODE,
        PWR_MODE,
        SYS_TRIGGER,
        TEMP_SOURCE,
        AXIS_MAP_CONFIG,
        AXIS_MAP_SIGN,

        ACC_OFFSET_X_LSB=0x55,
        ACC_OFFSET_X_MSB,
        ACC_OFFSET_Y_LSB,
        ACC_OFFSET_Y_MSB,
        ACC_OFFSET_Z_LSB,
        ACC_OFFSET_Z_MSB,
        MAG_OFFSET_X_LSB,
        MAG_OFFSET_X_MSB,
        MAG_OFFSET_Y_LSB,
        MAG_OFFSET_Y_MSB,
        MAG_OFFSET_Z_LSB,
        MAG_OFFSET_Z_MSB,
        GYR_OFFSET_X_LSB,
        GYR_OFFSET_X_MSB,
        GYR_OFFSET_Y_LSB,
        GYR_OFFSET_Y_MSB,
        GYR_OFFSET_Z_LSB,
        GYR_OFFSET_Z_MSB,
        ACC_RADIUS_LSB,
        ACC_RADIUS_MSB,
        MAG_RADIUS_LSB,
        MAG_RADIUS_MSB,
    };

    enum RegisterPage1 {

        Page_ID=0x07,
        ACC_Config,
        MAG_Config,
        GYR_Config_0,
        GYR_Config_1,
        ACC_Sleep_Config,
        GYR_Sleep_Config,
        Reserved,
        INT_MSK,
        INT_EN,
        ACC_AM_THRES,
        ACC_INT_SET,
        ACC_HG_DURATION,
        ACC_HG_THRES,
        ACC_NM_THRES,
        ACC_NM_SET,
        GYR_INT_SET,
        GYR_HR_X_SET,
        GYR_DUR_X,
        GYR_HR_Y_SET,
        GYR_DUR_Y,
        GYR_HR_Z_SET,
        GYR_DUR_Z,
        GYR_AM_THRES,
        GYR_AM_SET,

        UNIQE_ID_0=0x50,
        UNIQE_ID_1=0x51,
        UNIQE_ID_2=0x52,
        UNIQE_ID_3=0x53,
        UNIQE_ID_4=0x54,
        UNIQE_ID_5=0x55,
        UNIQE_ID_6=0x56,
        UNIQE_ID_7=0x57,
        UNIQE_ID_8=0x58,
        UNIQE_ID_9=0x59,
        UNIQE_ID_A=0x5A,
        UNIQE_ID_B=0x5B,
        UNIQE_ID_C=0x5C,
        UNIQE_ID_D=0x5D,
        UNIQE_ID_E=0x5E,
        UNIQE_ID_F=0x5F,
    };

    enum OpMode {
        CONFIG,
        ACCONLY,
        MAGONLY,
        GYROONLY,
        ACCMAG,
        ACCGYRO,
        MAGGYRO,
        AMG,
        IMU,
        COMPASS,
        M4G,
        NDOF_FMC_OFF,
        NDOF,
    };

    enum PowerMode {
        NORMAL,
        LOW,
        SUSPEND
    };

    struct ImuData {
        union {
            struct {
                int16_t accX;//0 1
                int16_t accY;//2 3
                int16_t accZ;//4 5
                int16_t magX;//6 7
                int16_t magY;//8 9
                int16_t magZ;//10 11
                int16_t gyrX;//12 13
                int16_t gyrY;//14 15
                int16_t gyrZ;//16 17
                int16_t head;//18 19
                int16_t roll;//20 21
                int16_t pitc;//22 23
                int16_t quaW;// 24 25
                int16_t quaX;// 26 27
                int16_t quaY;// 28 29
                int16_t quaZ;// 30 31
                int16_t linaccX;//32 33
                int16_t linaccY;//34 35
                int16_t linaccZ;//36 37
                int16_t gravX;//38 39
                int16_t gravY;//40 41
                int16_t gravZ;//42 43
            } names;
            uint16_t index[22];
        };
        int8_t temperature;
        uint8_t calibration;
    };

}

#endif //BNO055_BNO055ENUM_H
