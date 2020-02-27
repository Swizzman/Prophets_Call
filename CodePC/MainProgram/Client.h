#pragma once
#include <iostream>
#include <SFML/Network.hpp> 
class Client
{
private:
	sf::TcpSocket connectionSocket;
	sf::Packet recievePacket;
	int iD;
public:
	Client();
	virtual ~Client();
};

