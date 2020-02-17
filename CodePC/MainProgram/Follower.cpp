#include "Follower.h"

void Follower::die()
{
}

Follower::Follower() : GameEntity("Civilian.png", 5, 60)
{
	damage = 20;
	soulValue = 40;
	attackRange = 5.f;
	alive = true;
}

Follower::~Follower()
{
}

void Follower::increaseDamageDone(int increase)
{
	damage += increase;
}

void Follower::placeFollower(int width, int height)
{
	setPosition(rand() % width, rand() % height);
}
