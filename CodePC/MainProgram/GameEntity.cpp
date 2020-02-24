#include "GameEntity.h"

GameEntity::GameEntity(string textureName, int movingSpeedX, int movingSpeedY, int health)
{
	this->texture.loadFromFile("../images/" + textureName);
	this->sprite.setTexture(texture);
	this->movingSpeedX = movingSpeedX;
	this->movingSpeedY = movingSpeedY;
	this->health = health;
	this->textureName = textureName;

	
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
	if (sqrt(pow(enemy->getPos().x - sprite.getPosition().x, 2) + pow(enemy->getPos().y - sprite.getPosition().y, 2) <= range &&
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
	this->sprite.move(movingSpeedX, movingSpeedY);
}

void GameEntity::moveTowardsDest(sf::Vector2f dest)
{
	sf::Vector2f dist = dest- getPosition();
	float magni = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
	sf::Vector2f dir = sf::Vector2f(dist.x / magni, dist.y / magni);
	this->sprite.move(dir.x * movingSpeedX, dir.y * movingSpeedY);
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


void GameEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);

}

