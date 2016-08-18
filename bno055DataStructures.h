//
// Created by volundr on 8/17/16.
//

#ifndef BNO055_BNO055DATASTRUCTURES_H
#define BNO055_BNO055DATASTRUCTURES_H

#include "bno055DataSheet.h"

namespace bno055 {

    struct Vec3_f {
        union {
            struct { float       x,    y,     z; };
            struct { float heading, roll, pitch; };
            float index[3];
        };
        float   operator [](int i) const;
        float & operator [](int i)      ;
    };
    struct Vec4_f {
        union {
            struct { float w, x, y, z; };
            float index[4];
        };
        float   operator [](int i) const;
        float & operator [](int i)      ;
    };
    struct ImuData_f {
        union {
            struct {
                Vec3_f accel;
                Vec3_f mag;
                Vec3_f gyr;
                Vec3_f orient;
                Vec4_f quat;
                Vec3_f linAccel;
                Vec3_f grav;
            } names;
            float index[22];
        };
        int8_t temperature;
        uint8_t calibration;
        float   operator [](int i) const;
        float & operator [](int i)      ;
    };

    struct Vec3_16 {
        union {
            struct { int16_t       x,    y,     z; };
            struct { int16_t heading, roll, pitch; };
            int16_t index[3];
        };
        void switchEndianess();
        Vec3_f toFloats();
        Vec3_f toFusionEulerOrientation();
        int16_t   operator [](int i) const;
        int16_t & operator [](int i)      ;
    };
    struct Vec4_16 {
        union {
            struct { int16_t w, x, y, z; };
            int16_t index[3];
        };
        void switchEndianess();
        Vec4_f toFloats();
        int16_t   operator [](int i) const;
        int16_t & operator [](int i)      ;
    };
    struct ImuData_16 {
        union {
            struct {
                Vec3_16 accel;
                Vec3_16 mag;
                Vec3_16 gyr;
                Vec3_16 orient;
                Vec4_16 quat;
                Vec3_16 linAccel;
                Vec3_16 grav;
            } names;
            int16_t index[22];
        };
        int8_t temperature;
        uint8_t calibration;
        void switchEndianess();
        ImuData_f toFloats();
        int16_t   operator [](int i) const;
        int16_t & operator [](int i)      ;
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
        OutboundPacketHeader(uint8_t regAddr, uint8_t length, uint8_t readOrWrite);
    };

    struct OutboundPacket {
    protected:
        OutboundPacketHeader header;
        OutboundPacket(uint8_t regAddr, uint8_t length, uint8_t readOrWrite);
    public:
        uint8_t* bytes();
        std::string toString();
    };

    struct RegisterWritePacket : public OutboundPacket {
        uint8_t data[BNO055_MAX_PACKET_DATA_LENGTH];
        uint8_t length = 0;
        RegisterWritePacket(uint8_t regAddr, uint8_t length, uint8_t* data);
    };

    struct RegisterReadPacket : public OutboundPacket {
        uint8_t length = 4;
        RegisterReadPacket(uint8_t regAddr, uint8_t length);
    };

    enum ReceptionStatus {
        RECEIVED_EXPECTED,
        RECEIVED_WRONG_LENGTH,
        RECEIVED_ACK,
        RECEIVED_READ,
        RECEIVED_FAIL,
    };

    struct ReceivedRead {
        uint8_t response    = 0;
        uint8_t length      = 0;
        uint8_t data[BNO055_MAX_PACKET_DATA_LENGTH];
        int readFrom(UartInterface& uart);
        bool isValidRead();
        bool isActuallyAnAck();
        std::string getAck();
        std::string toString();
    };

    struct ReceivedAck {
        uint8_t response    = 0;
        uint8_t status      = 0;
        int readFrom(UartInterface& uart);
        int readFrom(ReceivedRead& read);
        bool isValidAck();
        bool isActuallyARead();
        bool isErrorStatus();
    };
}

#endif //BNO055_BNO055DATASTRUCTURES_H
