#include "Prophet.h"

sf::Vector2f Prophet::getCircCenter() const
{
	return sf::Vector2f(convertCirc.getGlobalBounds().left + convertCirc.getGlobalBounds().width / 2, convertCirc.getGlobalBounds().top + convertCirc.getGlobalBounds().height / 2);
}

Prophet::Prophet() :
	GameEntity("Prophet.png", 5, 5, 100)
{
	this->pointsToConvert = 100;
	this->convertingTimeMax = 1000;
	//this->group1 = new group();

	for (int i = 0; i < GROUPNR; i++)
	{

		this->group[i].capacity = 20;
		this->group[i].nrOfFollowers = 0;
		this->group[i].currentCommand = 0;
		this->group[i].followers = new Follower * [this->group[i].capacity]{ nullptr };

		
	}

	this->convertingSpeed = 10;
	this->chosenGroup = 0;
	this->collectedSouls = 0;
	setPosition(100, 100);
	this->moveHorizontal = 0;
	this->moveVertical = 0;
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
								group[a].followers[group[a].nrOfFollowers++] = follArr[i];
								std::cout << group[a].nrOfFollowers << std::endl;
								std::cout << currentCommandGroup << std::endl;
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
	if (sqrt(pow(otherBoundingBox.left - circCenter.x, 2) +
		pow(otherBoundingBox.top + otherBoundingBox.height - circCenter.y, 2)) < CircRadius)
	{
		collided = true;
	}
	if (sqrt(pow(otherBoundingBox.left + otherBoundingBox.width - circCenter.x, 2) +
		pow(otherBoundingBox.top - circCenter.y, 2)) < CircRadius)
	{
		collided = true;
	}
	if (sqrt(pow(otherBoundingBox.left + otherBoundingBox.width - circCenter.x, 2) +
		pow(otherBoundingBox.top + otherBoundingBox.height - circCenter.y, 2)) < CircRadius)
	{
		collided = true;
	}

	/*float distX = abs((convertCirc.getGlobalBounds().left + convertCirc.getGlobalBounds().width / 2) -  (otherBoundingBox.left + otherBoundingBox.width/2));
	float distY = abs((convertCirc.getGlobalBounds().top + convertCirc.getGlobalBounds().height / 2) - (otherBoundingBox.top + otherBoundingBox.height / 2));
	if (distX > (otherBoundingBox.width / 2 + convertCirc.getRadius()) ||
		distY > (otherBoundingBox.height / 2 + convertCirc.getRadius()))
	{
		collided = false;
	}
	else if(distX <= otherBoundingBox.width / 2 && distY <= otherBoundingBox.height / 2)
	{
		collided = true;
	}*/

	return collided;
}

void Prophet::moveProphet()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->moveVertical = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->moveVertical = 1;
	}
	else
	{
		this->moveVertical = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->moveHorizontal = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->moveHorizontal = -1;
	}
	else
	{
		this->moveHorizontal = 0;
	}
	setMovingSpeed(moveHorizontal, moveVertical);
	move();
	//convertCirc.setPosition(getBounds().left, getBounds().top);
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

void Prophet::recieveEnemyProphet(Prophet* other)
{
	otherProphet = other;
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
	std::cout << chosenAbility << std::endl;
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
			std::cout << this->group[i].currentCommand << std::endl;
			return this->group[i].currentCommand;
		}
	}
	

	
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
