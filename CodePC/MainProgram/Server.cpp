#include "Server.h"

Server::Server()
{
	port = 2000;
	listener.listen(port);
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
		if (selector.wait())
		{
			if (selector.isReady(listener))
			{

			}
		}
	}
}
