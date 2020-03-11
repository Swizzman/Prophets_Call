#pragma once
#include <SFML/Network.hpp>
#include "Client.h"
#include <iostream>
class Server
{
private:
	int port;
	sf::IpAddress iP;
	sf::TcpSocket tcpSocket;
	sf::TcpListener listener;
	sf::SocketSelector selector;
	bool clientConnected;
	std::unique_ptr<sf::TcpSocket> clientSock;
public:
	Server();
	virtual ~Server();
	void run();
	bool getClientConnected() const;
	void sendProphetPos(sf::Vector2f pos);
	void sendFollowerPos(sf::Vector2f pos, int index);
	void sendConverted(int index);
	void sendFollowerDamage(int index, int newHealth);
	void sendProphetDamage(int newHealth);
	void sendAbilPlace(sf::Vector2f pos, int type);
	void sendFollowerAnim(int index, int column, int row);
	Packet recieveAPacket();
};

