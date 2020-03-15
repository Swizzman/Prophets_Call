#include "LowestHP.h"
#include "Prophet.h"
#include "Follower.h"
LowestHP::LowestHP()
{
	this->attackProphetBool = false;
	this->range = 1000;
}

LowestHP::~LowestHP()
{
}

sf::Vector2f LowestHP::calculateRoute(GameEntity* thisObject, GameEntity* enemyObject, Follower* object)
{
	sf::Vector2f temp(0, 0);
	float magniTemp = 100000;
	float health = 100000;
	attackProphetBool = true;
	sf::Vector2f thisEnemy(0,0);
	int whichGroup;
	int whichFollower;
	if (sqrt(pow((enemyObject->getPosition().x + enemyObject->getBounds().width / 2) - (object->getPosition().x + object->getBounds().width / 2), 2) +
		pow((enemyObject->getPosition().y + enemyObject->getBounds().height / 2) - (object->getPosition().y + object->getBounds().height / 2), 2)) > object->getRange())
	{
		object->getNewRandomPos(0, true);

	}
	if ((object->getRandomPos().x + (enemyObject->getPosition().x + enemyObject->getBounds().width / 2) + (object->getBounds().width / 2) > enemyObject->getBounds().left&& object->getRandomPos().x + (enemyObject->getPosition().x + enemyObject->getBounds().width / 2) - (object->getBounds().width / 2) < enemyObject->getBounds().left + enemyObject->getBounds().width) && (object->getRandomPos().y + (enemyObject->getPosition().y + enemyObject->getBounds().height / 2) + (object->getBounds().height / 2) > enemyObject->getBounds().top&& object->getRandomPos().y + (enemyObject->getPosition().y + enemyObject->getBounds().height / 2) - (object->getBounds().height / 2) < enemyObject->getBounds().top + enemyObject->getBounds().height))
	{

		object->getNewRandomPos(0, true);

	}

	for (int a = 0; a < 3; a++)
	{

		for (int i = 0; i < dynamic_cast<Prophet*>(enemyObject)->getAllNrOfFollowers(a); i++)
		{
			thisEnemy = dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i]->getPosition() - object->getPosition();
			if (range > sqrt(pow(thisEnemy.x - object->getPosition().x, 2) + pow(thisEnemy.y - object->getPosition().y, 2)))
			{

				if (health > dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i]->getHealth())
				{
					temp = dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i]->getPosition() - object->getPosition();
					magniTemp = sqrt(pow(temp.x, 2) + pow(temp.y, 2));
					health = dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i]->getHealth();
					attackProphetBool = false;
					whichFollower = i;
					whichGroup = a;
				}
			}



		}
	}
	thisEnemy = (enemyObject)->getPosition() - object->getPosition();
	if (range > sqrt(pow(thisEnemy.x - object->getPosition().x, 2) + pow(thisEnemy.y - object->getPosition().y, 2)))
	{
		if (health > (enemyObject)->getHealth())
		{
			temp = (enemyObject)->getPosition() + object->getRandomPos() - object->getPosition();
			magniTemp = sqrt(pow(temp.x, 2) + pow(temp.y, 2));

			health = dynamic_cast<Prophet*>(enemyObject)->getHealth();
			attackProphetBool = true;
		}

	}

	sf::Vector2f dist = temp;
	float magni = magniTemp;
	sf::Vector2f dir = sf::Vector2f(dist.x / magni, dist.y / magni);
	if (object->getAttackCooldown() && object->getRange() > magni)
	{
		if (attackProphetBool == true)
		{
			enemyObject->takeDamage(object->inflictDamage());
			if (abs(dist.x) > abs(dist.y))
			{
				if (dist.x > 0)
				{
					object->startAnimation((int)FOLLOWERSPRITEROW::HITRIGHT, 6, 15, 1);
				}
				if (dist.x < 0)
				{
					object->startAnimation((int)FOLLOWERSPRITEROW::HITLEFT, 6, 15, 1);
				}


			}
			else
			{
				if (dist.y > 0)
				{
					object->startAnimation((int)FOLLOWERSPRITEROW::HITDOWN, 6, 15, 1);
				}
				if (dist.y < 0)
				{
					object->startAnimation((int)FOLLOWERSPRITEROW::HITUP, 6, 15, 1);
				}
			}

		}
		else
		{
			dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(whichGroup)[whichFollower]->takeDamage(object->inflictDamage());
			if (abs(dist.x) > abs(dist.y))
			{
				if (dist.x > 0)
				{
					object->startAnimation((int)FOLLOWERSPRITEROW::HITRIGHT, 6, 15, 1);
				}
				if (dist.x < 0)
				{
					object->startAnimation((int)FOLLOWERSPRITEROW::HITLEFT, 6, 15, 1);
				}


			}
			else
			{
				if (dist.y > 0)
				{
					object->startAnimation((int)FOLLOWERSPRITEROW::HITDOWN, 6, 15, 1);
				}
				if (dist.y < 0)
				{
					object->startAnimation((int)FOLLOWERSPRITEROW::HITUP, 6, 15, 1);
				}
			}
		}

	}

	return dir;
}
