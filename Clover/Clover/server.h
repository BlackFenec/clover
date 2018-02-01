#ifndef SERVER_H_
#define SERVER_H_



class Server {

public:

	virtual  ~Server() {};
	virtual bool Start() = 0;

};

#endif // !SERVER_H_