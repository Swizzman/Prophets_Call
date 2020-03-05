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
	convertedByOther = false;
	otherNotified = false;
	maxTime = rand() % 6000 + 2000;
	convertedAmount = 0;
	setMovingSpeed(getMovingSpeedX() - rand() % 3, getMovingSpeedY() - rand() % 3);
	test = 0;
	this->canAttack = true;
	followerRange = 100;
	attackCooldownTime = 2;
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

int Follower::inflictDamage()
{
	canAttack = false;
//	cout << "ouch" << endl;
	return damage;
}

void Follower::attackCooldown()
{

	attackTime += attackClock.restart();

	if (attackTime.asSeconds() > attackCooldownTime)
	{

		//cout << "Timer restart " << endl;
		attackTime = sf::Time::Zero;
		canAttack = true;
		

	}



}

bool Follower::getAttackCooldown()
{
	return canAttack;
}

void Follower::resetAttackClock()
{
	attackClock.restart();
}

void Follower::convert()
{
	if (!converted)
	{


		if (convertedAmount >= 100)
		{
			converted = true;
			otherNotified = true;
			switchTexture("Follower.png");

		}
		else
		{
			convertedAmount += 30;
		}
	}


}

void Follower::otherConvert()
{
	convertedAmount = 200;
	converted = true;
	convertedByOther = true;
	switchTexture("Follower.png");

}

void Follower::otherIsNotified()
{
	otherNotified = false;
}

bool Follower::getOtherNotified() const
{
	return otherNotified;
}



bool Follower::getConverted() const
{
	return converted;
}

bool Follower::getConvertedByOther() const
{
	return convertedByOther;
}

int Follower::getConvertedAmount() const
{
	return convertedAmount;
}

void Follower::Collided(GameEntity* other)
{

 
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

float Follower::getFollowerRange()
{
	return followerRange;
}
