//
// Created by volundr on 7/19/16.
//

#include <vector>
#include "Bno055Interface.h"

namespace bno055 {

    bool Bno055Interface::init(const char* bno055File) {
        bool wasSuccess = true;
        printf("foo0\n");
        wasSuccess &= uart.openPort(bno055File, BNO055_BAUD_RATE);
        printf("foo1\n");
        wasSuccess &= writeByte(OPR_MODE, CONFIG);
        wasSuccess &= writeByte(PWR_MODE, NORMAL);
        wasSuccess &= writeByte(Page_ID, 0);
        wasSuccess &= writeByte(SYS_TRIGGER, 0);
        wasSuccess &= writeByte(UNIT_SEL, 0x83);
        wasSuccess &= writeByte(AXIS_MAP_CONFIG, 0x24);
        wasSuccess &= writeByte(AXIS_MAP_SIGN, 0x06);
        wasSuccess &= writeByte(OPR_MODE, NDOF);

        hasInit = wasSuccess;
        return wasSuccess;
    }

    bool Bno055Interface::write(uint8_t regAddr, uint8_t length, uint8_t* data) {
        RegisterWritePacket packetToSend(regAddr, length, data);
        uart.sendData(packetToSend.bytes(), packetToSend.length);
        ReceivedAck ack;
        ack.readFrom(uart);
        return (ack.isValidAck() && !ack.isErrorStatus());
    }

    bool Bno055Interface::writeByte(uint8_t regAddr, uint8_t data) {
        return write(regAddr, 1, &data);
    }

    bool Bno055Interface::isLive() {
        return hasInit;
    }


}

