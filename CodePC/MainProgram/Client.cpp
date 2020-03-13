#include "Client.h"
#include <fstream>

Client::Client()
{
	std::ifstream iPIn;
	iPIn.open("../datafiles/ip.txt");
	iP = sf::IpAddress::LocalHost;
	iPIn >> iP;
	std::cout << iP << std::endl;
	connected = false;
	iPIn.close();
}

void Client::run()
{
	if (connectionSocket.connect(iP, 55000) != sf::Socket::Done)
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
	switch (recieved.type)
	{
	case 1:
		packet >> recieved.posX >> recieved.posY;
		break;
	case 2:
		packet >> recieved.posX >> recieved.posY >> recieved.index;
		break;
	case 4:
		packet >> recieved.index;
		break;
	case 5:
		packet >> recieved.index >> recieved.health;
		break;
	case 6:
		packet >> recieved.health;
		break;
	case 7:
		packet >> recieved.posX >> recieved.posY >> recieved.abilType;
		break;
	case 8:
		packet >> recieved.index >> recieved.column >> recieved.row;
		break;
	case 9:
		packet >> recieved.column >> recieved.row;
		break;
	case 10:
		packet >> recieved.index;
		break;
	default:
		break;
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

void Client::sendFollowerDamage(int index, int newHealth)
{
	sf::Packet packet;
	packet << (sf::Uint16) 5 << (sf::Uint16) index << (sf::Uint32) newHealth;
	connectionSocket.send(packet);
}

void Client::sendProphetDamage(int newHealth)
{
	sf::Packet packet;
	packet << (sf::Uint16) 6 << (sf::Uint32) newHealth;
	std::cout << "Prophet Damage sent!\n";
	connectionSocket.send(packet);
}

void Client::sendAbilPlace(sf::Vector2f pos, int type)
{
	sf::Packet packet;
	packet << (sf::Uint16) 7 << (sf::Uint32) pos.x << (sf::Uint32) pos.y << (sf::Uint16) type;
	connectionSocket.send(packet);
}

void Client::sendFollowerAnim(int index, int column, int row)
{
	sf::Packet packet;
	packet << (sf::Uint16) 8 << (sf::Uint16) index << (sf::Uint16) column << (sf::Uint16) row;
	connectionSocket.send(packet);
}

void Client::sendProphetAnim(int column, int row)
{
	sf::Packet packet;
	packet << (sf::Uint16) 9 << (sf::Uint16) column << (sf::Uint16) row;
	connectionSocket.send(packet);
}

void Client::sendSoulCollected(int index)
{
	sf::Packet packet;
	packet << (sf::Uint16) 10 << (sf::Uint16) index;
	connectionSocket.send(packet);
}

bool Client::getConnected() const
{
	return connected;
}
