#include "Prophet.h"

sf::Vector2f Prophet::getCircCenter() const
{
	return sf::Vector2f(convertCirc.getGlobalBounds().left + convertCirc.getGlobalBounds().width / 2, convertCirc.getGlobalBounds().top + convertCirc.getGlobalBounds().height / 2);
}

Prophet::Prophet() :
	GameEntity("Prophet.png", 0, 0, 100)
{

	//this->group1 = new group();

	for (int i = 0; i < GROUPNR; i++)
	{

		this->group[i].capacity = 20;
		this->group[i].nrOfFollowers = 0;
		this->group[i].currentCommand = 0;
		this->group[i].followers = new Follower * [this->group[i].capacity]{ nullptr };

		
	}
	this->xSpeed = 5;
	this->ySpeed = 5;
	this->convertingTimeMax = 500;
	this->chosenAbility = 0;
	this->convertingSpeed = 10;
	this->chosenGroup = 0;
	this->collectedSouls = 0;
	setPosition(100, 100);
	this->otherProphet = nullptr;
	this->convertCirc.setRadius(150);
	this->convertCirc.setFillColor(sf::Color::Transparent);
	this->convertCirc.setOutlineColor(sf::Color::Red);
	this->convertCirc.setOutlineThickness(5.f);
	this->convertCirc.setOrigin(getOrigin());
	currentCommandGroup = 0;
}

Prophet::~Prophet()
{
}

void Prophet::convert(Follower** follArr, int nrOf)
{
	convertingTime += clock.restart();
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
									//std::cout << group[a].nrOfFollowers << std::endl;

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

void Prophet::convertsFollow()
{
	for (int a = 0; a < GROUPNR; a++)
	{
		if (currentCommandGroup == a)
		{
			for (int i = 0; i < group[a].nrOfFollowers; i++)
			{
				group[a].followers[i]->moveTowardsDest(getPosition());
			}
		}
	}
	
}

void Prophet::resetClock()
{
	clock.restart();
}

bool Prophet::checkMovement()
{
	return false;
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		vDir = -this->ySpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		vDir = this->ySpeed;

	}
	else
	{
		vDir = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		hDir = this->xSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{

		hDir = -this->xSpeed;
	}
	else
	{
		hDir = 0;
	}
	setMovingSpeed(hDir, vDir);
	move();
	convertCirc.setPosition(getBounds().left - getBounds().width, getBounds().top - getBounds().height - 20);

}

int Prophet::getNrOfFollowers()
{
	for (int i = 0; i < GROUPNR; i++)
	{
		if (currentCommandGroup == i)
		{
			return group[i].nrOfFollowers;
		}
	}
	
}

void Prophet::addFollower()
{
}

void Prophet::collectSouls()
{
}

void Prophet::placeAbil(sf::Vector2f position)
{
	abilityMan.placeCurrentAbility(position);
}

int Prophet::getSouls()
{
	return collectedSouls;
}

Follower* Prophet::getFollowers()
{
	for (int i = 0; i < GROUPNR; i++)
	{
		if (currentCommandGroup == i)
		{
			return *group[i].followers;
		}
	}
	
}

Follower Prophet::getASingleFollower(int whichOne)
{
	for (int i = 0; i < GROUPNR; i++)
	{

		if (currentCommandGroup == i)
		{
			
			return *group[i].followers[whichOne-1];
		}
	}
	
}

void Prophet::recieveEnemyProphet(Prophet* other)
{
	otherProphet = other;
	abilityMan.recievePtr(other, &group[currentCommandGroup]);
}

int Prophet::getCurrentAbility()
{


	return chosenAbility;
}

void Prophet::changeAbility()
{
	chosenAbility++;
	if (chosenAbility >= 3)
	{
		chosenAbility = 0;
	}
	//std::cout << chosenAbility << std::endl;
}

void Prophet::checkAbility()
{
	if ((abilityActive = abilityMan.getAbilityActive()) == true)
	{
		abilityMan.placeCurrentAbility((sf::Vector2f)abilityMouse.getPosition());
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

int Prophet::getcurrentGroupCommand()
{

	for (int i = 0; i < GROUPNR; i++)
	{

		if (currentCommandGroup == i)
		{
			this->group[i].currentCommand++;
			if (this->group[i].currentCommand > 3)
			{
				this->group[i].currentCommand = 0;
			}
			//std::cout << this->group[i].currentCommand << std::endl;
			return this->group[i].currentCommand;
		}
	}
	

	
}

Ability* Prophet::getCurAbil() const
{
	return abilityMan.getCurrentAbility();
}


void Prophet::die()
{
	for (int i = 0; i < GROUPNR; i++)
	{
		for (int i = 0; i < group[i].nrOfFollowers; i++)
		{
			delete group[i].followers[i];
		}
		delete[] group[i].followers;
	}
	
	delete group;
}
