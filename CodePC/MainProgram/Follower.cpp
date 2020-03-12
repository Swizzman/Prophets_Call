#include "Follower.h"

void Follower::die()
{
	//die;

	alive = false;
	switchTexture("soul.png ");
	followerDied();



}

Follower::Follower() : GameEntity("CivilianSpriteSheet.png", 1, 1, 100, false)
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
	soulCollected = false;
	maxTime = rand() % 6000 + 2000;
	convertedAmount = 0;
	
	setMovingSpeed(getMovingSpeedX() - rand() % 3, getMovingSpeedY() - rand() % 3);
	this->canAttack = true;
	followerRange = 100;
	attackCooldownTime = 2;
	lastWalkingDirection = 5;
}

Follower::~Follower()
{


}

void Follower::increaseDamageDone(int increase)
{
	if (isAlive())
	{
		damage += increase;
		cout << damage << endl;
	}
}

void Follower::returnDamage()
{
	if (isAlive())
	{
		damage = startDamage;
		cout << damage << endl;
	}
}

void Follower::checkCivMove()
{
	if (isAlive())
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
				//cout << abs(this->getMovingSpeedX()) << " : " << abs(this->getMovingSpeedY())<< endl;
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
				//	cout << "same walking speed " << endl;
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
	if (isAlive())
	{
		canAttack = false;
		//	cout << "ouch" << endl;
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
	if (isAlive())
	{

		attackTime += attackClock.restart();

		if (attackTime.asSeconds() > attackCooldownTime)
		{

			//cout << "Timer restart " << endl;
			attackTime = sf::Time::Zero;
			canAttack = true;


		}

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
	if (isAlive())
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
	if (isAlive())
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

void Follower::Collided(GameEntity* other)
{

	if (!converted)
	{




		//if (this->getMovingSpeedY() == 0 && this->getMovingSpeedX() == 0)
		//{
		//	setPosition(getPosition().x, getPosition().y);
		////	startAnimation(lastWalkingDirection,1,15,-1);
		//	
		//}
		//else if (this->getMovingSpeedX() == 0 && this->getMovingSpeedY() != 0)
		//{
		//	setPosition(getPosition().x, getPosition().y - getMovingSpeedY() / abs(getMovingSpeedY()));
		//}
		//else if (this->getMovingSpeedY() == 0)
		//{
		//	setPosition(getPosition().x - getMovingSpeedX() / abs(getMovingSpeedX()), getPosition().y);
		//}

		//if (this->getMovingSpeedY() != 0 && this->getMovingSpeedX() != 0)
		//{
		//	setPosition(getPosition().x - getMovingSpeedX() / abs(getMovingSpeedX()), getPosition().y - getMovingSpeedY() / abs(getMovingSpeedY()));
		//}
		//setMovingSpeed(-getMovingSpeedX(), -getMovingSpeedY());
		//if (abs(this->getMovingSpeedX()) > abs(this->getMovingSpeedY()) && this->getMovingSpeedX() > 0)
		//{
		//	startAnimation((int)FOLLOWERSPRITEROW::WALKINGRIGHT, 9, 15, 0);
		//	lastWalkingDirection = (int)FOLLOWERSPRITEROW::WALKINGRIGHT;
		//}
		//else if (abs(this->getMovingSpeedX()) > abs(this->getMovingSpeedY()) && this->getMovingSpeedX() < 0)
		//{
		//	startAnimation((int)FOLLOWERSPRITEROW::WALKINGLEFT, 9, 15, 0);
		//	lastWalkingDirection = (int)FOLLOWERSPRITEROW::WALKINGLEFT;
		//}
		//else if (abs(this->getMovingSpeedX()) < abs(this->getMovingSpeedY()) && this->getMovingSpeedY() > 0)
		//{
		//	startAnimation((int)FOLLOWERSPRITEROW::WALKINGDOWN, 9, 15, 0);
		//	lastWalkingDirection = (int)FOLLOWERSPRITEROW::WALKINGDOWN;
		//}
		//else if (abs(this->getMovingSpeedX()) < abs(this->getMovingSpeedY()) && this->getMovingSpeedY() < 0)
		//{
		//	startAnimation((int)FOLLOWERSPRITEROW::WALKINGUP, 9, 15, 0);
		//	lastWalkingDirection = (int)FOLLOWERSPRITEROW::WALKINGUP;
		//}
		//if (getMovingSpeedX() == 0 && getMovingSpeedY() == 0)
		//{
		//	startAnimation(lastWalkingDirection, 1, 15, -1);
		//}
		//updateAnimation();

	}


}

float Follower::getFollowerRange()
{
	return followerRange;
}

bool Follower::getIfAlive()
{
	return alive;
}
