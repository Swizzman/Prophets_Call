#include "GameEntity.h"
class Follower;
GameEntity::GameEntity(string textureName, int movingSpeedX, int movingSpeedY, int health, bool isProphet)
{
	this->texture.loadFromFile("../images/" + textureName);
	this->sprite.setTexture(texture);
	this->movingSpeedX = movingSpeedX;
	this->movingSpeedY = movingSpeedY;
	this->health = health;
	this->maxHealth = health;
	this->textureName = textureName;
	this->animationTimer = 0;
	this->currentColummn = 0;
	collided = false;
	abilityHasTakenAffect = false;
	this->haveAnimation = isProphet;
	this->currentPriority = 0;
	lastWalkingDirection = 5;


	lastXDest = 0;
	lastYDest = 0;
	//	this->fps[cs[i]->nummberOfFollowersInGroup]->followerImage.setScale(60.f /
	//	followerProfileTexture[b].getSize().x, 60.f / followerProfileTexture[b].getSize().y);
	textureRect = sf::IntRect(0, 0, 64, 64);
	this->sprite.setTextureRect(textureRect);

	attackNotify = false;
	range = 100;

	randomPos = sf::Vector2f(rand() % 300 - 150, rand() % 300 - 150);
	maxTime = rand() % 6000 + 2000;
}

GameEntity::GameEntity()
{
	texture.loadFromFile("???");
	this->sprite.setTexture(texture);
	this->movingSpeedX = 0;
	this->movingSpeedY = 0;
	this->health = 0;
	this->maxHealth = 0;
	collided = false;
	abilityHasTakenAffect = false;
	range = 100;

	randomPos = sf::Vector2f(rand() % 300 - 150, rand() % 300 - 150);
	maxTime = rand() % 6000 + 2000;
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

void GameEntity::setHealth(int health)
{
	this->health = health;
}

void GameEntity::gainHealth(int health)
{
	if (this->health < maxHealth)
	{
		this->health += health;
	}

	if (this->health >= maxHealth)
	{
		this->health = maxHealth;
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

void GameEntity::otherAttackNotified()
{
	attackNotify = false;
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
	if ((lastXDest > 0 && dest.x > 0) || (lastXDest < 0 && dest.x < 0))
	{


		if (abs(dest.x) > abs(dest.y) && dest.x > 0.3)
		{
			startAnimation((int)FOLLOWERSPRITEROW::WALKINGRIGHT, 9, 15, 0);
			lastWalkingDirection = (int)FOLLOWERSPRITEROW::WALKINGRIGHT;
			//cout << abs(this->getMovingSpeedX()) << " : " << abs(this->getMovingSpeedY()) << endl;
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
			//	cout << "same walking speed " << endl;
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
		//	cout << "(" << dest.x << lastXDest << ") : (" << dest.y << lastYDest << ")" << endl;


	}



	/*if ((abs(dest.x) < 0.5f && abs(dest.y) < 0.5f) || (-lastXDest == dest.x || -lastYDest == dest.y))
	{
		startAnimation(lastWalkingDirection, 1, 15, -1);

	cout << "(" << dest.x  << ") : (" << dest.y  << ")" << endl;
	}*/

	updateAnimation();

	if (getCurrentPriority() <= 0)
	{
		this->sprite.move(dest.x * movingSpeedX, dest.y * movingSpeedY);
		lastXDest = dest.x;
		lastYDest = dest.y;

	}

}

void GameEntity::setMovingSpeed(int newSpeedX, int newSpeedY)
{
	this->movingSpeedX = newSpeedX;
	this->movingSpeedY = newSpeedY;

	/*if (movingSpeedY > 1)
	{
		updateAnimation();
	}*/

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
		//float xRPos = rand() % 250 - dynamic_cast<class Prophet>(this->)
		randomPos = sf::Vector2f(rand() % randomPosRange - randomPosRange / 2, rand() % randomPosRange - randomPosRange / 2);
		moveTimer = sf::Time::Zero;
		maxTime = rand() % 5000 + 2000;
		reset = false;

	}
	if (moveTimer.asMilliseconds() > maxTime&& randomPosRange != 0)
	{
		//float xRPos = rand() % 250 - dynamic_cast<class Prophet>(this->)
		randomPos = sf::Vector2f(rand() % randomPosRange - randomPosRange / 2, rand() % randomPosRange - randomPosRange / 2);
		moveTimer = sf::Time::Zero;
		maxTime = rand() % 5000 + 2000;


	}


}

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

bool GameEntity::hasAAnimation()
{
	return haveAnimation;
}

void GameEntity::startAnimation(int nrOfRows, int nrOfColumms, int nrOfFramesBeforeNextIntRect, int priority)
{

	if (priority >= this->currentPriority || (currentPriority == 0 && priority == -1))
	{
		if (currentRow != nrOfRows || (priority == -1 && currentPriority == 0))
		{
			textureRect.left = 0;
		}

		currentPriority = priority;
		currentRow = nrOfRows;
		frameBeforeNextSpriteFrame = nrOfFramesBeforeNextIntRect;
		//currentColummn = 0;
		this->nrOfColumms = nrOfColumms;
		updateAnimation();

		if (currentRow != nrOfRows)
		{
			this->textureRect.left = 0;
			this->sprite.setTextureRect(textureRect);
		}
		currentRow = nrOfRows;
		this->textureRect.top = this->textureRect.height * nrOfRows;


	}

}

void GameEntity::updateAnimation()
{


	this->animationTimer = (this->animationTimer + 1) % frameBeforeNextSpriteFrame;
	if (this->animationTimer == frameBeforeNextSpriteFrame - 1)
	{
		currentColummn++;
		this->textureRect.left = (this->textureRect.left + this->textureRect.width) % (int)(nrOfColumms * this->textureRect.width);

	}
	if (currentColummn >= nrOfColumms)
	{
		currentPriority = 0;

		currentColummn = 0;
	}
	this->sprite.setTextureRect(this->textureRect);


}

int GameEntity::getCurrentPriority()
{
	return currentPriority;
}

void GameEntity::setAnimation(int column, int row)
{
	textureRect.left = column * 64;
	textureRect.top = row * 64;
	sprite.setTextureRect(textureRect);
}

int GameEntity::getCurrentRow()
{
	return currentRow;
}

int GameEntity::getCurrentColummn()
{
	return currentColummn;
}




void GameEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);

}

