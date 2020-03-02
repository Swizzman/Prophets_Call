#pragma once
#include <iostream>
#include <SFML/Network.hpp> 
struct Packet 
{
	sf::Uint16 type;
	sf::Uint32 posX;
	sf::Uint32 posY;

};
class Client
{
private:
	sf::TcpSocket connectionSocket;
	sf::Packet recievePacket;
	sf::Uint16 iD;
public:
	Client();
	virtual ~Client();
	Packet recieveAPacket();
};

