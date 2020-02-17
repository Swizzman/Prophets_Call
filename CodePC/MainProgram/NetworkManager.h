#pragma once
#include <SFML/Network.hpp>
class NetworkManager
{

private:
	int port;
	sf::UdpSocket socket;

public:
	NetworkManager();
	~NetworkManager();
	void socket();
	void bindSocket();

};

