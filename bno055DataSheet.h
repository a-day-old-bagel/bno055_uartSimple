//
// Created by volundr on 7/6/16.
//

#ifndef BNO055_BNO055ENUM_H
#define BNO055_BNO055ENUM_H

#include <cstring>
#include <sstream>
#include "UartInterface.h"

#define BNO055_BAUD_RATE B115200
#define BNO055_MAX_PACKET_DATA_LENGTH 128

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
        /*Reserved,*/
        OPR_MODE = 0x3D,
        PWR_MODE,
        SYS_TRIGGER,
        TEMP_SOURCE,
        AXIS_MAP_CONFIG,
        AXIS_MAP_SIGN,
        /*Reserved,...,*/
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

        /*Reserved,...,*/
        /*Page_ID=0x07,*/
        ACC_Config = 0x08,
        MAG_Config,
        GYR_Config_0,
        GYR_Config_1,
        ACC_Sleep_Config,
        GYR_Sleep_Config,
        /*Reserved,*/
        INT_MSK = 0x0F,
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
        /*Reserved,...,*/
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
        /*Reserved,...,*/
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
    enum PacketFormat {
        SEND_START_HEADER_BYTE = 0xAA,
        SEND_WRITE_HEADER_BYTE = 0x00,
        SEND_READ_HEADER_BYTE  = 0x01,
        RECV_ACK_HEADER_BYTE   = 0xEE,
        RECV_READ_HEADER_BYTE  = 0xBB,
    };
    enum AckResponse {
        WRITE_SUCCESS = 0x01,
        READ_FAIL,
        WRITE_FAIL,
        REGMAP_INVALID_ADDRESS,
        REGMAP_WRITE_DISABLED,
        WRONG_START_BYTE,
        BUS_OVER_RUN_ERROR,
        MAX_LENGTH_ERROR,
        MIN_LENGTH_ERROR,
        RECEIVE_CHARACTER_TIMEOUT,
    };
}

#endif //BNO055_BNO055ENUM_H
