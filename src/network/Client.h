#ifndef CLIENT_H_
#define CLIENT_H_

#include "ClientServer.h"
#include "IClient.h"
#include <fstream>
#include <memory>
#include <thread>

class Client : public IClient
{
private:

	std::shared_ptr<std::ostream> m_Output;
	const std::string k_ServerAddress = "localhost";
	const std::string k_ServerReceivingPort = "27015";
	const std::string k_ServerSendPort = "27016";
	std::thread * m_SocketProcessing;

	void SetUpClient();

public:

	Client(std::shared_ptr<ITcpSocket> s, std::shared_ptr<std::ostream> output);
	virtual ~Client();

	virtual std::shared_ptr<IClientServer> GetClientServer();
	virtual void ProcessClient(std::shared_ptr<IClientServer> client);
	virtual void Send(std::string message);
	virtual void SetClientServer(std::shared_ptr<IClientServer> client);
	virtual void Start();
};

#endif