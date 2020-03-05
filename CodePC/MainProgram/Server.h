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
	bool clientConnected;
	Client* client;
	std::unique_ptr<sf::TcpSocket> clientSock;
public:
	Server();
	virtual ~Server();
	void run();
	bool getClientConnected() const;
	void sendProphetPos(sf::Vector2f pos);
	void sendFollowerPos(sf::Vector2f pos, int index);
	void sendConverted(int index);
};

