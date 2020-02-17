#include "Prophet.h"

Prophet::Prophet():
	GameEntity("Prophet.png", 5, 100)
{
	convertingSpeed = 10;
	chosenGroup = 0;
	collectedSouls = 0;
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

void Prophet::die()
{
}
