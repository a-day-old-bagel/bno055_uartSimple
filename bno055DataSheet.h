//
// Created by volundr on 7/6/16.
//

#ifndef BNO055_BNO055ENUM_H
#define BNO055_BNO055ENUM_H

#include <cstring>
#include <sstream>
#include "UartInterface.h"

#define BNO055_BAUD_RATE B115200
#define BNO055_SEND_HEADER_LENGTH 4
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

    #define EMIT_CASE_ERROR_ENUM(e) case e: return #e
    static std::string ackToString(int err) {
        switch (err) {
            EMIT_CASE_ERROR_ENUM(WRITE_SUCCESS);
            EMIT_CASE_ERROR_ENUM(READ_FAIL);
            EMIT_CASE_ERROR_ENUM(WRITE_FAIL);
            EMIT_CASE_ERROR_ENUM(REGMAP_INVALID_ADDRESS);
            EMIT_CASE_ERROR_ENUM(REGMAP_WRITE_DISABLED);
            EMIT_CASE_ERROR_ENUM(WRONG_START_BYTE);
            EMIT_CASE_ERROR_ENUM(BUS_OVER_RUN_ERROR);
            EMIT_CASE_ERROR_ENUM(MAX_LENGTH_ERROR);
            EMIT_CASE_ERROR_ENUM(MIN_LENGTH_ERROR);
            EMIT_CASE_ERROR_ENUM(RECEIVE_CHARACTER_TIMEOUT);
            default:
                return std::to_string(err);
        }
    }
    #undef EMIT_CASE_ERROR_ENUM

    enum ReceptionStatus {
        RECEIVED_EXPECTED,
        RECEIVED_WRONG_LENGTH,
        RECEIVED_ACK,
        RECEIVED_READ,
        RECEIVED_FAIL,
    };

    struct vec3_f {
        union {
            struct {
                float x, y, z;
            };
            struct {
                float heading, roll, pitch;
            };
            float index[3];
        };
    };
    struct vec4_f {
        union {
            struct {
                float w, x, y, z;
            };
            float index[4];
        };
    };
    struct ImuData_f {
        union {
            struct {
                vec3_f accel;
                vec3_f mag;
                vec3_f gyr;
                vec3_f orient;
                vec4_f quat;
                vec3_f linAccel;
                vec3_f grav;
            } names;
            float index[22];
        };
        int8_t temperature;
        uint8_t calibration;
    };

    static void switchEndianess16(void* begin, int howManyToSwitch) {
        int16_t* begin16 = (int16_t*)begin;
        for (int i = 0; i < howManyToSwitch; ++i) {
            begin16[i] =  (begin16[i] << 8)  |
                         ((begin16[i] >> 8)  & (int16_t)0x00ff);
        }
    }
    struct vec3_16 {
        union {
            struct {
                int16_t x, y, z;
            };
            struct {
                int16_t heading, roll, pitch;
            };
            int16_t index[3];
        };
        void switchEndianess() { switchEndianess16(this, 3); }
        vec3_f toFloats() {
            vec3_f result {};
            for (int i = 0; i < 3; ++i) {
                result.index[i] = (float)index[i];
            }
            return result;
        }
        vec3_f toFloatsDeg() {
            vec3_f result {};
            for (int i = 0; i < 3; ++i) {
                result.index[i] = (float)index[i] / 16.f;
            }
            return result;
        }
    };
    struct vec4_16 {
        union {
            struct {
                int16_t w, x, y, z;
            };
            int16_t index[3];
        };
        void switchEndianess() { switchEndianess16(this, 4); }
        vec4_f toFloats() {
            vec4_f result {};
            for (int i = 0; i < 4; ++i) {
                result.index[i] = (float)index[i];
            }
            return result;
        }
    };
    struct ImuData_16 {
        union {
            struct {
                vec3_16 accel;
                vec3_16 mag;
                vec3_16 gyr;
                vec3_16 orient;
                vec4_16 quat;
                vec3_16 linAccel;
                vec3_16 grav;
            } names;
            uint16_t index[22];
        };
        int8_t temperature;
        uint8_t calibration;
        void switchEndianess() { switchEndianess16(this, 22); }
        ImuData_f toFloats() {
            ImuData_f result {};
            for (int i = 0; i < 22; ++i) {
                result.index[i] = (float)index[i];
            }
            return result;
        }
    };

    union OutboundPacketHeader {
        union {
            struct {
                uint8_t start;
                uint8_t readOrWrite;
                uint8_t regAddr;
                uint8_t length;
            } names;
            uint8_t index[4];
        };
        OutboundPacketHeader(uint8_t regAddr, uint8_t length, uint8_t readOrWrite) {
            names.start         = SEND_START_HEADER_BYTE;
            names.readOrWrite   = readOrWrite;
            names.regAddr       = regAddr;
            names.length        = length;
        }
    };

    struct OutboundPacket {
    protected:
        OutboundPacketHeader header;
        OutboundPacket(uint8_t regAddr, uint8_t length, uint8_t readOrWrite) : header(regAddr, length, readOrWrite) { }
    public:
        uint8_t* bytes() {
            return (uint8_t*) this;
        }
        std::string toString() {
            std::stringstream ss;
            ss << "(0x) ";
            uint8_t* myBytes = bytes();
            int realLength = (header.names.readOrWrite == SEND_READ_HEADER_BYTE ? 4 : header.names.length);
            for (int i = 0; i < realLength; ++i) {
                ss << std::hex << (uint32_t)myBytes[i] << " ";
            }
            return ss.str();
        }
    };

    struct RegisterWritePacket : public OutboundPacket {
        uint8_t data[BNO055_MAX_PACKET_DATA_LENGTH];
        uint8_t length = 0;
        RegisterWritePacket(uint8_t regAddr, uint8_t length, uint8_t* data)
                : OutboundPacket(regAddr, length, SEND_WRITE_HEADER_BYTE), length(length + sizeof(OutboundPacket))
        {
            memcpy(&this->data, data, length);
        }
    };

    struct RegisterReadPacket : public OutboundPacket {
        uint8_t length = 4;
        RegisterReadPacket(uint8_t regAddr, uint8_t length)
                : OutboundPacket(regAddr, length, SEND_READ_HEADER_BYTE) { }
    };

    struct ReceivedRead {
        uint8_t response    = 0;
        uint8_t length      = 0;
        uint8_t data[BNO055_MAX_PACKET_DATA_LENGTH];
        int readFrom(UartInterface& uart) {
            int64_t bytesReceived = uart.recvData((uint8_t*)this, 2);
            if (isValidRead() && bytesReceived == 2) {
                bytesReceived = uart.recvData(&data[0], BNO055_MAX_PACKET_DATA_LENGTH);
                if (bytesReceived == length) {
                    return RECEIVED_EXPECTED;
                } else {
                    return RECEIVED_WRONG_LENGTH;
                }
            }
            if (isActuallyAnAck()) {
                return RECEIVED_ACK;
            }
            return RECEIVED_FAIL;
        }
        bool isValidRead() {
            return response == RECV_READ_HEADER_BYTE;
        }
        bool isActuallyAnAck() {
            return response == RECV_ACK_HEADER_BYTE;
        }
        std::string getAck() {
            return ackToString(length);
        }
        std::string toString() {
            std::stringstream ss;
            ss << "(0x) ";
            uint8_t* myBytes = (uint8_t*)this;
            int realLength = 8;
            for (int i = 0; i < realLength; ++i) {
                ss << std::hex << (uint32_t)myBytes[i] << " ";
            }
            return ss.str();
        }
    };

    struct ReceivedAck {
        uint8_t response    = 0;
        uint8_t status      = 0;
        int readFrom(UartInterface& uart) {
            int64_t bytesReceived = uart.recvData((uint8_t*)this, 2);
            if (bytesReceived == 2) {
                if (isValidAck()) {
                    return RECEIVED_EXPECTED;
                }
            }
            if (isActuallyARead()) {
                return RECEIVED_READ;
            }
            return RECEIVED_FAIL;
        }
        int readFrom(ReceivedRead& read) {
            response = read.response;
            status = read.length;
            if (response == RECV_ACK_HEADER_BYTE) {
                return RECEIVED_EXPECTED;
            }
            return RECEIVED_FAIL;
        }
        bool isValidAck() {
            return response == RECV_ACK_HEADER_BYTE;
        }
        bool isActuallyARead() {
            return response == RECV_READ_HEADER_BYTE;
        }
        bool isErrorStatus() {
            return status != WRITE_SUCCESS;
        }
    };

}

#endif //BNO055_BNO055ENUM_H
