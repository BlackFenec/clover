#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

#include "ITcpSocket.h"
#include <string>

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")

class TcpSocket : public ITcpSocket
{
private:

	const int k_DefaultBufferLength = 512;
	std::shared_ptr<SOCKET> m_TcpSocket;
	struct addrinfo* m_Result;

	void Create(int aiFamily, int aiFlags, const char * serverAddress, const char * serverPort)
	{
		m_TcpSocket = std::make_shared<SOCKET>();
		*m_TcpSocket = INVALID_SOCKET;
		struct addrinfo hints;
		m_Result = NULL;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = aiFamily;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = aiFlags;

		int result = getaddrinfo(serverAddress, serverPort, &hints, &m_Result);
		if (result != 0)
		{
			printf("getaddrinfo failed with error: %d\n", result);
			WSACleanup();
		}
	}

	std::string Receive(std::shared_ptr<SOCKET> socket)
	{
		char * receivedBuffer = new char[k_DefaultBufferLength];
		int result;
		std::string response = "";

		do {
			result = recv(*socket, receivedBuffer, k_DefaultBufferLength, 0);
			if (result > 0)
			{
				response += std::string(receivedBuffer, result);
				printf("Bytes received: %d\n", result);
			}
			else if (result == 0)
				printf("Connection closed\n");
			/*else
				printf("recv failed: %d\n", WSAGetLastError());*/
		} while (result > 0);

		return response;
	}

	void Send(std::string message, std::shared_ptr<SOCKET> socket)
	{
		char * receivedBuffer = new char[k_DefaultBufferLength];

		int result = send(*socket, message.c_str(), (int)strlen(message.c_str()), 0);
		if (result == SOCKET_ERROR)
		{
			//printf("send failed: %d\n", WSAGetLastError());
			closesocket(*socket);
			WSACleanup();
		}

		//printf("Bytes Sent: %ld\n", result);
	}

public :

	virtual std::shared_ptr<SOCKET> Accept()
	{
		std::shared_ptr<SOCKET> m_ClientSocket(new SOCKET());
		*m_ClientSocket = INVALID_SOCKET;

		while(*m_ClientSocket == INVALID_SOCKET) *m_ClientSocket = accept(*m_TcpSocket, NULL, NULL);
		
		return m_ClientSocket;
	}

	virtual void Bind()
	{
		if (SOCKET_ERROR == bind(*m_TcpSocket, m_Result->ai_addr, (int)m_Result->ai_addrlen))
		{
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(m_Result);
			this->Close();
		}
		freeaddrinfo(m_Result);
	}

	virtual void Close()
	{
		closesocket(*m_TcpSocket);
		WSACleanup();
	}

	virtual void CloseClient(std::shared_ptr<SOCKET> client)
	{
		closesocket(*client);
		WSACleanup();
	}

	virtual void ConnectToServer()
	{
		for (struct addrinfo * ptr = m_Result; ptr != NULL; ptr = ptr->ai_next)
		{
			*m_TcpSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
			if (*m_TcpSocket == INVALID_SOCKET)
			{
				printf("socket failed with error: %ld\n", WSAGetLastError());
				WSACleanup();
			}

			if (SOCKET_ERROR == connect(*m_TcpSocket, ptr->ai_addr, (int)ptr->ai_addrlen))
			{
				closesocket(*m_TcpSocket);
				*m_TcpSocket = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(m_Result);

		if (*m_TcpSocket == INVALID_SOCKET)
		{
			printf("Unable to connect to server!\n");
			WSACleanup();
		}
	}

	virtual void CreateClient(std::string serverAddress, std::string serverPort)
	{
		this->Create(AF_UNSPEC, NULL, serverAddress.c_str(), serverPort.c_str());
	}

	virtual void CreateServer(std::string port)
	{
		this->Create(AF_INET, AI_PASSIVE, NULL, port.c_str());

		*m_TcpSocket = socket(m_Result->ai_family, m_Result->ai_socktype, m_Result->ai_protocol);
		if (*m_TcpSocket == INVALID_SOCKET)
		{
			printf("socket failed with error: %ld\n", WSAGetLastError());
			freeaddrinfo(m_Result);
			WSACleanup();
		}
			
	}

	virtual void Initialize()
	{
		WSADATA wsaData;
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0)
		{
			printf("WSAStartup failed with error: %d\n", iResult);
		}
	}

	virtual void Listen()
	{
		if (SOCKET_ERROR == listen(*m_TcpSocket, SOMAXCONN))
		{
			printf("listen failed with error: %d\n", WSAGetLastError());
			this->Close();
		}
	}
	
	virtual std::string Receive()
	{
		return this->Receive(m_TcpSocket);
	}

	virtual std::string ReceiveFromClient(std::shared_ptr<SOCKET> client)
	{
		return this->Receive(client);
	}

	virtual void Send(std::string message)
	{
		this->Send(message, m_TcpSocket);
	}

	virtual void SendToClient(std::string message, std::shared_ptr<SOCKET> client)
	{
		this->Send(message, client);
	}

	virtual void Shutdown()
	{
		if (SOCKET_ERROR == shutdown(*m_TcpSocket, SD_SEND))
		{
			printf("shutdown failed: %d\n", WSAGetLastError());
		}
	}

	virtual void ShutdownClient(std::shared_ptr<SOCKET> client)
	{
		if (SOCKET_ERROR == shutdown(*client, SD_SEND))
		{
			printf("shutdown failed: %d\n", WSAGetLastError());
		}
	}
};

#endif // !TCPSOCKET_H_