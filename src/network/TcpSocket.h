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

	static void Cleanup();
	static void CloseSocket(std::shared_ptr<SOCKET> socket);
	void Create(int aiFamily, int aiFlags, const char * serverAddress, const char * serverPort);
	static std::string Receive(std::shared_ptr<SOCKET> socket);
	static void Send(std::string message, std::shared_ptr<SOCKET> socket);
	static void Shutdown(std::shared_ptr<SOCKET> socket);

public :

	virtual std::shared_ptr<SOCKET> Accept();
	virtual void Bind();
	virtual void Close();
	static void Close(std::shared_ptr<SOCKET> socket);
	virtual std::shared_ptr<SOCKET> ConnectToServer();
	virtual void CreateClient(std::string serverAddress, std::string serverPort);
	virtual void CreateServer(std::string port);
	virtual void Initialize();
	virtual void Listen();
	virtual std::string Receive();
	static std::string ReceiveFrom(std::shared_ptr<SOCKET> client);
	virtual void Send(std::string message);
	static void SendTo(std::string message, std::shared_ptr<SOCKET> client);
	virtual void Shutdown();
	static void ShutdownSocket(std::shared_ptr<SOCKET> socket);
};

#endif // !TCPSOCKET_H_