#include "Prophet.h"

Prophet::Prophet()
{
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
