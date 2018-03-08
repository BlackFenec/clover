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
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
		}
	}

public :
	virtual void Send(std::string message)
	{
		//TODO Clean up
		int recvbuflen = DEFAULT_BUFLEN;
		char recvbuf[DEFAULT_BUFLEN];

		int iResult = send(tcpSocket, message.c_str(), (int)strlen(message.c_str()), 0);
		if (iResult == SOCKET_ERROR) 
		{
			printf("send failed: %d\n", WSAGetLastError());
			closesocket(tcpSocket);
			WSACleanup();
		}

		printf("Bytes Sent: %ld\n", iResult);

		this->Shutdown();

		do {

			iResult = recv(tcpSocket, recvbuf, recvbuflen, 0);
			if (iResult > 0)
				printf("Bytes received: %d\n", iResult);
			else if (iResult == 0)
				printf("Connection closed\n");
			else
				printf("recv failed with error: %d\n", WSAGetLastError());

		} while (iResult > 0);

		this->Close();
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
		//TODO : cleanup
		char recvbuf[DEFAULT_BUFLEN];
		int recvbuflen = DEFAULT_BUFLEN;
		clientSocket = INVALID_SOCKET;

		// Accept a client socket
		clientSocket = accept(tcpSocket, NULL, NULL);
		if (clientSocket == INVALID_SOCKET) {
			printf("accept failed: %d\n", WSAGetLastError());
			closesocket(tcpSocket);
			WSACleanup();
		}

		closesocket(tcpSocket);

		int iResult;
		// Receive until the peer shuts down the connection
		do {

			iResult = recv(clientSocket, recvbuf, recvbuflen, 0);
			if (iResult > 0) {
				printf("Bytes received: %d\n", iResult);

				// Echo the buffer back to the sender
				int iSendResult = send(clientSocket, recvbuf, iResult, 0);
				if (iSendResult == SOCKET_ERROR) {
					printf("send failed with error: %d\n", WSAGetLastError());
					closesocket(clientSocket);
					WSACleanup();
					//return 1;
				}
				printf("Bytes sent: %d\n", iSendResult);
			}
			else if (iResult == 0)
				printf("Connection closing...\n");
			else {
				printf("recv failed with error: %d\n", WSAGetLastError());
				closesocket(clientSocket);
				WSACleanup();
				//return 1;
			}

		} while (iResult > 0);

		// shutdown the connection since we're done
		this->ShutdownClient();

		// cleanup
		this->CloseClient();
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
		//TODO : Cleanup
		int recvbuflen = DEFAULT_BUFLEN;
		char recvbuf[DEFAULT_BUFLEN];
		int iResult;

		do {
			iResult = recv(tcpSocket, recvbuf, recvbuflen, 0);
			if (iResult > 0)
				printf("Bytes received: %d\n", iResult);
			else if (iResult == 0)
				printf("Connection closed\n");
			else
				printf("recv failed: %d\n", WSAGetLastError());
		} while (iResult > 0);
		return recvbuf;
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