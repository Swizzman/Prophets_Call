#include "Server.h"
#include "Client.h"

Server::Server()
{
	port = 55000;
	listener.listen(port, sf::IpAddress::LocalHost);
	std::cout << "Server started on: " << sf::IpAddress::LocalHost << ":" << port << std::endl;
	isRunning = true;
	clientConnected = false;
	selector.add(listener);
	std::cout << "Listening...\n";
	client = nullptr;
	clientSock = std::make_unique<sf::TcpSocket>();
}

Server::~Server()
{
}

void Server::run()
{


	std::cout << "isRunning\n";
	if (selector.wait())
	{
		std::cout << "wait\n";

		if (selector.isReady(listener))
		{
			std::cout << "isReady\n";
			if (listener.accept(*clientSock) == sf::Socket::Done)
			{
				std::cout << "Client connected\n";

				clientConnected = true;

			}
		}
	}



}

bool Server::getClientConnected() const
{
	return clientConnected;
}

void Server::sendProphetPos(sf::Vector2f pos)
{
	sf::Packet packet;
	packet << (sf::Uint16) 1 << (sf::Uint32) pos.x << (sf::Uint32) pos.y;
	clientSock->send(packet);
}

void Server::sendFollowerPos(sf::Vector2f pos, int index)
{
	sf::Packet packet;
	packet << (sf::Uint16) 2 << (sf::Uint32) pos.x << (sf::Uint32) pos.y << (sf::Uint16) index;
	clientSock->send(packet);
}

void Server::sendConverted(int index)
{
	sf::Packet packet;
	packet << (sf::Uint16) 4 << (sf::Uint16) index;
	clientSock->send(packet);
}

Packet Server::recieveAPacket()
{


	sf::Packet packet;
	Packet recieved;
	sf::Uint16 x, y;
	clientSock->receive(packet);
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
