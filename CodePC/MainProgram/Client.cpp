#include "Client.h"

Client::Client()
{
	iD = 0;
	if (connectionSocket.connect(sf::IpAddress::LocalHost, 55000) != sf::Socket::Done)
	{
		std::cout << "Error connecting \n";
	}
	else
	{
		std::cout << "Connected to Server\n";
		connectionSocket.receive(this->recievePacket);
		this->recievePacket >> iD;
		std::cout << iD << std::endl;
		
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
	return recieved;
}
