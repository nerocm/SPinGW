#ifndef SERIALPORT_H
#define SERIALPORT_H
#include <windows.h>

#define COMREADINTT 50
#define COMREADTOTM 10
#define COMREADTOTC 50
#define COMWRITETOTM 10
#define COMWRITETOTC 50

enum Baudrate
{
	B50	= 50,
	B110	= 110,
	B150	= 150,
	B300	= 300,
	B1200	= 1200,
	B2400	= 2400,
	B4800	= 4800,
	B9600   = 9600,
	B19200	= 19200,
	B38400	= 38400,
	B57600	= 57600,
	B115200 = 115200,
	B230400	= 230400,
	B460800	= 460800,
	B500000 = 500000,
	B1000000= 1000000
};

enum Stopbits
{
	one = ONESTOPBIT,
	onePointFive = ONE5STOPBITS,
	two = TWOSTOPBITS
};

enum Paritycheck
{
	even = EVENPARITY,
	odd  = ODDPARITY,
	off  = NOPARITY,
	mark = MARKPARITY	
};


void ErrorExit(LPTSTR lpszFunction); 


/**
	\brief Opens a new connection to a serial port
	\param portname		name of the serial port(COM1 - COM9 or \\\\.\\COM1-COM256)
	\param baudrate		the baudrate of this port (for example 9600)
	\param stopbits		th nuber of stoppbits (one, onePointFive or two)
	\param parity		the parity (even, odd, off or mark)
	\return			HANDLE to the serial port
	*/
HANDLE openSerialPort(LPCSTR portname,enum Baudrate baudrate, enum Stopbits stopbits, enum Paritycheck parity);

/**
	\brief Opens a new connection to a serial port
	\param portname		name of the serial port(COM1 - COM9 or \\\\.\\COM1-COM256)
	\param baudrate		the baudrate of this port (for example 9600)
	\param stopbits		th nuber of stoppbits (one, onePointFive or two)
	\param parity		the parity (even, odd, off or mark)
	\param flags		pass special access flags
	\return			HANDLE to the serial port
	*/
HANDLE openSerialPortFlags(LPCSTR portname,enum Baudrate baudrate, enum Stopbits stopbits, enum Paritycheck parity, int flags);

/**
	\brief Set serial port timeouts
	\param hSerial		File HANDLE to the serial port
	\param readIntT		Read Interval Timeout value
	\param readTotM		Read Total Timeout Multiplier value
	\param readTotC		Read Total Timeout Constant value
	\param writeTotM		Write Total Timeout Multiplier value
	\param writeTotC		Write Total Timeout Constant value
	\return				nothing
	*/

void comTimeouts(HANDLE hSerial, int readIntT, int readTotM, int readTotC, int writeTotM, int writeTotC);
/**
	\brief Read data from the serial port
	\param hSerial		File HANDLE to the serial port
	\param buffer		pointer to the area where the read data will be written
	\param buffersize	maximal size of the buffer area
	\return				amount of that was read
	*/
DWORD readFromSerialPort(HANDLE hSerial, char * buffer, int buffersize);

/**
	\brief Read data from the serial port
	\param hSerial		File HANDLE to the serial port
	\param buffer		pointer to the area where the read data will be written
	\param buffersize	maximal size of the buffer area
	\param o		pointer to OVERLAPPED structure
	\return				amount of data that was read
	*/
DWORD readFromSerialPortOverlapped(HANDLE hSerial, char * buffer, int buffersize, OVERLAPPED * o);

/**
	\brief write data to the serial port
	\param hSerial	File HANDLE to the serial port
	\param buffer	pointer to the area where the read data will be read
	\param length	amount of data to be read
	\return			amount of data that was written
	*/
DWORD writeToSerialPort(HANDLE hSerial, char * data, int length);

void closeSerialPort(HANDLE hSerial);

/**
	\brief set the event mask for the serial port
	\param hSerial	File HANDLE to the serial port
	\param mask	contains the event interrups to monitor
	\return			0 on success or the error value
	*/
BOOL setSerialMask(HANDLE hSerial, int mask);
#endif
