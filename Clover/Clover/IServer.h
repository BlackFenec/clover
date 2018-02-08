#ifndef ISERVER_H_
#define ISERVER_H_

class IServer {

public:

	virtual ~IServer() {}
	virtual void Start() = 0;

};

#endif // !ISERVER_H_