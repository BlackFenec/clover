#include "TcpSocket.h"

std::shared_ptr<SOCKET> TcpSocket::Accept()
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

void TcpSocket::Bind()
{
	if (SOCKET_ERROR == bind(*m_TcpSocket, m_Result->ai_addr, (int)m_Result->ai_addrlen))
	{
		freeaddrinfo(m_Result);
		this->Close();
	}
	freeaddrinfo(m_Result);
}

void TcpSocket::Cleanup()
{
#ifdef _WIN32
	WSACleanup();
#endif
}

void TcpSocket::Close()
{
	CloseSocket(m_TcpSocket);
	Cleanup();
}

void TcpSocket::Close(std::shared_ptr<SOCKET> socket)
{
	CloseSocket(socket);
	Cleanup();
}

void TcpSocket::CloseSocket(std::shared_ptr<SOCKET> socket)
{
#ifdef _WIN32
	closesocket(*socket);
#else
	close(*socket);
#endif
}

void TcpSocket::Create(int aiFamily, int aiFlags, const char * serverAddress, const char * serverPort)
{
	m_TcpSocket = std::make_shared<SOCKET>();
	*m_TcpSocket = INVALID_SOCKET;
	struct addrinfo hints;
	m_Result = NULL;

#ifdef _WIN32
	ZeroMemory(&hints, sizeof(hints));
#else
	memset(&hints, 0, sizeof(hints));
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

std::string TcpSocket::Receive(std::shared_ptr<SOCKET> socket)
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
	} while (result > 0 && result == k_DefaultBufferLength);

	return response;
}

void TcpSocket::Send(std::string message, std::shared_ptr<SOCKET> socket)
{
	char * receivedBuffer = new char[k_DefaultBufferLength];
	int result = send(*socket, message.c_str(), (int)strlen(message.c_str()), 0);
	if (result == SOCKET_ERROR)
	{
		CloseSocket(socket);
		Cleanup();
	}
}

void TcpSocket::Shutdown(std::shared_ptr<SOCKET> socket)
{
#ifdef _WIN32
	shutdown(*socket, SD_BOTH);
#else
	shutdown(*socket, SHUT_RDWR);
#endif
}

std::shared_ptr<SOCKET> TcpSocket::ConnectToServer()
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

void TcpSocket::CreateClient(std::string serverAddress, std::string serverPort)
{
	this->Create(AF_UNSPEC, NULL, serverAddress.c_str(), serverPort.c_str());
}

void TcpSocket::CreateServer(std::string port)
{
	this->Create(AF_INET, AI_PASSIVE, NULL, port.c_str());

	*m_TcpSocket = socket(m_Result->ai_family, m_Result->ai_socktype, m_Result->ai_protocol);
	if (*m_TcpSocket == INVALID_SOCKET)
	{
		freeaddrinfo(m_Result);
		Cleanup();
	}

}

void TcpSocket::Initialize()
{
#ifdef _WIN32
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
}

void TcpSocket::Listen()
{
	if (SOCKET_ERROR == listen(*m_TcpSocket, SOMAXCONN))
	{
		this->Close();
	}
}

std::string TcpSocket::Receive()
{
	return this->Receive(m_TcpSocket);
}

std::string TcpSocket::ReceiveFrom(std::shared_ptr<SOCKET> client)
{
	return Receive(client);
}

void TcpSocket::Send(std::string message)
{
	this->Send(message, m_TcpSocket);
}

void TcpSocket::SendTo(std::string message, std::shared_ptr<SOCKET> client)
{
	Send(message, client);
}

void TcpSocket::Shutdown()
{
	Shutdown(m_TcpSocket);
}

void TcpSocket::ShutdownSocket(std::shared_ptr<SOCKET> socket)
{
	Shutdown(socket);
}