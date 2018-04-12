#ifndef ICLIENTSERVER_H_
#define ICLIENTSERVER_H_

#include "ITcpSocket.h"
#include <memory>
#include <queue>

class IClientServer
{
protected:
	bool m_IsClosing;
	std::queue<std::string> m_Messages;
	std::shared_ptr<SOCKET> m_Socket;

public:
	IClientServer() {};
	virtual ~IClientServer() {};

	virtual void Close() = 0;
	virtual bool IsClosing() = 0;
	virtual void QueueMessage(std::string message) = 0;
	virtual std::string ReceiveMessage() = 0;
	virtual void SendMessages() = 0;
	virtual void SetClosingState(bool isClosing) = 0;
	virtual void Shutdown() = 0;
};

#endif //!ICLIENTSERVER_H_