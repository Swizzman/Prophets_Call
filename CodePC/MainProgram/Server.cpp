#include "Server.h"
#include "Client.h"

Server::Server()
{
	port = 55000;
	iP = ("25.74.9.3");
	listener.listen(port, iP);
	std::cout << "Server started on: " << iP << ":"<<port<< std::endl;
	isRunning = true;
	clientConnected = false;
	selector.add(listener);
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
					sf::Packet tempPacket;
					tempPacket << sf::Uint16(55);
					clientSock->send(tempPacket);
					std::cout << "Sent info\n";
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
	std::cout << "Sent this prophets Position\n";
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
	tcpSocket.send(packet);
}
