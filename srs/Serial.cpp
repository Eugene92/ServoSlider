#include "Serial.h"

Serial::Serial() {}

Serial::Serial(int portNumber)
{
    char portName[20];
    sprintf(portName,"\\\\.\\COM%d", portNumber);
    this->OpenPort(portName, CBR_9600);
}

Serial::Serial(char *portName)
{
    this->OpenPort(portName, CBR_9600);
}

Serial::~Serial()
{
    if(this->connected)
    {
        this->connected = false;
        CloseHandle(this->hSerial); // unknown method
    }
}

bool Serial::Open(int port, int baud)
{
    char portName[20];
    sprintf(portName,"\\\\.\\COM%d", port);
    this->OpenPort(portName, baud);

    return this->connected;
}

void Serial::OpenPort(char *portName, int baud=CBR_9600)
{
    this->connected = false;

    this->hSerial = CreateFileA(portName,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL, // | FILE_FLAG_OVERLAPPED
            NULL);

    if(this->hSerial==INVALID_HANDLE_VALUE)
    {
        if(GetLastError()==ERROR_FILE_NOT_FOUND){

            printf("ERROR: Handle was not attached. Reason: %s not available.\n", portName);

        }
        else
        {
            printf("ERROR!!!");
        }
    }
    else
    {
        DCB dcbSerialParams;


        memset(&dcbSerialParams,0,sizeof(dcbSerialParams));
        dcbSerialParams.DCBlength = sizeof(DCB);
//            GetCommState(m_Handle, &ComDCM);

        if (!GetCommState(this->hSerial, &dcbSerialParams))
        {
            printf("failed to get current serial parameters!");
        }
        else
        {
            dcbSerialParams.BaudRate=baud;
            dcbSerialParams.ByteSize=8;
            dcbSerialParams.StopBits=ONESTOPBIT;
            dcbSerialParams.Parity=NOPARITY;

             if(!SetCommState(hSerial, &dcbSerialParams))
             {
                printf("ALERT: Could not set Serial Port parameters");
             }
             else
             {
                 this->connected = true;
                 Sleep(ARDUINO_WAIT_TIME);
             }
        }
    }
}

int Serial::ReadData(char *buffer, unsigned int nbChar)
{
    DWORD bytesRead;
    unsigned int toRead;

    ClearCommError(this->hSerial, &this->errors, &this->status);

    if(this->status.cbInQue>0)
    {
        if(this->status.cbInQue>nbChar)
        {
            toRead = nbChar;
        }
        else
        {
            toRead = this->status.cbInQue;
        }

        if(ReadFile(this->hSerial, buffer, toRead, &bytesRead, NULL) && bytesRead != 0)
        {
            return bytesRead;
        }
    }

    return -1;

}


bool Serial::WriteData(char *buffer, unsigned int nbChar)
{
    this->bytesSend=0;

    if(!WriteFile(this->hSerial, (void *)buffer, nbChar, &this->bytesSend, 0))
    {
        ClearCommError(this->hSerial, &this->errors, &this->status);

        return false;
    }
    else
        return true;
}

bool Serial::IsConnected()
{
    return this->connected;
}

int Serial::Send(char* buff, int szBuff)
{
    this->WriteData(buff, szBuff);
    return this->bytesSend;
}

int Serial::Recv(char* buff, int szBuff)
{
    return this->ReadData(buff, szBuff);
}

void Serial::Close()
{
    this->connected = false;
    CloseHandle(hSerial);
}

void Serial::Clean()
{
    if(!this->connected)
        return;

    //PurgeComm(hSerial, PURGE_TXCLEAR|PURGE_RXCLEAR);
}
