//
// Created by volundr on 7/19/16.
//

#include <vector>
#include <iostream>
#include "Bno055Interface.h"

#define RESPONSE_WAIT_WRITE 2000
#define RESPONSE_WAIT_READ  10000

namespace bno055 {

    bool Bno055Interface::init(const char* bno055File) {

        bool wasSuccess = true;
        if ( ! uart.openPort(bno055File, BNO055_BAUD_RATE) ) {
            std::cout << "Could not open serial connection to bno055!\n";
            wasSuccess = false;
        }
        #define TRY_SEND_BYTE(byteSent, value) \
                if ( ! writeByte(byteSent, value) ) {\
                std::cout << "Did not receive response after sending " #byteSent "\n";\
                wasSuccess = false; }
        TRY_SEND_BYTE(OPR_MODE, CONFIG)
        TRY_SEND_BYTE(PWR_MODE, NORMAL)
        TRY_SEND_BYTE(Page_ID, 0)
        TRY_SEND_BYTE(SYS_TRIGGER, 0)
        TRY_SEND_BYTE(UNIT_SEL, 0x83)
        TRY_SEND_BYTE(AXIS_MAP_CONFIG, 0x24)
        TRY_SEND_BYTE(AXIS_MAP_SIGN, 0x06)
        TRY_SEND_BYTE(OPR_MODE, NDOF)
        #undef TRY_SEND_BYTE

        hasInit = wasSuccess;
        return wasSuccess;
    }

    bool Bno055Interface::write(uint8_t regAddr, uint8_t length, uint8_t* data) {
        RegisterWritePacket packetToSend(regAddr, length, data);
        ReceivedAck ack;
        int loopCounter = 0;
        do {
            uart.sendData(packetToSend.bytes(), packetToSend.length);
            usleep(RESPONSE_WAIT_WRITE); // 2 ms
            if (++loopCounter >= 1000000 / RESPONSE_WAIT_WRITE) {
                std::cout << "Write timed out!\n";
                return false;
            }
        } while (ack.readFrom(uart) != RECEIVED_EXPECTED || ack.isErrorStatus());
        return true;
    }

    static bool pullData(RegisterReadPacket& readRequestPacket, ReceivedRead& dataReceived, UartInterface& uart) {
        int loopCounter = 0;
        do {
            uart.sendData(readRequestPacket.bytes(), readRequestPacket.length);
            usleep(RESPONSE_WAIT_READ);
            if (++loopCounter >= 1000000 / RESPONSE_WAIT_READ) {
                std::cout << "Read timed out!\n";
                return false;
            }
            int receivedExpected = dataReceived.readFrom(uart);
            if (receivedExpected == RECEIVED_EXPECTED) {
                break;
            } else if (receivedExpected == RECEIVED_ACK) {
                std::cout << "Read request failed: " << dataReceived.getAck() << ": request was: ";
                std::cout << readRequestPacket.toString() << std::endl;
            } else if (receivedExpected == RECEIVED_WRONG_LENGTH) {
                std::cout << "received wrong length." << std::endl;
            } else {
                std::cout << "received unexpected: " << dataReceived.toString() << std::endl;
            }
        } while(true);
        return true;
    }

    bool Bno055Interface::queryImuData(ImuData_16* out) {
        RegisterReadPacket readRequestPacket(ACC_DATA_X_LSB, 46);
        ReceivedRead dataReceived;
        if (!pullData(readRequestPacket, dataReceived, uart)) {
            return false;
        }
        *out = *(ImuData_16*)&dataReceived.data;
        return true;
    }

    bool Bno055Interface::queryVec3(Vec3_16* vec3Out, availableVec3sToQuery regBegin) {
        RegisterReadPacket readRequestPacket(regBegin, 6);
        ReceivedRead dataReceived;
        if (!pullData(readRequestPacket, dataReceived, uart)) {
            return false;
        }
        *vec3Out = *(Vec3_16*)&dataReceived.data;
        return true;
    }

    bool Bno055Interface::queryVec4(Vec4_16* vec4Out, availableVec4sToQuery regBegin) {
        RegisterReadPacket readRequestPacket(regBegin, 8);
        ReceivedRead dataReceived;
        if (!pullData(readRequestPacket, dataReceived, uart)) {
            return false;
        }
        *vec4Out = *(Vec4_16*)&dataReceived.data;
        return true;
    }

    bool Bno055Interface::queryChunk_16(int16_t *out, int start, size_t length) {
        RegisterReadPacket readRequestPacket((uint8_t) start, (uint8_t)length);
        ReceivedRead dataReceived;
        if (!pullData(readRequestPacket, dataReceived, uart)) {
            return false;
        }
        int16_t* data_16 = (int16_t*) dataReceived.data;
        for (int i = 0; i < length / 2; ++i) {
            out[i] = data_16[i];
        }
        *out = *(int16_t*)&dataReceived.data;
        return true;
    }

    bool Bno055Interface::writeByte(uint8_t regAddr, uint8_t data) {
        return write(regAddr, 1, &data);
    }

    bool Bno055Interface::isLive() {
        return hasInit;
    }
}

