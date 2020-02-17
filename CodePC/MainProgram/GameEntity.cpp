#include "GameEntity.h"

GameEntity::GameEntity(string textureName, int movingSpeedX, int movingSpeedY, int health)
{
	this->texture.loadFromFile("../images/" + textureName);
	this->sprite.setTexture(texture);
	this->movingSpeedX = movingSpeedX;
	this->movingSpeedY = movingSpeedY;
	this->health = health;


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
}

sf::Vector2f GameEntity::getPos()
{
	return sprite.getPosition();
}

sf::FloatRect GameEntity::getBounds()
{
	return sprite.getGlobalBounds();
}

int GameEntity::getHealth()
{
	return health;
}

void GameEntity::gainHelth()
{
	this->health += 75;

}


void GameEntity::attackCooldown()
{
	
	canAttack = true;
}

bool GameEntity::getAttackBool()
{
	return canAttack;
}

void GameEntity::attack(GameEntity* enemy, float range, int damage)
{
	if (sqrt (pow(enemy->getPos().x - sprite.getPosition().x,2) + pow(enemy->getPos().y - sprite.getPosition().y,2) <=range &&
		sqrt(pow(enemy->getPos().x - sprite.getPosition().x, 2) + pow(enemy->getPos().y - sprite.getPosition().y, 2) >= -range)))
	{
		if (canAttack == true)
		{
			enemy->takeDamage(damage);

			//attack enemy object
			canAttack = false;
		}
		
	}
	

}

void GameEntity::move()
{
	this->sprite.move(movingSpeedX,movingSpeedY);
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

sf::Vector2f GameEntity::getPosition()
{
	return this->sprite.getPosition();
}

void GameEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{	
	target.draw(this->sprite);

}

