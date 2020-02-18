#include "Prophet.h"

Prophet::Prophet() :
	GameEntity("Prophet.png", 5, 5, 100)
{
	convertingSpeed = 10;
	chosenGroup = 0;
	collectedSouls = 200;
	setPosition(100, 100);
}

Prophet::~Prophet()
{
}

void Prophet::convert()
{
}

bool Prophet::checkMovement()
{

	
	return false;
}

void Prophet::moveProphet()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		moveVertical = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		moveVertical = 1;
	}
	else
	{
		moveVertical = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moveHorizontal = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moveHorizontal = -1;
	}
	else
	{
		moveHorizontal = 0;
	}
	setMovingSpeed(moveHorizontal, moveVertical);
		move();
}

int Prophet::getNrOfFollowers()
{
	return group1.nrOfFollowers;
}

void Prophet::addFollower()
{
}

void Prophet::collectSouls()
{
}

int Prophet::getSouls()
{
	return collectedSouls;
}

Follower* Prophet::getFollowers()
{
	return *group1.followers;
}

void Prophet::recieveEnemyProphet(Prophet* other)
{
	otherProphet = other;
}

int Prophet::getCurrentAbility()
{


	return chosenAbility;
}

void Prophet::changeAbility()
{
	chosenAbility++;
	if (chosenAbility >= 3 )
	{
		chosenAbility = 0;
	}
	std::cout << chosenAbility << std::endl;
}

void Prophet::die()
{
}
