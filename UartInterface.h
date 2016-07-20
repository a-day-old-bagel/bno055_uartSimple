//
// Created by volundr on 7/6/16.
//

#ifndef BNO055_UARTINTERFACE_H
#define BNO055_UARTINTERFACE_H

#include <stdio.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
#include <stdint.h>

namespace bno055 {

    class UartInterface {
        int uartFile = -1;
    public:
        ~UartInterface();
        bool    openPort(const char* deviceFile, tcflag_t baudRate);
        bool    closePort();
        int64_t sendData(uint8_t* data, uint32_t length);
        int64_t recvData(uint8_t* empty, uint32_t maxLength);
    };

}

#endif //BNO055_UARTINTERFACE_H
