#include "GameEntity.h"

GameEntity::GameEntity(string textureName, int movingSpeed, int health)
{
	this->texture.loadFromFile("../images/" + textureName);
	this->sprite.setTexture(texture);
	this->movingSpeed = movingSpeed;
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

void GameEntity::move(int x, int y)
{
	this->sprite.move(x*movingSpeed,y * movingSpeed);
}

int GameEntity::getMovingSpeed()
{
	return movingSpeed;
}

void GameEntity::setPosition(float x, float y)
{
	this->sprite.setPosition(x, y);
}

void GameEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{	
	target.draw(this->sprite);

}

