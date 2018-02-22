#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

#include <string>
#include "ITcpSocket.h"

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

class TcpSocket : public ITcpSocket{
private:
	WSADATA wsaData;
public :
	virtual void SendMessage(std::string message)
	{

	}

	virtual void Initialize()
	{
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			//TODO : throw exception
		}
	}
};

#endif // !TCPSOCKET_H_