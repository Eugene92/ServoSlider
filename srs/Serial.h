#ifndef SERIAL_H
#define SERIAL_H

#define ARDUINO_WAIT_TIME 2000

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class Serial
{
    private:
        HANDLE hSerial;
        bool connected;
        COMSTAT status;
        DWORD errors;
        DWORD bytesSend;

    public:
        Serial();
        Serial(int portNumber);
        Serial(char *portName);
        bool Open(int port, int baud);
        void OpenPort(char *portName, int baud);

        ~Serial();

        int ReadData(char *buffer, unsigned int nbChar);
        bool WriteData(char *buffer, unsigned int nbChar);
        bool IsConnected();

        int Send(char* buff, int szBuff);
        int Recv(char* buff, int szBuff);
        void Close();
        void Clean();
};

#endif // SERIAL_H
