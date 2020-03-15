#include "Follow.h"
#include "Follower.h"
#include "Prophet.h"
Follow::Follow()
{
	this->attackProphetBool = false;

}

Follow::~Follow()
{
}

sf::Vector2f Follow::calculateRoute(GameEntity* thisObject, GameEntity* enemyObject, Follower* object)
{
	//if follower destination is inside prophet get a new randomPos
	if ((object->getRandomPos().x + (thisObject->getPosition().x + thisObject->getBounds().width / 2) + (object->getBounds().width / 2) > thisObject->getBounds().left&& object->getRandomPos().x + (thisObject->getPosition().x + thisObject->getBounds().width / 2) - (object->getBounds().width / 2) < thisObject->getBounds().left + thisObject->getBounds().width) && (object->getRandomPos().y + (thisObject->getPosition().y + thisObject->getBounds().height / 2) + (object->getBounds().height / 2) > thisObject->getBounds().top&& object->getRandomPos().y + (thisObject->getPosition().y + thisObject->getBounds().height / 2) - (object->getBounds().height / 2) < thisObject->getBounds().top + thisObject->getBounds().height))
	{

		object->getNewRandomPos(0, true);


	}

	sf::Vector2f dist = thisObject->getPosition() + object->getRandomPos() - object->getPosition();
	float magni = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
	sf::Vector2f dir = sf::Vector2f(dist.x / magni, dist.y / magni);

	float magniTemp = 100000;
	sf::Vector2f attackDist;
	int whichGroup;
	int whichFollower;
	attackProphetBool = true;
	for (int a = 0; a < 3; a++)
	{
		for (int i = 0; i < dynamic_cast<Prophet*>(enemyObject)->getAllNrOfFollowers(a); i++)
		{
			

			if (magniTemp > sqrt(pow(dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i]->getPosition().x - object->getPosition().x, 2) +
				pow(dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i]->getPosition().y - object->getPosition().y, 2)))
			{
				attackDist = dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i]->getPosition() - object->getPosition();
			//	temp = dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i].getPosition() - object->getPosition();
				magniTemp = sqrt(pow(dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i]->getPosition().x - object->getPosition().x, 2) + pow(dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i]->getPosition().y - object->getPosition().y, 2));


				attackProphetBool = false;
				whichFollower = i;
				whichGroup = a;

			}

		}

	}
	if (magniTemp > sqrt(pow((enemyObject)->getPosition().x - object->getPosition().x, 2) +
		pow((enemyObject)->getPosition().y - object->getPosition().y, 2)))
	{
	
		attackDist = (enemyObject)->getPosition() - object->getPosition();
		magniTemp = sqrt(pow((enemyObject)->getPosition().x - object->getPosition().x, 2) + pow((enemyObject)->getPosition().y - object->getPosition().y, 2));
		attackProphetBool = true;

	}

	if (object->getAttackCooldown() && object->getFollowerRange() > magniTemp)
	{
		cout << "can attack " << endl;
			if (attackProphetBool == true)
			{
				enemyObject->takeDamage(object->inflictDamage());
				if (abs(attackDist.x) > abs(attackDist.y))
				{
					if (attackDist.x > 0)
					{
						object->startAnimation((int)FOLLOWERSPRITEROW::HITRIGHT, 6, 15, 1);
					}
					if (attackDist.x < 0)
					{
						object->startAnimation((int)FOLLOWERSPRITEROW::HITLEFT, 6, 15, 1);
					}


				}
				else
				{
					if (attackDist.y > 0)
					{
						object->startAnimation((int)FOLLOWERSPRITEROW::HITDOWN, 6, 15, 1);
					}
					if (attackDist.y < 0)
					{
						object->startAnimation((int)FOLLOWERSPRITEROW::HITUP, 6, 15, 1);
					}
				}

			}
			else
			{
				dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(whichGroup)[whichFollower]->takeDamage(object->inflictDamage());
				if (abs(attackDist.x) > abs(attackDist.y))
				{
					if (attackDist.x > 0)
					{
						object->startAnimation((int)FOLLOWERSPRITEROW::HITRIGHT, 6, 15, 1);
					}
					if (attackDist.x < 0)
					{
						object->startAnimation((int)FOLLOWERSPRITEROW::HITLEFT, 6, 15, 1);
					}


				}
				else
				{
					if (attackDist.y > 0)
					{
						object->startAnimation((int)FOLLOWERSPRITEROW::HITDOWN, 6, 15, 1);
					}
					if (attackDist.y < 0)
					{
						object->startAnimation((int)FOLLOWERSPRITEROW::HITUP, 6, 15, 1);
					}
				}
			}

		

	}

	return dir;
}
