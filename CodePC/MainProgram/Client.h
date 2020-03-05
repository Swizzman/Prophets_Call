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
	bool connected;

public:
	Client();
	virtual ~Client();
	Packet recieveAPacket();
	void sendProphetPos(sf::Vector2f pos);
	bool getConnected() const;
};

