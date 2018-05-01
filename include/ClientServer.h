#ifndef CLIENTSERVER_H_
#define CLIENTSERVER_H_

#include "IClientServer.h"
#include "TcpSocket.h"
#include <mutex>

class ClientServer : public IClientServer
{
private :
	std::mutex m_UseSocket;
	std::mutex m_UseMessages;
public:

	ClientServer(std::shared_ptr<SOCKET> s)
	{
		this->m_Socket = s;
		this->m_IsClosing = false;
	};

	virtual ~ClientServer() {};

	virtual void Close()
	{
		TcpSocket::Close(this->m_Socket);
	}

	virtual bool IsClosing()
	{
		return this->m_IsClosing;
	}

	virtual void QueueMessage(std::string message)
	{
		m_UseMessages.lock();
		this->m_Messages.push(message);
		m_UseMessages.unlock();
	}

	virtual std::string ReceiveMessage()
	{
		m_UseSocket.lock();
		std::string response = TcpSocket::ReceiveFrom(this->m_Socket);
		m_UseSocket.unlock();

		return response;
	}

	virtual void SendMessages() 
	{
		m_UseMessages.lock();
		while (!this->m_Messages.empty())
		{
			m_UseSocket.lock();
			TcpSocket::SendTo(m_Messages.front(), this->m_Socket);
			m_UseSocket.unlock();
		}
		m_UseMessages.unlock();
	}

	virtual void SetClosingState(bool isClosing)
	{
		this->m_IsClosing = isClosing;
	}

	virtual void Shutdown()
	{
		TcpSocket::ShutdownSocket(this->m_Socket);
	}
};

#endif // !CLIENTSERVER_H_