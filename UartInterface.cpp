//
// Created by volundr on 7/6/16.
//

#include "UartInterface.h"

namespace bno055 {

    /**
     * Opens communications with the UART device found at location 'deviceFile'
     * This code was taken from the 'Using the UART' tutorial page found at
     * http://www.raspberry-projects.com/pi/programming-in-c/uart-serial-port/using-the-uart
     */
    bool UartInterface::openPort(const char* deviceFile, tcflag_t baudRate) {
        /*
         * Close any existing serial communications
         */
        closePort();
        /*
         * OPEN THE UART
         * The flags (defined in fcntl.h):
         * 	Access modes (use 1 of these):
         * 		O_RDONLY - Open for reading only.
         * 		O_RDWR - Open for reading and writing.
         * 		O_WRONLY - Open for writing only.
         *
         * 	O_NDELAY / O_NONBLOCK (same function) -
         * 	Enables nonblocking mode. When set read requests on the file can return immediately with a failure status
         * 	if there is no input immediately available (instead of blocking). Likewise, sendData requests can also return
         * 	immediately with a failure status if the output can't be written immediately.
         *
         * 	O_NOCTTY -
         * 	When set and path identifies a terminal device, open() shall not cause the terminal device to become the
         * 	controlling terminal for the process.
         */
        uartFile = open(deviceFile, O_RDWR | O_NOCTTY | O_SYNC);		//Open in synchronous mode
        if (uartFile == -1) {
            return false;
        }

        /*
         * CONFIGURE THE UART
         * The flags (defined in /usr/include/termios.h -
         * see http://pubs.opengroup.org/onlinepubs/007908799/xsh/termios.h.html):
         *
         * 	Baud rate:  B1200, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800, B500000, B576000,
         * 	                B921600, B1000000, B1152000, B1500000, B2000000, B2500000, B3000000, B3500000, B4000000
         * 	CSIZE   :   CS5, CS6, CS7, CS8
         * 	CLOCAL  :   Ignore modem status lines
         * 	CREAD   :   Enable receiver
         * 	IGNPAR  :   Ignore characters with parity errors
         * 	ICRNL   :   Map CR to NL on input (Use for ASCII comms where you want to auto correct end of line characters
         * 	                - don't use for bianry comms!)
         * 	PARENB  :   Parity enable
         * 	PARODD  :   Odd parity (else even)
         */
        struct termios options;
        tcgetattr(uartFile, &options);
        options.c_cflag = baudRate | CS8 | CLOCAL | CREAD;		//<Set baud rate
        options.c_iflag = IGNPAR;
        options.c_oflag = 0;
        options.c_lflag = 0;
        tcflush(uartFile, TCIOFLUSH);
        tcsetattr(uartFile, TCSANOW, &options);

        return true;
    }

    bool UartInterface::closePort() {
        if (uartFile != -1) {
            close(uartFile);
            uartFile = -1;
            return true;
        }
        return false;
    }

    UartInterface::~UartInterface() {
        if (uartFile != -1) {
            close(uartFile);
        }
    }

    int64_t UartInterface::sendData(uint8_t* data, uint32_t length) {
        if (uartFile == -1) {
            return -1;
        } else {
            return (int64_t)write(uartFile, data, length);
        }
    }

    int64_t UartInterface::recvData(uint8_t* empty, uint32_t maxLength) {
        if (uartFile == -1) {
            return -1;
        } else {
            return (int64_t)read(uartFile, (void*)empty, maxLength);
        }
    }

}