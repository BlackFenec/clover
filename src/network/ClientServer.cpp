#include "ClientServer.h"

ClientServer::ClientServer(std::shared_ptr<SOCKET> s)
{
	this->m_Socket = s;
	this->m_IsClosing = false;
};

ClientServer::~ClientServer() 
{

}

void ClientServer::Close()
{
	TcpSocket::Close(this->m_Socket);
}

bool ClientServer::IsClosing()
{
	return this->m_IsClosing;
}

void ClientServer::QueueMessage(std::string message)
{
	m_UseMessages.lock();
	this->m_Messages.push(message);
	m_UseMessages.unlock();
}

std::string ClientServer::ReceiveMessage()
{
	m_UseSocket.lock();
	std::string response = TcpSocket::ReceiveFrom(this->m_Socket);
	m_UseSocket.unlock();

	return response;
}

void ClientServer::SendMessages()
{
	m_UseMessages.lock();
	while (!this->m_Messages.empty())
	{
		m_UseSocket.lock();
		TcpSocket::SendTo(m_Messages.front(), this->m_Socket);
		m_UseSocket.unlock();
		m_Messages.pop();
	}
	m_UseMessages.unlock();
}

void ClientServer::SetClosingState(bool isClosing)
{
	this->m_IsClosing = isClosing;
}

void ClientServer::Shutdown()
{
	TcpSocket::ShutdownSocket(this->m_Socket);
}