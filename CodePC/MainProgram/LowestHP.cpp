#include "LowestHP.h"
#include "Prophet.h"
#include "Follower.h"
LowestHP::LowestHP()
{
	std::cout << "1" << std::endl;
	enemysNotInRange = true;
	tempDist = sf::Vector2f(0, 0);
	magniTemp = 100000;
	health = 100000;
	attackProphetBool = true;
	enemysNotInRange = true;
	thisEnemy = sf::Vector2f(0, 0);
	whichGroup = 0;
	whichFollower = 0;
}

LowestHP::~LowestHP()
{
}
//
//GameEntity* LowestHP::calculateRoute(GameEntity* thisObject, GameEntity** object)
//{
//	return nullptr;
//}

sf::Vector2f LowestHP::calculateRoute(GameEntity* thisObject, GameEntity* enemyObject, Follower* object)
{
	tempDist = sf::Vector2f(0, 0);
	magniTemp = 100000;
	health = 100000;
	attackProphetBool = true;
	enemysNotInRange = true;
	thisEnemy = sf::Vector2f(0,0);
	whichGroup;
	whichFollower;
	if (sqrt(pow((enemyObject->getPosition().x + enemyObject->getBounds().width / 2) - (object->getPosition().x + object->getBounds().width / 2), 2) +
		pow((enemyObject->getPosition().y + enemyObject->getBounds().height / 2) - (object->getPosition().y + object->getBounds().height / 2), 2)) > object->getRange())
	{
		//	cout << "get new random pos" << endl;
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
			if (range > sqrt(pow(thisEnemy.x , 2) + pow(thisEnemy.y , 2)))
			{

				if (health > dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i]->getHealth() && dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i]->getHealth() > 0)
				{
					tempDist = dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i]->getPosition() - object->getPosition();
					magniTemp = sqrt(pow(tempDist.x, 2) + pow(tempDist.y, 2));
						//sqrt(pow(dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i]->getPosition().x - object->getPosition().x, 2) + pow(dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i]->getPosition().y - object->getPosition().y, 2));
					attackProphetBool = false;
					whichFollower = i;
					whichGroup = a;
					health = dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i]->getHealth();
				}
			}
			//+object->getRandomPos()



		}
	}
	thisEnemy = (enemyObject)->getPosition() - object->getPosition();
	if (range > sqrt(pow(thisEnemy.x , 2) + pow(thisEnemy.y, 2)))
	{
		if (health > (enemyObject)->getHealth() && (enemyObject)->getHealth() > 0)
		{
			tempDist = (enemyObject)->getPosition() + object->getRandomPos() -object->getPosition();

			magniTemp = sqrt(pow(tempDist.x, 2) + pow(tempDist.y, 2));
			
				//sqrt(pow((enemyObject)->getPosition().x - object->getPosition().x, 2) + pow((enemyObject)->getPosition().y - object->getPosition().y, 2));
			attackProphetBool = true;
			health = dynamic_cast<Prophet*>(enemyObject)->getHealth();
		}

	}



	sf::Vector2f dist;
	float magni;

	if (tempDist != sf::Vector2f(0,0))
	{
	 enemysNotInRange = false;
	 dist = tempDist;
	 magni = magniTemp;
	 

	}
	else
	{
		enemysNotInRange = true;
		dist = thisObject->getPosition() + object->getRandomPos() - object->getPosition();
		magni = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
	}
	sf::Vector2f dir = sf::Vector2f(dist.x / magni, dist.y / magni);
	if (object->getAttackCooldown() && object->getRange() > magni && enemysNotInRange == false)
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
	
	
	//cout << dist.x << " : " << dist.y << endl;

	return dir;
}
