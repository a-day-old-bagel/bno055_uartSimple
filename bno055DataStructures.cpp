//
// Created by volundr on 8/17/16.
//

#include "bno055DataStructures.h"

namespace bno055 {
    float   Vec3_f::operator [](int i) const { return index[i]; }
    float & Vec3_f::operator [](int i)       { return index[i]; }

    float   Vec4_f::operator [](int i) const { return index[i]; }
    float & Vec4_f::operator [](int i)       { return index[i]; }

    float   ImuData_f::operator [](int i) const { return index[i]; }
    float & ImuData_f::operator [](int i)       { return index[i]; }

    static void switchEndianess16(void* begin, int howManyToSwitch) {
        int16_t* begin16 = (int16_t*)begin;
        for (int i = 0; i < howManyToSwitch; ++i) {
            begin16[i] =  (begin16[i] << 8)  |
                          ((begin16[i] >> 8)  & (int16_t)0x00ff);
        }
    }

    void Vec3_16::switchEndianess() { switchEndianess16(this, 3); }
    Vec3_f Vec3_16::toFloats() {
        Vec3_f result {};
        for (int i = 0; i < 3; ++i) {
            result.index[i] = (float)index[i];
        }
        return result;
    }
    Vec3_f Vec3_16::toFusionEulerOrientation() {
        Vec3_f result {};
        for (int i = 0; i < 3; ++i) {
            result.index[i] = (float)index[i] / 16.f;
        }
        return result;
    }
    int16_t   Vec3_16::operator [](int i) const { return index[i]; }
    int16_t & Vec3_16::operator [](int i)       { return index[i]; }

    void Vec4_16::switchEndianess() { switchEndianess16(this, 4); }
    Vec4_f Vec4_16::toFloats() {
        Vec4_f result {};
        for (int i = 0; i < 4; ++i) {
            result.index[i] = (float)index[i];
        }
        return result;
    }
    int16_t   Vec4_16::operator [](int i) const { return index[i]; }
    int16_t & Vec4_16::operator [](int i)       { return index[i]; }

    void ImuData_16::switchEndianess() { switchEndianess16(this, 22); }
    ImuData_f ImuData_16::toFloats() {
        ImuData_f result {};
        for (int i = 0; i < 22; ++i) {
            result.index[i] = (float)index[i];
        }
        return result;
    }
    int16_t   ImuData_16::operator [](int i) const { return index[i]; }
    int16_t & ImuData_16::operator [](int i)       { return index[i]; }

    OutboundPacketHeader::OutboundPacketHeader(uint8_t regAddr, uint8_t length, uint8_t readOrWrite) {
        names.start         = SEND_START_HEADER_BYTE;
        names.readOrWrite   = readOrWrite;
        names.regAddr       = regAddr;
        names.length        = length;
    }

    OutboundPacket::OutboundPacket(uint8_t regAddr, uint8_t length, uint8_t readOrWrite)
            : header(regAddr, length, readOrWrite) { }
    uint8_t* OutboundPacket::bytes() {
        return (uint8_t*) this;
    }
    std::string OutboundPacket::toString() {
        std::stringstream ss;
        ss << "(0x) ";
        uint8_t* myBytes = bytes();
        int realLength = (header.names.readOrWrite == SEND_READ_HEADER_BYTE ? 4 : header.names.length);
        for (int i = 0; i < realLength; ++i) {
            ss << std::hex << (uint32_t)myBytes[i] << " ";
        }
        return ss.str();
    }

    RegisterWritePacket::RegisterWritePacket(uint8_t regAddr, uint8_t length, uint8_t* data)
            : OutboundPacket(regAddr, length, SEND_WRITE_HEADER_BYTE), length(length + sizeof(OutboundPacket))
    {
        memcpy(&this->data, data, length);
    }

    RegisterReadPacket::RegisterReadPacket(uint8_t regAddr, uint8_t length)
            : OutboundPacket(regAddr, length, SEND_READ_HEADER_BYTE) { }

    #define EMIT_CASE(e) case e: return #e
    static std::string ackToString(int err) {
        switch (err) {
            EMIT_CASE(WRITE_SUCCESS);
            EMIT_CASE(READ_FAIL);
            EMIT_CASE(WRITE_FAIL);
            EMIT_CASE(REGMAP_INVALID_ADDRESS);
            EMIT_CASE(REGMAP_WRITE_DISABLED);
            EMIT_CASE(WRONG_START_BYTE);
            EMIT_CASE(BUS_OVER_RUN_ERROR);
            EMIT_CASE(MAX_LENGTH_ERROR);
            EMIT_CASE(MIN_LENGTH_ERROR);
            EMIT_CASE(RECEIVE_CHARACTER_TIMEOUT);
            default:
                return std::to_string(err);
        }
    }
    #undef EMIT_CASE
    int ReceivedRead::readFrom(UartInterface& uart) {
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
    bool ReceivedRead::isValidRead() {
        return response == RECV_READ_HEADER_BYTE;
    }
    bool ReceivedRead::isActuallyAnAck() {
        return response == RECV_ACK_HEADER_BYTE;
    }
    std::string ReceivedRead::getAck() {
        return ackToString(length);
    }
    std::string ReceivedRead::toString() {
        std::stringstream ss;
        ss << "(0x) ";
        uint8_t* myBytes = (uint8_t*)this;
        int realLength = 8;
        for (int i = 0; i < realLength; ++i) {
            ss << std::hex << (uint32_t)myBytes[i] << " ";
        }
        return ss.str();
    }

    int ReceivedAck::readFrom(UartInterface& uart) {
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
    int ReceivedAck::readFrom(ReceivedRead& read) {
        response = read.response;
        status = read.length;
        if (response == RECV_ACK_HEADER_BYTE) {
            return RECEIVED_EXPECTED;
        }
        return RECEIVED_FAIL;
    }
    bool ReceivedAck::isValidAck() {
        return response == RECV_ACK_HEADER_BYTE;
    }
    bool ReceivedAck::isActuallyARead() {
        return response == RECV_READ_HEADER_BYTE;
    }
    bool ReceivedAck::isErrorStatus() {
        return status != WRITE_SUCCESS;
    }
}