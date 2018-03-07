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
	struct addrinfo *ptr;
public :
	virtual void Send(std::string message)
	{
		int recvbuflen = DEFAULT_BUFLEN;
		char recvbuf[DEFAULT_BUFLEN];

		int iResult;

		// Send an initial buffer
		iResult = send(tcpSocket, message.c_str(), (int)strlen(message.c_str()), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed: %d\n", WSAGetLastError());
			closesocket(tcpSocket);
			WSACleanup();
			//TODO : throw
		}

		printf("Bytes Sent: %ld\n", iResult);

		iResult = shutdown(tcpSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(tcpSocket);
			WSACleanup();
			//return 1;
		}

		// Receive until the peer closes the connection
		do {

			iResult = recv(tcpSocket, recvbuf, recvbuflen, 0);
			if (iResult > 0)
				printf("Bytes received: %d\n", iResult);
			else if (iResult == 0)
				printf("Connection closed\n");
			else
				printf("recv failed with error: %d\n", WSAGetLastError());

		} while (iResult > 0);

		// cleanup
		closesocket(tcpSocket);
		WSACleanup();
	}

	virtual void Initialize()
	{
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed with error: %d\n", iResult);
			//TODO : throw exception
		}
	}

	virtual void Create(std::string serverAdress, std::string serverPort)
	{
		tcpSocket = INVALID_SOCKET;
		struct addrinfo hints;
		ptr = NULL;
		result = NULL;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		int iResult = getaddrinfo(serverAdress.c_str(), serverPort.c_str(), &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			//TODO: throw
		}
	}

	virtual void Create(std::string port)
	{
		tcpSocket = INVALID_SOCKET;

		result = NULL;
		struct addrinfo hints;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		// Resolve the server address and port
		int iResult = getaddrinfo(NULL, port.c_str(), &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			//TODO: throw
		}

		// Create a SOCKET for connecting to server
		tcpSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (tcpSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			//TODO: throw
		}
	}

	virtual void Bind()
	{
		int iResult = bind(tcpSocket, result->ai_addr, (int)result->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(result);
			closesocket(tcpSocket);
			WSACleanup();
			//TODO : throw
		}

		freeaddrinfo(result);
	}

	virtual void Listen()
	{
		int iResult = listen(tcpSocket, SOMAXCONN);
		if (iResult == SOCKET_ERROR) {
			printf("listen failed with error: %d\n", WSAGetLastError());
			closesocket(tcpSocket);
			WSACleanup();
			//TODO : throw
		}

	}

	virtual void Accept()
	{
		char recvbuf[DEFAULT_BUFLEN];
		int recvbuflen = DEFAULT_BUFLEN;
		clientSocket = INVALID_SOCKET;

		// Accept a client socket
		clientSocket = accept(tcpSocket, NULL, NULL);
		if (clientSocket == INVALID_SOCKET) {
			printf("accept failed: %d\n", WSAGetLastError());
			closesocket(tcpSocket);
			WSACleanup();
			//TODO : throw
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
		iResult = shutdown(clientSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(clientSocket);
			WSACleanup();
			//return 1;
		}

		// cleanup
		closesocket(clientSocket);
		WSACleanup();
	}

	virtual void ConnectToServer()
	{
		int iResult;
		for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

			tcpSocket = socket(ptr->ai_family, ptr->ai_socktype,
				ptr->ai_protocol);
			if (tcpSocket == INVALID_SOCKET) {
				printf("socket failed with error: %ld\n", WSAGetLastError());
				WSACleanup();
				//TODO : throw
			}

			iResult = connect(tcpSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR) {
				closesocket(tcpSocket);
				tcpSocket = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(result);

		if (tcpSocket == INVALID_SOCKET) {
			printf("Unable to connect to server!\n");
			WSACleanup();
			//TODO : throw
		}
	}

	virtual void Close()
	{
		int iResult = shutdown(tcpSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed: %d\n", WSAGetLastError());			
		}

		closesocket(tcpSocket);
		WSACleanup();
	}

	virtual void CloseClient()
	{
		int iResult = shutdown(clientSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed: %d\n", WSAGetLastError());
		}

		closesocket(clientSocket);
		WSACleanup();
	}
	
	virtual std::string Receive()
	{
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
};

#endif // !TCPSOCKET_H_