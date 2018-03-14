#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

#include <string>
#include "ITcpSocket.h"

#define DEFAULT_BUFLEN 512

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
	SOCKET tcpSocket;
	SOCKET clientSocket;
	struct addrinfo *result;

	void Create(int aiFamily, int aiFlags, const char * serverAddress, const char * serverPort)
	{
		tcpSocket = INVALID_SOCKET;
		struct addrinfo hints;
		result = NULL;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = aiFamily;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = aiFlags;

		int iResult = getaddrinfo(serverAddress, serverPort, &hints, &result);
		if (iResult != 0) 
		{
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
		}
	}

	std::string Receive(SOCKET socket)
	{
		char recvbuf[DEFAULT_BUFLEN];
		int iResult;
		std::string response = "";

		do {
			iResult = recv(socket, recvbuf, DEFAULT_BUFLEN, 0);
			if (iResult > 0)
			{
				response += std::string(recvbuf, iResult);
				printf("Bytes received: %d\n", iResult);
			}
			else if (iResult == 0)
				printf("Connection closed\n");
			else
				printf("recv failed: %d\n", WSAGetLastError());
		} while (iResult > 0);

		return response;
	}

	void Send(std::string message, SOCKET socket)
	{
		int recvbuflen = DEFAULT_BUFLEN;
		char recvbuf[DEFAULT_BUFLEN];

		int iResult = send(socket, message.c_str(), (int)strlen(message.c_str()), 0);
		if (iResult == SOCKET_ERROR)
		{
			printf("send failed: %d\n", WSAGetLastError());
			closesocket(socket);
			WSACleanup();
		}

		printf("Bytes Sent: %ld\n", iResult);
	}

public :
	virtual void Send(std::string message)
	{
		this->Send(message, tcpSocket);
	}

	virtual void SendToClient(std::string message)
	{
		this->Send(message, clientSocket);
	}

	virtual void Initialize()
	{
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) 
		{
			printf("WSAStartup failed with error: %d\n", iResult);
		}
	}

	virtual void CreateClient(std::string serverAddress, std::string serverPort)
	{
		this->Create(AF_UNSPEC,NULL,serverAddress.c_str(), serverPort.c_str());
	}

	virtual void CreateServer(std::string port)
	{
		this->Create(AF_INET, AI_PASSIVE,NULL, port.c_str());

		tcpSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (tcpSocket == INVALID_SOCKET) 
		{
			printf("socket failed with error: %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
		}
	}

	virtual void Bind()
	{
		if (SOCKET_ERROR == bind(tcpSocket, result->ai_addr, (int)result->ai_addrlen)) 
		{
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(result);
			this->Close();
		}
		freeaddrinfo(result);
	}

	virtual void Listen()
	{
		if (SOCKET_ERROR == listen(tcpSocket, SOMAXCONN))
		{
			printf("listen failed with error: %d\n", WSAGetLastError());
			this->Close();
		}

	}

	virtual void Accept()
	{
		clientSocket = INVALID_SOCKET;

		clientSocket = accept(tcpSocket, NULL, NULL);
		if (clientSocket == INVALID_SOCKET) {
			printf("accept failed: %d\n", WSAGetLastError());
			closesocket(tcpSocket);
			WSACleanup();
		}

		closesocket(tcpSocket);
	}

	virtual void ConnectToServer()
	{
		for (struct addrinfo * ptr = result; ptr != NULL; ptr = ptr->ai_next) 
		{
			tcpSocket = socket(ptr->ai_family, ptr->ai_socktype,ptr->ai_protocol);
			if (tcpSocket == INVALID_SOCKET) 
			{
				printf("socket failed with error: %ld\n", WSAGetLastError());
				WSACleanup();
			}

			if (SOCKET_ERROR == connect(tcpSocket, ptr->ai_addr, (int)ptr->ai_addrlen)) 
			{
				closesocket(tcpSocket);
				tcpSocket = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(result);

		if (tcpSocket == INVALID_SOCKET) 
		{
			printf("Unable to connect to server!\n");
			WSACleanup();
		}
	}

	virtual void Close()
	{
		closesocket(tcpSocket);
		WSACleanup();
	}

	virtual void CloseClient()
	{
		closesocket(clientSocket);
		WSACleanup();
	}
	
	virtual std::string Receive()
	{
		return this->Receive(tcpSocket);
	}

	virtual std::string ReceiveFromClient()
	{
		return this->Receive(clientSocket);
	}

	virtual void ShutdownClient()
	{
		if (SOCKET_ERROR == shutdown(clientSocket, SD_SEND))
		{
			printf("shutdown failed: %d\n", WSAGetLastError());
		}
	}

	virtual void Shutdown()
	{
		if (SOCKET_ERROR == shutdown(tcpSocket, SD_SEND)) 
		{
			printf("shutdown failed: %d\n", WSAGetLastError());
		}
	}
};

#endif // !TCPSOCKET_H_