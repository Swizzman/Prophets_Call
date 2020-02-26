#pragma once
#include <SFML/Network.hpp>
#include "Client.h"
#include <iostream>
class Server
{
private:
	int port;
	sf::TcpSocket tcpSocket;
	sf::TcpListener listener;
	sf::SocketSelector selector;
	bool isRunning;
	Client client;
public:
	Server();
	virtual ~Server();
	void run();
};

