#pragma once
#include <iostream>
#include <SFML/Network.hpp> 
struct Packet 
{
	sf::Uint16 type;
	sf::Uint32 posX;
	sf::Uint32 posY;
	sf::Uint16 index;

};
class Client
{
private:
	sf::TcpSocket connectionSocket;
	sf::Packet recievePacket;
	sf::Uint16 iD;
	sf::IpAddress iP;
public:
	Client();
	void run();
	virtual ~Client();
	Packet recieveAPacket();
};

