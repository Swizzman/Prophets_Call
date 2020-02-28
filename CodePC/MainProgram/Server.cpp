#include "Server.h"

Server::Server()
{
	port = 55000;
	listener.listen(port, sf::IpAddress::LocalHost);
	std::cout << "Server started on: " << sf::IpAddress::LocalHost << ":"<<port<< std::endl;
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

void Server::sendPos(sf::Vector2f pos)
{

	sf::Packet packet;
	packet << (sf::Uint16)pos.x << (sf::Uint16)pos.y;
	std::cout << clientSock->send(packet) << std::endl;
}
