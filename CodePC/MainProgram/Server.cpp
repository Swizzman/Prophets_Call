#include "Server.h"
#include "Client.h"

Server::Server()
{
	iP = sf::IpAddress::LocalHost;
	iP = ("25.74.9.3");
	port = 55000;
	listener.listen(port, iP);
	std::cout << "Server started on: " << iP << ":" << port << std::endl;
	clientConnected = false;
	selector.add(listener);
	std::cout << "Listening...\n";
	clientSock = std::make_unique<sf::TcpSocket>();
}

Server::~Server()
{
}

void Server::disconnect()
{
	if (clientConnected)
	{
		clientSock->disconnect();
		tcpSocket.disconnect();
		clientConnected = false;
	}
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

void Server::sendFollowerDamage(int index, int newHealth)
{
	sf::Packet packet;
	std::cout << "Follower Damage sent!\n";
	packet << (sf::Uint16) 5 << (sf::Uint16) index << (sf::Uint32) newHealth;
	clientSock->send(packet);
}

void Server::sendProphetDamage(int newHealth)
{
	sf::Packet packet;
	packet << (sf::Uint16) 6 << (sf::Uint32) newHealth;
	clientSock->send(packet);
}

void Server::sendAbilPlace(sf::Vector2f pos, int type)
{
	sf::Packet packet;
	packet << (sf::Uint16) 7 << (sf::Uint32) pos.x << (sf::Uint32) pos.y << (sf::Uint16) type;
	clientSock->send(packet);
}

void Server::sendFollowerAnim(int index, int column, int row)
{
	sf::Packet packet;
	packet << (sf::Uint16) 8 << (sf::Uint16) index << (sf::Uint16) column << (sf::Uint16) row;
	clientSock->send(packet);


}

void Server::sendProphetAnim(int column, int row)
{
	sf::Packet packet;
	packet << (sf::Uint16) 9 << (sf::Uint16) column << (sf::Uint16) row;
	clientSock->send(packet);
}

void Server::sendSoulCollected(int index)
{
	sf::Packet packet;
	packet << (sf::Uint16) 10 << (sf::Uint16) index;
	clientSock->send(packet);
}

Packet Server::recieveAPacket()
{


	sf::Packet packet;
	Packet recieved;
	sf::Uint16 x, y;
	if (clientSock->receive(packet) == sf::Socket::Disconnected)
	{
		clientConnected = false;
	}



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
