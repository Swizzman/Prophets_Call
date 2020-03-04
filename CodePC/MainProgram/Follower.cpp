#include "Follower.h"

void Follower::die()
{
}

Follower::Follower() : GameEntity("Civilian.png", 1, 1, 60)
{
	windowHeight = 0;
	windowWidth = 0;
	damage = 20;
	startDamage = 20;
	soulValue = 40;
	attackRange = 5.f;
	alive = true;
	converted = false;
	maxTime = rand() % 6000 + 2000;
	convertedAmount = 0;
	setMovingSpeed(getMovingSpeedX() - rand() % 3, getMovingSpeedY() - rand() % 3);
	test = 0;
}

Follower::~Follower()
{
}

void Follower::increaseDamageDone(int increase)
{
	damage += increase;
	cout << damage << endl;
}

void Follower::returnDamage()
{
	damage = startDamage;
	cout << damage << endl;
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

void Follower::convert()
{
	if (convertedAmount >= 100)
	{
		converted = true;
		switchTexture("Follower.png");

	}
	else
	{
		convertedAmount += 30;
	}
}



bool Follower::getConverted() const
{
	return converted;
}

int Follower::getConvertedAmount() const
{
	return convertedAmount;
}

void Follower::Collided(GameEntity* other)
{
	
	//moveTimer = sf::milliseconds(maxTime);
	/*if (getMovingSpeedX() == 0 && getMovingSpeedY == 0)
	{
		getmov
	}*/
	if (!converted)
	{


		if (this->getMovingSpeedY() == 0 && this->getMovingSpeedX() == 0)
		{
			setPosition(getPosition().x, getPosition().y);
		}
		else if (this->getMovingSpeedX() == 0 && this->getMovingSpeedY() != 0)
		{
			setPosition(getPosition().x, getPosition().y - getMovingSpeedY() / abs(getMovingSpeedY()));
		}
		else if (this->getMovingSpeedY() == 0)
		{
			setPosition(getPosition().x - getMovingSpeedX() / abs(getMovingSpeedX()), getPosition().y);
		}

		if (this->getMovingSpeedY() != 0 && this->getMovingSpeedX() != 0)
		{
			setPosition(getPosition().x - getMovingSpeedX() / abs(getMovingSpeedX()), getPosition().y - getMovingSpeedY() / abs(getMovingSpeedY()));
		}

		

			setMovingSpeed(-getMovingSpeedX(), -getMovingSpeedY());
		
	}
	

}
