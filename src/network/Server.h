#ifndef SERVER_H_
#define SERVER_H_

#include "IServer.h"
#include "ClientServer.h"
#include "Server.h"
#include <map>
#include <queue>
#include <thread>

class Server : public IServer
{
private:
	const std::string k_ServerReceivingPort = "27015";
	const std::string k_ServerSendPort = "27016";
	std::map<std::shared_ptr<IClientServer>, std::thread*> m_SendingClients;
	std::map<std::shared_ptr<IClientServer>, std::thread*> m_ReceivingClients;

public :
	
	Server(std::shared_ptr<ITcpSocket> receivingSocket, std::shared_ptr<ITcpSocket> sendingSocket);
	Server(std::shared_ptr<ITcpSocket> receivingSocket, std::shared_ptr<ITcpSocket> sendingSocket, bool isClosing);
	virtual ~Server();
	virtual void Close();
	virtual void ListenReceivingSockets();
	virtual void ListenSendingSockets();
	virtual void ProcessReceivingClient(std::shared_ptr<IClientServer> client);
	virtual void ProcessSendingClient(std::shared_ptr<IClientServer> client);
	virtual void Run();
};

#endif // !SERVER_H_