#include "Prophet.h"

sf::Vector2f Prophet::getCircCenter() const
{
	return sf::Vector2f(convertCirc.getGlobalBounds().left + convertCirc.getGlobalBounds().width / 2, convertCirc.getGlobalBounds().top + convertCirc.getGlobalBounds().height / 2);
}

Prophet::Prophet() :
	GameEntity("Prophet.png", 5, 5, 100)
{
	this->group1 = new group();
	this->group1->capacity = 20;
	this->group1->nrOfFollowers = 0;
	this->group1->currentCommand = 0;
	this->group1->followers = new Follower * [this->group1->capacity]{ nullptr };
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
}

Prophet::~Prophet()
{
}

void Prophet::convert(Follower** follArr, int nrOf)
{

	for (int i = 0; i < nrOf && group1->nrOfFollowers < group1->capacity; i++)
	{
		if (!follArr[i]->getConverted())
		{

			if (group1->nrOfFollowers < group1->capacity)
			{
				if (checkCollision(follArr[i]->getBounds()))
				{
					follArr[i]->convert();
					group1->followers[group1->nrOfFollowers++] = follArr[i];
					std::cout << group1->nrOfFollowers << std::endl;
				}
			}
		}
	}

}

void Prophet::convertsFollow()
{
	for (int i = 0; i < group1->nrOfFollowers; i++)
	{
		group1->followers[i]->moveTowardsDest(getPosition());
	}
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
	return group1->nrOfFollowers;
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
	return *group1->followers;
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
	if (chosenAbility >= 3 )
	{
		chosenAbility = 0;
	}
	std::cout << chosenAbility << std::endl;
}

sf::CircleShape Prophet::getConvertCirc() const
{
	return convertCirc;
}

void Prophet::die()
{
	for (int i = 0; i < group1->nrOfFollowers; i++)
	{
		delete group1->followers[i];
	}
	delete [] group1->followers;
	delete group1;
}
