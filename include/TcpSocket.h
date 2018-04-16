#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

#include "ITcpSocket.h"

#ifdef _WIN32
	#undef UNICODE
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <string>
	#pragma comment (lib, "Ws2_32.lib")
#else
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <unistd.h>
	#include <cstring>
	const int INVALID_SOCKET = -1;
	const int SOCKET_ERROR = -1;
#endif
#include <stdlib.h>
#include <stdio.h>
#include <thread>


class TcpSocket : public ITcpSocket
{
private:

	static const int k_DefaultBufferLength = 512;
	std::shared_ptr<SOCKET> m_TcpSocket;
	struct addrinfo* m_Result;

	static void Cleanup()
	{
		#ifdef _WIN32
			WSACleanup();
		#endif
	}

	static void CloseSocket(std::shared_ptr<SOCKET> socket)
	{
		#ifdef _WIN32
			closesocket(*socket);
		#else
			close(*socket);
		#endif
	}

	void Create(int aiFamily, int aiFlags, const char * serverAddress, const char * serverPort)
	{
		m_TcpSocket = std::make_shared<SOCKET>();
		*m_TcpSocket = INVALID_SOCKET;
		struct addrinfo hints;
		m_Result = NULL;

		#ifdef _WIN32
			ZeroMemory(&hints, sizeof(hints));
		#else
			memset(&hints,0,sizeof(hints));
		#endif
		hints.ai_family = aiFamily;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = aiFlags;

		int result = getaddrinfo(serverAddress, serverPort, &hints, &m_Result);
		if (result != 0)
		{
			Cleanup();
		}
	}

	static std::string Receive(std::shared_ptr<SOCKET> socket)
	{
		char * receivedBuffer = new char[k_DefaultBufferLength];
		int result;
		std::string response = "";

		do {
			result = recv(*socket, receivedBuffer, k_DefaultBufferLength, 0);
			if (result > 0)
			{
				response += std::string(receivedBuffer, result);
			}
		} while (result > 0);

		return response;
	}

	static void Send(std::string message, std::shared_ptr<SOCKET> socket)
	{
		char * receivedBuffer = new char[k_DefaultBufferLength];

		int result = send(*socket, message.c_str(), (int)strlen(message.c_str()), 0);
		if (result == SOCKET_ERROR)
		{
			CloseSocket(socket);
			Cleanup();
		}
	}

	static void Shutdown(std::shared_ptr<SOCKET> socket)
	{
		#ifdef _WIN32
			shutdown(*socket, SD_BOTH);
		#else
			shutdown(*socket, SHUT_RDWR);
		#endif
	}

public :

	virtual std::shared_ptr<SOCKET> Accept()
	{
		std::shared_ptr<SOCKET> m_ClientSocket(new SOCKET());
		*m_ClientSocket = INVALID_SOCKET;

		while (*m_ClientSocket == INVALID_SOCKET) 
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			*m_ClientSocket = accept(*m_TcpSocket, NULL, NULL);
		}
		
		return m_ClientSocket;
	}

	virtual void Bind()
	{
		if (SOCKET_ERROR == bind(*m_TcpSocket, m_Result->ai_addr, (int)m_Result->ai_addrlen))
		{
			freeaddrinfo(m_Result);
			this->Close();
		}
		freeaddrinfo(m_Result);
	}

	virtual void Close()
	{
		CloseSocket(m_TcpSocket);
		Cleanup();
	}

	static void Close(std::shared_ptr<SOCKET> socket)
	{
		CloseSocket(socket);
		Cleanup();
	}

	virtual std::shared_ptr<SOCKET> ConnectToServer()
	{
		for (struct addrinfo * ptr = m_Result; ptr != NULL; ptr = ptr->ai_next)
		{
			*m_TcpSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
			if (*m_TcpSocket == INVALID_SOCKET)
			{
				Cleanup();
			}

			if (SOCKET_ERROR == connect(*m_TcpSocket, ptr->ai_addr, (int)ptr->ai_addrlen))
			{
				CloseSocket(m_TcpSocket);
				*m_TcpSocket = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(m_Result);

		if (*m_TcpSocket == INVALID_SOCKET)
		{
			Cleanup();
		}
		return m_TcpSocket;
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
			freeaddrinfo(m_Result);
			Cleanup();
		}
			
	}

	virtual void Initialize()
	{
		#ifdef _WIN32
			WSADATA wsaData;
			WSAStartup(MAKEWORD(2, 2), &wsaData);
		#endif
	}

	virtual void Listen()
	{
		if (SOCKET_ERROR == listen(*m_TcpSocket, SOMAXCONN))
		{
			this->Close();
		}
	}
	
	virtual std::string Receive()
	{
		return this->Receive(m_TcpSocket);
	}

	static std::string ReceiveFrom(std::shared_ptr<SOCKET> client)
	{
		return Receive(client);
	}

	virtual void Send(std::string message)
	{
		this->Send(message, m_TcpSocket);
	}

	static void SendTo(std::string message, std::shared_ptr<SOCKET> client)
	{
		Send(message, client);
	}

	virtual void Shutdown()
	{
		Shutdown(m_TcpSocket);
	}

	static void ShutdownSocket(std::shared_ptr<SOCKET> socket)
	{
		Shutdown(socket);
	}
};

#endif // !TCPSOCKET_H_