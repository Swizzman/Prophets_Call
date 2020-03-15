#include "Prophet.h"

sf::Vector2f Prophet::getCircCenter() const
{
	return sf::Vector2f(convertCirc.getGlobalBounds().left + convertCirc.getGlobalBounds().width / 2,
		convertCirc.getGlobalBounds().top + convertCirc.getGlobalBounds().height / 2);
}

Prophet::Prophet() :
	GameEntity("thisProphetSpriteSheet.png", 0, 0, 1000, true)
{

	for (int i = 0; i < GROUPNR; i++)
	{

		this->group[i].capacity = 20;
		this->group[i].nrOfFollowers = 0;
		this->group[i].currentCommand = 0;
		this->group[i].followers = new Follower * [this->group[i].capacity]{ nullptr };


	}

	this->xSpeed = 2;
	this->ySpeed = 2;
	this->convertingTimeMax = 500;
	this->chosenAbility = 0;
	this->convertingSpeed = 10;
	this->chosenGroup = 0;
	this->collectedSouls = 100;
	this->otherProphet = nullptr;
	this->convertCirc.setRadius(150);
	this->convertCirc.setFillColor(sf::Color::Transparent);
	this->convertCirc.setOutlineColor(sf::Color::Red);
	this->convertCirc.setOutlineThickness(5.f);
	this->convertCirc.setOrigin(getPosition().x + getBounds().width / 2, getPosition().y + getBounds().height / 2);
	this->abilityActive = false;
	this->abilityAnimation = false;
	this->lastWalkingDirection = 0;
	this->currentCommandGroup = 0;
	setPosition(100, 100);


}

Prophet::~Prophet()
{
	for (int i = 0; i < GROUPNR; i++)
	{

		delete[] group[i].followers;

	}

}



void Prophet::convert(Follower** follArr, int nrOf)
{
	convertingTime += clock.restart();

	if (otherProphet != nullptr)
	{
		if (convertingTime.asMilliseconds() > convertingTimeMax)
		{
			for (int a = 0; a < GROUPNR; a++)
			{
				if (currentCommandGroup == a)
				{


					for (int i = 0; i < nrOf && group[a].nrOfFollowers < group[a].capacity; i++)
					{
						if (!follArr[i]->getConverted())
						{

							if (group[a].nrOfFollowers < group[a].capacity)
							{
								if (checkCollision(follArr[i]->getBounds()))
								{

									follArr[i]->convert();
									if (follArr[i]->getConverted())
									{
										group[a].followers[group[a].nrOfFollowers++] = follArr[i];

									}

								}

							}
						}
					}
				}
			}
			convertingTime = sf::Time::Zero;
		}
	}

}

void Prophet::convertsFollow()
{

	if (otherProphet != nullptr)
	{
		commandMan.useCommand();
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

}

void Prophet::resetClock()
{
	clock.restart();
}



bool Prophet::checkCollision(sf::FloatRect otherBoundingBox)
{
	bool collided = false;
	sf::Vector2f circCenter = getCircCenter();
	float CircRadius = convertCirc.getRadius();
	if (sqrt(pow(otherBoundingBox.left - circCenter.x, 2) +
		pow(otherBoundingBox.top - circCenter.y, 2)) < CircRadius)
	{
		collided = true;
	}
	else if (sqrt(pow(otherBoundingBox.left - circCenter.x, 2) +
		pow(otherBoundingBox.top + otherBoundingBox.height - circCenter.y, 2)) < CircRadius)
	{
		collided = true;
	}
	else if (sqrt(pow(otherBoundingBox.left + otherBoundingBox.width - circCenter.x, 2) +
		pow(otherBoundingBox.top - circCenter.y, 2)) < CircRadius)
	{
		collided = true;
	}
	else if (sqrt(pow(otherBoundingBox.left + otherBoundingBox.width - circCenter.x, 2) +
		pow(otherBoundingBox.top + otherBoundingBox.height - circCenter.y, 2)) < CircRadius)
	{
		collided = true;
	}

	return collided;
}

void Prophet::moveProphet()
{
	int hDir = 0;
	int vDir = 0;
	if (getCurrentPriority() <= 0)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			hDir = this->xSpeed;
			startAnimation((int)ANIMATIONSPRITEROW::WALKINGRIGHT, 9, 10, 0);
			lastWalkingDirection = (int)ANIMATIONSPRITEROW::WALKINGRIGHT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{

			hDir = -this->xSpeed;
			startAnimation((int)ANIMATIONSPRITEROW::WALKINGLEFT, 9, 10, 0);
			lastWalkingDirection = (int)ANIMATIONSPRITEROW::WALKINGLEFT;
		}
		else
		{
			hDir = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			vDir = -this->ySpeed;
			startAnimation((int)ANIMATIONSPRITEROW::WALKINGUP, 9, 10, 0);
			lastWalkingDirection = (int)ANIMATIONSPRITEROW::WALKINGUP;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			vDir = this->ySpeed;
			startAnimation((int)ANIMATIONSPRITEROW::WALKINGDOWN, 9, 10, 0);
			lastWalkingDirection = (int)ANIMATIONSPRITEROW::WALKINGDOWN;
		}
		else
		{
			vDir = 0;

		}
	}
	if (hDir == 0 && vDir == 0)
	{

		startAnimation(lastWalkingDirection, 1, 30, -1);
	}
	updateAnimation();
	setMovingSpeed(hDir, vDir);
	move();

	convertCirc.setPosition(getPosition().x - convertCirc.getRadius() / 2 - 11, getPosition().y - convertCirc.getRadius() / 2 - 11);


}

int Prophet::getNrOfFollowers()
{
	int nrOf = 0;
	for (int i = 0; i < GROUPNR; i++)
	{
		if (currentCommandGroup == i)
		{
			nrOf = group[i].nrOfFollowers;
		}
	}
	return nrOf;
}

int Prophet::getAllNrOfFollowers(int thisGroup)
{
	int nrOf = 0;
	for (int i = 0; i < GROUPNR; i++)
	{
		if (i == thisGroup)
		{
			nrOf = group[i].nrOfFollowers;

		}

	}
	return nrOf;
}


void Prophet::collectSouls(Follower* follower)
{
	if (checkCollision(follower->getBounds()) && !follower->getSoulCollected())
	{
		collectedSouls += follower->getSoulValue();
		follower->setSoulCollected();
	}
}

void Prophet::placeAbil(sf::Vector2f position, int force)
{

	if (otherProphet != nullptr)
	{

		abilityMan.placeCurrentAbility(position, force);
	}
}

int Prophet::getSouls() const
{
	return collectedSouls;
}

void Prophet::decreaseSouls(int amount)
{
	collectedSouls -= amount;
	if (collectedSouls < 0)
	{
		collectedSouls = 0;
	}
}

Follower* Prophet::getFollowers() const
{
	Follower* follower = nullptr;
	for (int i = 0; i < GROUPNR; i++)
	{
		if (currentCommandGroup == i)
		{
			follower = *group[i].followers;
		}
	}
	return follower;
}

Follower& Prophet::getASingleFollower(int whichOne)const
{

	for (int i = 0; i < GROUPNR; i++)
	{

		if (currentCommandGroup == i)
		{

			return *group[i].followers[whichOne];
		}
	}

}

Follower** Prophet::getAllFollowers(int thisGroup) const
{
	for (int i = 0; i < GROUPNR; i++)
	{
		if (i == thisGroup)
		{

			return group[i].followers;
		}
	}
}

void Prophet::recieveEnemyProphet(Prophet* other)
{
	if (other != nullptr && this != nullptr)
	{
		otherProphet = other;
		abilityMan.recievePtr(other, this, &group[currentCommandGroup]);
		commandMan.recievePtr(other, &group[currentCommandGroup], this);
	}
}

int Prophet::getCurrentAbility() const
{
	return chosenAbility;
}

void Prophet::changeAbility()
{
	if (otherProphet != nullptr)
	{

		chosenAbility++;
		if (chosenAbility > 2)
		{
			chosenAbility = 0;
		}
		abilityMan.switchAbility();
	}
}



sf::CircleShape Prophet::getConvertCirc() const
{
	return convertCirc;
}

void Prophet::changeCurrentCommandGroup()
{
	currentCommandGroup++;

	if (currentCommandGroup > GROUPNR - 1)
	{
		currentCommandGroup = 0;
	}

}

int Prophet::getCurrentGroupCommand()
{
	int command = 0;
	for (int i = 0; i < GROUPNR; i++)
	{

		if (currentCommandGroup == i)
		{
			if (this->group[i].currentCommand > 3)
			{
				this->group[i].currentCommand = 0;
			}
			command = this->group[i].currentCommand;
		}
	}
	return command;


}

Ability* Prophet::getCurAbil() const
{
	if (otherProphet != nullptr)
	{

		return abilityMan.getCurrentAbility();
	}
	else
	{
		return nullptr;
	}
}

bool Prophet::getIfSoundBoolIsActive()
{
	if (otherProphet != nullptr)
	{
		return abilityMan.getActivateSoundBool();
	}
	else
	{
		return false;
	}
}


void Prophet::changeCurrentCommand()
{
	if (otherProphet != nullptr)
	{

		commandMan.switchCommand(currentCommandGroup);
	}

}

bool Prophet::getIfAbilityIsActive()
{
	if (otherProphet != nullptr)
	{

		return abilityMan.getAbilityActive();
	}
	else
	{
		abilityAnimation = false;
		return false;
	}
}

void Prophet::timerForAbility()
{
	if (otherProphet != nullptr)
	{
		if (abilityAnimation == false)
		{
			abilityAnimation = true;
		}

		abilityMan.stopAbility();
		abilityMan.whileAbilityIsActive();
	}

}

void Prophet::endingReinforcementAbility()
{
	if (otherProphet != nullptr)
	{

		abilityMan.stopReinforceAbility();
	}
}

bool Prophet::returnReinforceBool()
{
	bool reinforce = false;
	if (otherProphet != nullptr)
	{
		reinforce = abilityMan.returnReinforcementBool();
	}
	return reinforce;

}

int Prophet::getWalkingDirection() const
{
	return lastWalkingDirection;
}

int Prophet::getCurrentGroup() const
{
	return chosenGroup;
}

void Prophet::addFollower(Follower* follower)
{
	bool added = false;
	for (int i = 0; i < GROUPNR && !added; i++)
	{

		if (group[i].nrOfFollowers < group[i].capacity)
		{
			group[i].followers[group[i].nrOfFollowers] = follower;
			added = true;
			group[i].nrOfFollowers++;

		}
	}
}

void Prophet::removeFollower(Follower* follower)
{

	for (int i = 0; i < GROUPNR; i++)
	{
		for (int a = 0; a < group[i].nrOfFollowers; a++)
		{

			if (group[i].followers[a] == follower)
			{
				group[i].followers[a] = nullptr;
				for (int b = a; b < group[i].nrOfFollowers; b++)
				{
					group[i].followers[b] = group[i].followers[b + 1];
				}
				group[i].followers[group[i].nrOfFollowers] = nullptr;
				group[i].nrOfFollowers--;

			}
		}
	}
}


void Prophet::die()
{

}
