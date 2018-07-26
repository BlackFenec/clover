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

	ClientServer(std::shared_ptr<SOCKET> s);
	virtual ~ClientServer();
	virtual void Close();
	virtual bool IsClosing();
	virtual void QueueMessage(std::string message);
	virtual std::string ReceiveMessage();
	virtual void SendMessages();
	virtual void SetClosingState(bool isClosing);
	virtual void Shutdown();
};

#endif // !CLIENTSERVER_H_