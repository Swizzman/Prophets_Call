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
}

Server::~Server()
{
}

void Server::run()
{
	while (isRunning)
	{


		std::cout << "isRunning\n";
		if (selector.wait())
		{
			std::cout << "wait\n";

			if (selector.isReady(listener))
			{
				std::cout << "isReady\n";
				std::unique_ptr<sf::TcpSocket> tempSocket = std::make_unique<sf::TcpSocket>();
				if (listener.accept(*tempSocket) == sf::Socket::Done)
				{
					std::cout << "Client connected\n";
				}


			}
		}

	}

}
