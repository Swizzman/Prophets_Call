#include "GameEntity.h"
class Follower;
GameEntity::GameEntity(string textureName, int movingSpeedX, int movingSpeedY, int health)
{
	this->texture.loadFromFile("../images/" + textureName);
	this->sprite.setTexture(texture);
	this->movingSpeedX = movingSpeedX;
	this->movingSpeedY = movingSpeedY;
	this->health = health;
	this->maxHealth = health;
	this->textureName = textureName;
	collided = false;
	abilityHasTakenAffect = false;
	

	range = 100;

	randomPos = sf::Vector2f(rand() % 300 -150, rand() % 300-150);
	maxTime = rand() % 6000 + 2000;
}

GameEntity::GameEntity()
{
	texture.loadFromFile("???");
	this->sprite.setTexture(texture);

}

GameEntity::~GameEntity()
{

}

void GameEntity::takeDamage(int damage)
{
	this->health -= damage;
	if (this->health < 0 )
	{
		this->health = 0;
	}
	std::cout << health << std::endl;
}

sf::Vector2f GameEntity::getPos()
{
	return sprite.getPosition();
}

sf::FloatRect GameEntity::getBounds()
{
	return sprite.getGlobalBounds();
}

void GameEntity::switchTexture(std::string newTexture)
{
	texture.loadFromFile("../images/" + newTexture);
	sprite.setTexture(texture);
	this->textureName = newTexture;
}

int GameEntity::getHealth()
{
	
	return health;
}

void GameEntity::gainHealth(int health)
{
	if (this->health < maxHealth)
	{
		this->health += health;
	}

	if(this->health >= maxHealth)
	{
		this->health = maxHealth;
	}
	//cout << this->maxHealth << endl;
	cout << this->health << endl;

}


//void GameEntity::attackCooldown()
//{
//
//	canAttack = true;
//}

bool GameEntity::getAttackBool()
{
	return canAttack;
}

void GameEntity::attack(GameEntity* enemy, int damage)
{
	//if (sqrt(pow(enemy->getPos().x - sprite.getPosition().x, 2) + pow(enemy->getPos().y - sprite.getPosition().y, 2) <= range &&
	//	sqrt(pow(enemy->getPos().x - sprite.getPosition().x, 2) + pow(enemy->getPos().y - sprite.getPosition().y, 2) >= -range)))
	//{
	//	if (canAttack == true)
	//	{
	//		enemy->takeDamage(damage);

	//		//attack enemy object
	//		canAttack = false;
	//	}
	//	
	//	

	//}


}

void GameEntity::move()
{
	this->sprite.move(movingSpeedX, movingSpeedY);
}

void GameEntity::moveTowardsDest(sf::Vector2f dest, int currentCommand)
{
	getNewRandomPos(currentCommand, false);
	/*sf::Vector2f dist = dest- getPosition();
	float magni = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
	sf::Vector2f dir = sf::Vector2f(dist.x / magni, dist.y / magni);*/
	
	this->sprite.move(dest.x * movingSpeedX, dest.y * movingSpeedY);


}

void GameEntity::setMovingSpeed(int newSpeedX, int newSpeedY)
{
	this->movingSpeedX = newSpeedX;
	this->movingSpeedY = newSpeedY;
}

int GameEntity::getMovingSpeedX()
{
	return movingSpeedX;
}

int GameEntity::getMovingSpeedY()
{
	return movingSpeedY;
}

void GameEntity::setPosition(float xPos, float yPos)
{

	this->sprite.setPosition(xPos, yPos);
}

string GameEntity::getTextureName()
{
	return textureName;
}

sf::Vector2f GameEntity::getPosition()
{
	return this->sprite.getPosition();
}

sf::Vector2f GameEntity::getOrigin()
{
	return this->sprite.getOrigin();
}

sf::Vector2f GameEntity::getRandomPos()
{
	return randomPos;
}

void GameEntity::getNewRandomPos(int currentCommand, bool reset)
{
		
	moveTimer += clock.restart();
	int randomPosRange=0;

	if (currentCommand == 0)
	{
		randomPosRange = 250;
	}
	else if (currentCommand == 1)
	{
		randomPosRange = 0;
	}
	else if (currentCommand == 2)
	{
		randomPosRange = 0 ;
	}
	else
	{
		randomPosRange = range;
		randomPosRange *= 2;
	}
	if (reset)
	{
		//float xRPos = rand() % 250 - dynamic_cast<class Prophet>(this->)
		randomPos = sf::Vector2f(rand() % randomPosRange - randomPosRange / 2, rand() % randomPosRange - randomPosRange / 2);
		moveTimer = sf::Time::Zero;
		maxTime = rand() % 5000 + 2000;
		reset = false;
		
	}
	if (moveTimer.asMilliseconds() > maxTime && randomPosRange != 0)
	{
		//float xRPos = rand() % 250 - dynamic_cast<class Prophet>(this->)
		randomPos = sf::Vector2f(rand() % randomPosRange- randomPosRange/2, rand() % randomPosRange - randomPosRange/2);
		moveTimer = sf::Time::Zero;
		maxTime = rand() % 5000 + 2000;
		
		
	}
	
	
}
//
//void GameEntity::Collided(GameEntity* other)
//{
//	if (other != this)
//	{
//		if (this->getBounds().intersects(other->getBounds()))
//		{
//
//		this->setMovingSpeed(-getMovingSpeedX(), -getMovingSpeedY());
//		//other->setMovingSpeed(-other->getMovingSpeedX(), -other->getMovingSpeedY());
//		this->move();
//		//other->move();
//		}
//	}
//}

bool GameEntity::getCollidedBool()
{
	return collided;
}

void GameEntity::touchedByAbility(bool abilityIsActive)
{
	if (abilityIsActive == true)
	{

	abilityHasTakenAffect = true;
	}
	else
	{
		abilityHasTakenAffect = false;
	}

}

bool GameEntity::CheckIfEntityCanBeAffectedByAbility()
{
	return abilityHasTakenAffect;
}

bool GameEntity::getIfIsInRangeOfAbility(bool IsInRange)
{
	if (IsInRange)
	{
		isInRangeOfAbility = true;
	}
	else
		isInRangeOfAbility = false;
	return	isInRangeOfAbility;
}

float GameEntity::getRange()
{

	return range;
}




void GameEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);

}

