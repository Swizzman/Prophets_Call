#include "Follower.h"

void Follower::die()
{
}

Follower::Follower() : GameEntity("Civilian.png", 1, 1, 60)
{
	windowHeight = 0;
	windowWidth = 0;
	damage = 20;
	soulValue = 40;
	attackRange = 5.f;
	alive = true;
	converted = false;
	clientNotified = false;
	maxTime = rand() % 6000 + 2000;
	convertedAmount = 0;
	setMovingSpeed(getMovingSpeedX() - rand() % 3, getMovingSpeedY() - rand() % 3);

}

Follower::~Follower()
{
}

void Follower::increaseDamageDone(int increase)
{
	damage += increase;
}

void Follower::checkCivMove()
{
	if (!converted)
	{

		moveTimer += clock.restart();
		if (moveTimer.asMilliseconds() > maxTime)
		{
			setMovingSpeed(1, 1);
			setMovingSpeed(getMovingSpeedX() - rand() % 3, getMovingSpeedY() - rand() % 3);
			moveTimer = sf::Time::Zero;
			maxTime = rand() % 6000 + 2000;

		}
		move();
		if (getPosition().x < 0 || getPosition().x + getBounds().width > windowWidth)
		{
			setMovingSpeed(-getMovingSpeedX(), getMovingSpeedY());
		}
		else if (getPosition().y < 0 || getPosition().y + getBounds().height > windowHeight)
		{

			setMovingSpeed(-getMovingSpeedX(), -getMovingSpeedY());

		}
	}
	else
	{
		setMovingSpeed(1, 1);
	}
}


void Follower::placeFollower(int width, int height)
{
	setPosition(rand() % width, rand() % height);
	windowHeight = height;
	windowWidth = width;
}

void Follower::convert(bool force = false)
{
	if (!force)
	{

		if (convertedAmount >= 100)
		{
			converted = true;
			clientNotified = true;
			switchTexture("Follower.png");

		}
		else
		{
			convertedAmount += 30;
		}
	}
	else
	{
		converted = true;
		switchTexture("Follower.png");

	}
}



bool Follower::getConverted() const
{
	return converted;
}

bool Follower::getClientNotified()
{
	bool whatToReturn = clientNotified;
	if (clientNotified)
	{
		clientNotified = false;
	}
	return whatToReturn;
}

int Follower::getConvertedAmount() const
{
	return convertedAmount;
}
