#include "Client.h"

Client::Client()
{
	iD = 0;
	iP = ("25.74.9.3");
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
	else if (recieved.type == 4)
	{
		packet >> recieved.index;
	}
	return recieved;
}
