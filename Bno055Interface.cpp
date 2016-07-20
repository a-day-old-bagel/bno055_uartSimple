//
// Created by volundr on 7/19/16.
//

#include <vector>
#include <iostream>
#include "Bno055Interface.h"

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
//        int loopWaitTime = 2000; // microseconds
        int loopCounter = 0;
        do {
            uart.sendData(packetToSend.bytes(), packetToSend.length);
//            usleep(2000); // 2 ms
//            if (++loopCounter >= 1000000 / loopWaitTime) {
//                loopCounter = 0;
//                std::cout << "Waiting for response...";
//            }
            if (loopCounter++) {
                loopCounter = 0;
                std::cout << "Resending data...\n";
            }
        } while (ack.readFrom(uart) != RECEIVED_EXPECTED || ack.isErrorStatus());
        return true;
    }

    bool Bno055Interface::writeByte(uint8_t regAddr, uint8_t data) {
        return write(regAddr, 1, &data);
    }

    bool Bno055Interface::isLive() {
        return hasInit;
    }


}

