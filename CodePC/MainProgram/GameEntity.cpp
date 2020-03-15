#include "GameEntity.h"
class Follower;
GameEntity::GameEntity(std::string textureName, int movingSpeedX, int movingSpeedY, int health, bool isProphet)
{
	this->texture.loadFromFile("../images/" + textureName);
	this->sprite.setTexture(texture);
	this->movingSpeedX = movingSpeedX;
	this->movingSpeedY = movingSpeedY;
	this->health = health;
	this->healthLastFrame = health;
	this->maxHealth = health;
	this->textureName = textureName;
	this->animationTimer = 0;
	this->currentColummn = 0;
	this->collided = false;
	this->abilityHasTakenAffect = false;
	this->haveAnimation = isProphet;
	this->currentPriority = 0;
	this->lastWalkingDirection = 5;
	this->alive = true;
	this->lastXDest = 0;
	this->lastYDest = 0;
	this->textureRect = sf::IntRect(0, 0, 64, 64);
	this->sprite.setTextureRect(textureRect);

	this->attackNotify = false;
	this->range = 100;

	this->randomPos = sf::Vector2f(rand() % 300 - 150, rand() % 300 - 150);
	this->maxTime = rand() % 6000 + 2000;
}

GameEntity::GameEntity()
{
	texture.loadFromFile("???");
	this->sprite.setTexture(texture);
	this->movingSpeedX = movingSpeedX;
	this->movingSpeedY = movingSpeedY;
	this->health = health;
	this->healthLastFrame = health;
	this->maxHealth = health;
	this->textureName = textureName;
	this->animationTimer = 0;
	this->currentColummn = 0;
	this->collided = false;
	this->abilityHasTakenAffect = false;
	this->haveAnimation = false;
	this->currentPriority = 0;
	this->lastWalkingDirection = 5;
	this->alive = true;


	this->lastXDest = 0;
	this->lastYDest = 0;

	this->textureRect = sf::IntRect(0, 0, 64, 64);
	this->sprite.setTextureRect(textureRect);

	this->attackNotify = false;
	this->range = 100;

	this->randomPos = sf::Vector2f(rand() % 300 - 150, rand() % 300 - 150);
	this->maxTime = rand() % 6000 + 2000;
}

GameEntity::~GameEntity()
{

}

void GameEntity::takeDamage(int damage)
{

	this->health -= damage;
	if (this->health < 0)
	{
		this->health = 0;
	}
	if (this->health > maxHealth)
	{
		this->health = maxHealth;
	}
	attackNotify = true;

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

void GameEntity::setHealth(int health)
{
	this->health = health;
	if (this->health < 0)
	{
		this->health = 0;
	}
}

void GameEntity::gainHealth(int health)
{
	if (alive)
	{
		if (this->health < maxHealth)
		{
			this->health += health;
		}

		if (this->health >= maxHealth)
		{
			this->health = maxHealth;
		}
		healthLastFrame = this->health;
		attackNotify = true;
	}

}

bool GameEntity::hasLostHealth()
{
	if (healthLastFrame > health)
	{

		healthLastFrame = health;
		return true;
	}
	else if (healthLastFrame <= health)
	{

		return false;
	}

}

bool GameEntity::getAttackBool()
{
	return canAttack;
}

bool GameEntity::getAttackNotify() const
{
	return attackNotify;
}

bool GameEntity::getDeathNotify() const
{
	return deathNotify;
}

void GameEntity::otherDeathNotify()
{
	deathNotify = false;
}

void GameEntity::otherAttackNotified()
{
	attackNotify = false;
}

void GameEntity::move()
{
	if (alive == true)
	{
		this->sprite.move(movingSpeedX, movingSpeedY);
	}
}

void GameEntity::moveTowardsDest(sf::Vector2f dest, int currentCommand)
{
	if (alive == true)
	{
		getNewRandomPos(currentCommand, false);
	
		if ((lastXDest > 0 && dest.x > 0) && getCurrentPriority() <= 0 || (lastXDest < 0 && dest.x < 0) && getCurrentPriority() <= 0)
		{
			if (abs(dest.x) > abs(dest.y) && dest.x > 0.3)
			{
				startAnimation((int)FOLLOWERSPRITEROW::WALKINGRIGHT, 9, 15, 0);
				lastWalkingDirection = (int)FOLLOWERSPRITEROW::WALKINGRIGHT;

			}
			else if (abs(dest.x) > abs(dest.y) && dest.x < -0.5)
			{
				startAnimation((int)FOLLOWERSPRITEROW::WALKINGLEFT, 9, 15, 0);
				lastWalkingDirection = (int)FOLLOWERSPRITEROW::WALKINGLEFT;
			}
			else if (abs(dest.x) < abs(dest.y) && dest.y > 0.5)
			{
				startAnimation((int)FOLLOWERSPRITEROW::WALKINGDOWN, 9, 15, 0);
				lastWalkingDirection = (int)FOLLOWERSPRITEROW::WALKINGDOWN;
			}
			else if (abs(dest.x) < abs(dest.y) && dest.y < -0.5)
			{
				startAnimation((int)FOLLOWERSPRITEROW::WALKINGUP, 9, 15, 0);
				lastWalkingDirection = (int)FOLLOWERSPRITEROW::WALKINGUP;
			}
			if (abs(dest.x) == abs(dest.y) && dest.y < -0.5)
			{
				startAnimation((int)FOLLOWERSPRITEROW::WALKINGUP, 9, 15, 0);
				lastWalkingDirection = (int)FOLLOWERSPRITEROW::WALKINGUP;
			}
			else if (abs(dest.x) == abs(dest.y) && dest.y > 0.5)
			{
				startAnimation((int)FOLLOWERSPRITEROW::WALKINGDOWN, 9, 15, 0);
				lastWalkingDirection = (int)FOLLOWERSPRITEROW::WALKINGDOWN;
			}
		}
		else
		{

			startAnimation(lastWalkingDirection, 1, 15, -1);
		}

		updateAnimation();

		if (getCurrentPriority() <= 0)
		{
			this->sprite.move(dest.x * movingSpeedX, dest.y * movingSpeedY);
			lastXDest = dest.x;
			lastYDest = dest.y;

		}
	}
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

void GameEntity::setPosition(sf::Vector2f position)
{
	this->sprite.setPosition(position);
}

std::string GameEntity::getTextureName() const
{
	return textureName;
}

sf::Vector2f GameEntity::getPosition() const
{
	return this->sprite.getPosition();
}

sf::Vector2f GameEntity::getOrigin() const
{
	return this->sprite.getOrigin();
}

sf::Vector2f GameEntity::getRandomPos() const
{
	return this->randomPos;
}

void GameEntity::getNewRandomPos(int currentCommand, bool reset)
{
	if (alive)
	{
		moveTimer += clock.restart();
		int randomPosRange = 0;

		if (currentCommand == 0)
		{
			randomPosRange = 150;
		}
		else if (currentCommand == 1)
		{
			randomPosRange = 0;
		}
		else if (currentCommand == 2)
		{
			randomPosRange = 0;
		}
		else
		{
			randomPosRange = range;
			randomPosRange *= 2;
		}
		if (reset)
		{
			randomPos = sf::Vector2f(rand() % randomPosRange - randomPosRange / 2, rand() % randomPosRange - randomPosRange / 2);
			moveTimer = sf::Time::Zero;
			maxTime = rand() % 5000 + 2000;
			reset = false;

		}
		if (moveTimer.asMilliseconds() > maxTime&& randomPosRange != 0)
		{
			randomPos = sf::Vector2f(rand() % randomPosRange - randomPosRange / 2, rand() % randomPosRange - randomPosRange / 2);
			moveTimer = sf::Time::Zero;
			maxTime = rand() % 5000 + 2000;
		}

	}
}

bool GameEntity::getCollidedBool() const
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

bool GameEntity::checkIfEntityCanBeAffectedByAbility() const
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

float GameEntity::getRange() const
{
	return range;
}

bool GameEntity::hasAAnimation() const
{
	return haveAnimation;
}

void GameEntity::startAnimation(int nrOfRows, int nrOfColumms, int nrOfFramesBeforeNextIntRect, int priority)
{
	if (alive == true)
	{


		if (priority >= this->currentPriority || (this->currentPriority == 0 && priority == -1))
		{
			if (this->currentRow != nrOfRows || (priority == -1 && this->currentPriority == 0))
			{
				this->textureRect.left = 0;
			}

			this->currentPriority = priority;
			this->currentRow = nrOfRows;
			this->frameBeforeNextSpriteFrame = nrOfFramesBeforeNextIntRect;
			this->nrOfColumms = nrOfColumms;
			updateAnimation();

			if (this->currentRow != nrOfRows)
			{
				this->textureRect.left = 0;
				this->sprite.setTextureRect(textureRect);
			}
			this->currentRow = nrOfRows;
			this->textureRect.top = this->textureRect.height * nrOfRows;


		}
	}
}

void GameEntity::updateAnimation()
{
	if (alive == true)
	{

		this->animationTimer = (this->animationTimer + 1) % frameBeforeNextSpriteFrame;
		if (this->animationTimer == frameBeforeNextSpriteFrame - 1)
		{
			this->currentColummn++;
			this->textureRect.left = (this->textureRect.left + this->textureRect.width) % (int)(nrOfColumms * this->textureRect.width);

		}
		if (currentColummn >= nrOfColumms)
		{
			this->currentPriority = 0;

			this->currentColummn = 0;
		}
		this->sprite.setTextureRect(this->textureRect);

	}
}

int GameEntity::getCurrentPriority() const
{
	return currentPriority;
}

void GameEntity::setAnimation(int column, int row)
{
	if (alive)
	{

		textureRect.left = column * 64;
		textureRect.top = row * 64;
		sprite.setTextureRect(textureRect);
	}
}

int GameEntity::getCurrentRow() const
{
	return currentRow;
}

int GameEntity::getCurrentColummn()const 
{
	return currentColummn;
}

void GameEntity::followerDied()
{
	if (alive == true)
	{
		this->alive = false;
		this->textureRect.left = 0;
		this->textureRect.top = 0;
		this->textureRect.width = 50;
		this->textureRect.height = 71;
		this->sprite.setTextureRect(this->textureRect);
	}
}

bool GameEntity::getAlive() const
{
	return alive;
}

void GameEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(this->sprite);

}

