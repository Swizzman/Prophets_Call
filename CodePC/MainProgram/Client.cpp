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
		connectionSocket.setBlocking(false);
		std::cout << "Connected to Server";
		
	}
}

Client::~Client()
{
}
