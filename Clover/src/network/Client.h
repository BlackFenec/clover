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

	std::thread * m_SocketProcessing;
	std::shared_ptr<std::ostream> m_Output;
	const std::string k_ServerAddress = "localhost";
	const std::string k_ServerReceivingPort = "27015";
	const std::string k_ServerSendPort = "27016";

	void SetUpClient();

public:

	Client(std::shared_ptr<ITcpSocket> s, std::shared_ptr<std::ostream> output);
	virtual ~Client();

	std::shared_ptr<IClientServer> GetClientServer();
	void ProcessClient(std::shared_ptr<IClientServer> client);
	void Send(std::string message);
	void SetClientServer(std::shared_ptr<IClientServer> client);
	void Start();
};

#endif