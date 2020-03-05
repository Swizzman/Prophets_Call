#include "Client.h"

Client::Client()
{
	if (connectionSocket.connect(sf::IpAddress::LocalHost, 55000) != sf::Socket::Done)
	{
		std::cout << "Error connecting \n";
	}
	else
	{
		std::cout << "Connected to Server\n";
		connected = true;
		
	}
}

Client::~Client()
{
}

Packet Client::recieveAPacket()
{
	sf::Packet packet;
	Packet recieved;
	sf::Uint16 x, y;
	connectionSocket.receive(packet);
	packet >> recieved.type;
	if (recieved.type == 1)
	{
		packet >> recieved.posX >> recieved.posY;
	}
	else if (recieved.type == 2)
	{
		packet >> recieved.posX >> recieved.posY >> recieved.index;
	}
	else if (recieved.type == 4)
	{
		std::cout << "It's a conversion!\n";
		packet >> recieved.index;
	}
	return recieved;
}

void Client::sendProphetPos(sf::Vector2f pos)
{
	sf::Packet packet;
	packet << (sf::Uint16) 1 << (sf::Uint32) pos.x << (sf::Uint32) pos.y;
	connectionSocket.send(packet);

}

bool Client::getConnected() const
{
	return connected;
}
