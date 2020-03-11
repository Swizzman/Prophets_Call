#pragma once
#include <iostream>
#include <SFML/Network.hpp> 
struct Packet
 
{
	sf::Uint16 type;
	sf::Uint32 posX;
	sf::Uint32 posY;
	sf::Uint16 index;
	sf::Uint32 health;
	sf::Uint16 abilType;
};
class Client
{
private:
	sf::TcpSocket connectionSocket;
	sf::Packet recievePacket;
	bool connected;
	sf::IpAddress iP;
public:
	Client();
	void run();
	virtual ~Client();
	Packet recieveAPacket();
	void sendProphetPos(sf::Vector2f pos);
	void sendFollowerPos(sf::Vector2f pos, int index);
	void sendConverted(int index);
	void sendFollowerDamage(int index, int newHealth);
	void sendProphetDamage(int newHealth);
	void sendAbilPlace(sf::Vector2f pos, int type);

	bool getConnected() const;
};

