#include "Follower.h"

void Follower::die()
{
	alive = false;
	switchTexture("soul.png ");
	followerDied();
}

Follower::Follower() : GameEntity("CivilianSpriteSheet.png", 1, 1, 100, false)
{
	this->windowHeight = 0;
	this->windowWidth = 0;
	this->damage = 20;
	this->startDamage = 20;
	this->soulValue = 40;
	this->alive = true;
	this->converted = false;
	this->convertedByOther = false;
	this->otherNotified = false;
	this->soulCollected = false;
	this->maxTime = rand() % 6000 + 2000;
	this->convertedAmount = 0;
	setMovingSpeed(getMovingSpeedX() - rand() % 3, getMovingSpeedY() - rand() % 3);
	this->canAttack = true;
	this->followerRange = 100.f;
	this->attackCooldownTime = 2;
	this->lastWalkingDirection = 5;
}

Follower::~Follower()
{


}

void Follower::increaseDamageDone(int increase)
{
	if (getAlive())
	{
		damage += increase;
	}
}

void Follower::resetDamage()
{
	if (getAlive())
	{
		damage = startDamage;
	}
}

void Follower::checkCivMove()
{
	if (getAlive())
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

			if (abs(this->getMovingSpeedX()) > abs(this->getMovingSpeedY()) && this->getMovingSpeedX() > 0)
			{
				startAnimation((int)FOLLOWERSPRITEROW::WALKINGRIGHT, 9, 15, 0);
				lastWalkingDirection = (int)FOLLOWERSPRITEROW::WALKINGRIGHT;

			}
			else if (abs(this->getMovingSpeedX()) > abs(this->getMovingSpeedY()) && this->getMovingSpeedX() < 0)
			{
				startAnimation((int)FOLLOWERSPRITEROW::WALKINGLEFT, 9, 15, 0);
				lastWalkingDirection = (int)FOLLOWERSPRITEROW::WALKINGLEFT;
			}
			else if (abs(this->getMovingSpeedX()) < abs(this->getMovingSpeedY()) && this->getMovingSpeedY() > 0)
			{
				startAnimation((int)FOLLOWERSPRITEROW::WALKINGDOWN, 9, 15, 0);
				lastWalkingDirection = (int)FOLLOWERSPRITEROW::WALKINGDOWN;
			}
			else if (abs(this->getMovingSpeedX()) < abs(this->getMovingSpeedY()) && this->getMovingSpeedY() < 0)
			{
				startAnimation((int)FOLLOWERSPRITEROW::WALKINGUP, 9, 15, 0);
				lastWalkingDirection = (int)FOLLOWERSPRITEROW::WALKINGUP;
			}

			if (abs(getMovingSpeedX()) == abs(getMovingSpeedY()) && this->getMovingSpeedY() < 0)
			{
				startAnimation((int)FOLLOWERSPRITEROW::WALKINGUP, 9, 15, 0);
				lastWalkingDirection = (int)FOLLOWERSPRITEROW::WALKINGUP;
			}
			else if (abs(getMovingSpeedX()) == abs(getMovingSpeedY()) && this->getMovingSpeedY() > 0)
			{
				startAnimation((int)FOLLOWERSPRITEROW::WALKINGDOWN, 9, 15, 0);
				lastWalkingDirection = (int)FOLLOWERSPRITEROW::WALKINGDOWN;
			}
			else if (getMovingSpeedX() == 0 && getMovingSpeedY() == 0)
			{
				startAnimation(lastWalkingDirection, 1, 15, -1);

			}

			updateAnimation();
		}
		else
		{
			setMovingSpeed(1, 1);
		}
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
	if (getAlive())
	{
		canAttack = false;
		return damage;
	}
}

int Follower::getSoulValue() const
{
	return soulValue;
}

void Follower::setSoulCollected()
{
	soulCollected = true;
}

bool Follower::getSoulCollected() const
{
	return soulCollected;
}

void Follower::attackCooldown()
{
	if (getAlive())
	{

		attackTime += attackClock.restart();

		if (attackTime.asSeconds() > attackCooldownTime)
		{

			attackTime = sf::Time::Zero;
			canAttack = true;


		}

	}

}

bool Follower::getAttackCooldown() const
{
	return canAttack;
}

void Follower::resetAttackClock()
{
	attackClock.restart();
}

void Follower::convert()
{
	if (getAlive())
	{
		if (!converted)
		{


			if (convertedAmount >= 100)
			{
				converted = true;
				otherNotified = true;
				switchTexture("FollowerSpriteSheet.png");

			}
			else
			{
				convertedAmount += 30;
			}
		}
	}

}

void Follower::otherConvert()
{
	if (getAlive())
	{
		convertedAmount = 200;
		converted = true;
		switchTexture("EnemyFollowerSpriteSheet.png");
		convertedByOther = true;

	}
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



float Follower::getFollowerRange() const
{
	return followerRange;
}

bool Follower::getIfAlive() const
{
	return alive;
}
