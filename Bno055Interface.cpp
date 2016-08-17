//
// Created by volundr on 7/19/16.
//

#include <vector>
#include <iostream>
#include "Bno055Interface.h"

#define RESPONSE_WAIT_WRITE 2000
#define RESPONSE_WAIT_READ  50000

namespace bno055 {

    bool Bno055Interface::init(const char* bno055File) {

        #define REPORT_FAILURE(byteSent) std::cout << "Did not receive response after sending " byteSent "\n"; wasSuccess = false
        bool wasSuccess = true;
        if ( ! uart.openPort(bno055File, BNO055_BAUD_RATE) ) {
            std::cout << "Could not open serial connection to bno055!\n";
            wasSuccess = false;
        }
        if ( ! writeByte(OPR_MODE, CONFIG) ) {
            REPORT_FAILURE("OPR_MODE");
            wasSuccess = false;
        }
        if ( ! writeByte(PWR_MODE, NORMAL) ) {
            REPORT_FAILURE("PWR_MODE");
            wasSuccess = false;
        }
        if ( ! writeByte(Page_ID, 0) ) {
            REPORT_FAILURE("Page_ID");
            wasSuccess = false;
        }
        if ( ! writeByte(SYS_TRIGGER, 0) ) {
            REPORT_FAILURE("SYS_TRIGGER");
            wasSuccess = false;
        }
        if ( ! writeByte(UNIT_SEL, 0x83) ) {
            REPORT_FAILURE("UNIT_SEL");
            wasSuccess = false;
        }
        if ( ! writeByte(AXIS_MAP_CONFIG, 0x24) ) {
            REPORT_FAILURE("AXIS_MAP_CONFIG");
            wasSuccess = false;
        }
        if ( ! writeByte(AXIS_MAP_SIGN, 0x06) ) {
            REPORT_FAILURE("AXIS_MAP_SIGN");
            wasSuccess = false;
        }
        if ( ! writeByte(OPR_MODE, NDOF) ) {
            REPORT_FAILURE("OPR_MODE");
            wasSuccess = false;
        }
        #undef REPORT_FAILURE

        hasInit = wasSuccess;
        return wasSuccess;
    }

    bool Bno055Interface::write(uint8_t regAddr, uint8_t length, uint8_t* data) {
        RegisterWritePacket packetToSend(regAddr, length, data);
        ReceivedAck ack;
        int responseWait = RESPONSE_WAIT_WRITE; // microseconds
        int loopCounter = 0;
        do {
            uart.sendData(packetToSend.bytes(), packetToSend.length);
            usleep(responseWait); // 2 ms
            // If stuck in this while loop for an entire second, print a message and reset counter.
            if (++loopCounter >= 1000000 / responseWait) {
                loopCounter = 0;
                std::cout << "Waiting for write response...";
            }
        } while (ack.readFrom(uart) != RECEIVED_EXPECTED || ack.isErrorStatus());
        return true;
    }

    static bool pullData(RegisterReadPacket& readRequestPacket, ReceivedRead& dataReceived, UartInterface& uart) {
        int responseWait = RESPONSE_WAIT_READ; // microseconds
        int loopCounter = 0;
        do {
            uart.sendData(readRequestPacket.bytes(), readRequestPacket.length);
            usleep(responseWait); // 2 ms
            // If stuck in this while loop for an entire second, print a message and reset counter.
            if (++loopCounter >= 1000000 / responseWait) {
                loopCounter = 0;
                std::cout << "Waiting for read response...\n";
            }
            int receivedExpected = dataReceived.readFrom(uart);
            if (receivedExpected == RECEIVED_EXPECTED) {
                break;
            } else if (receivedExpected == RECEIVED_ACK) {
                std::cout << "Read request failed: " << dataReceived.getAck() << " request was: ";
                std::cout << "\t" << readRequestPacket.toString() << std::endl;
            } else {
                std::cout << "# " << dataReceived.toString() << std::endl;
            }
        } while(true);
    }

    bool Bno055Interface::updateImuData(ImuData* out) {
        RegisterReadPacket readRequestPacket(ACC_DATA_X_LSB, 46);
        ReceivedRead dataReceived;
        pullData(readRequestPacket, dataReceived, uart);
//        int responseWait = RESPONSE_WAIT_READ; // microseconds
//        int loopCounter = 0;
//        do {
//            uart.sendData(readRequestPacket.bytes(), readRequestPacket.length);
//            usleep(responseWait); // 2 ms
//            // If stuck in this while loop for an entire second, print a message and reset counter.
//            if (++loopCounter >= 1000000 / responseWait) {
//                loopCounter = 0;
//                std::cout << "Waiting for read response...\n";
//            }
//            int receivedExpected = dataReceived.readFrom(uart);
//            if (receivedExpected == RECEIVED_EXPECTED) {
////                std::cout << "Read request successful!\n";
//                break;
//            } else if (receivedExpected == RECEIVED_ACK) {
//                std::cout << "Read request failed: " << dataReceived.getAck() << " request was: ";
//                std::cout << "\t" << readRequestPacket.toString() << std::endl;
////                return false;
//            } else {
//                std::cout << "# " << dataReceived.toString() << std::endl;
//            }
//        } while(true);
        *out = *(ImuData*)&dataReceived.data;
        return true;
    }

    bool Bno055Interface::writeByte(uint8_t regAddr, uint8_t data) {
        return write(regAddr, 1, &data);
    }

    bool Bno055Interface::isLive() {
        return hasInit;
    }
}

