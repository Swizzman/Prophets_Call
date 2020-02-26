#include "Server.h"

Server::Server()
{
	port = 55000;
	listener.listen(port);
	std::cout << sf::IpAddress::getLocalAddress();
	isRunning = true;
	selector.add(listener);
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

			}
		}

	}

}
