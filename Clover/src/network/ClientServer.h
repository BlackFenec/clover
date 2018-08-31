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

	void Close();
	bool IsClosing();
	void QueueMessage(std::string message);
	std::string ReceiveMessage();
	void SendMessages();
	void SetClosingState(bool isClosing);
	void Shutdown();
};

#endif // !CLIENTSERVER_H_