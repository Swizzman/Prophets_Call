#include "Client.h"

Client::Client()
{
	iP = ("25.74.9.3");
	connected = false;
}

void Client::run()
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
		packet >> recieved.index;
	}
	else if (recieved.type == 5)
	{
		packet >> recieved.index >> recieved.health;
	}
	else if (recieved.type == 6)
	{
		packet >> recieved.health;
	}
	return recieved;
}

void Client::sendProphetPos(sf::Vector2f pos)
{
	sf::Packet packet;
	packet << (sf::Uint16) 1 << (sf::Uint32) pos.x << (sf::Uint32) pos.y;
	connectionSocket.send(packet);

}

void Client::sendFollowerPos(sf::Vector2f pos, int index)
{
	sf::Packet packet;
	packet << (sf::Uint16) 2 << (sf::Uint32) pos.x << (sf::Uint32) pos.y << (sf::Uint16) index;
	connectionSocket.send(packet);
}

void Client::sendConverted(int index)
{
	sf::Packet packet;
	packet << (sf::Uint16) 4 << (sf::Uint16) index;
	connectionSocket.send(packet);
}

bool Client::getConnected() const
{
	return connected;
}
