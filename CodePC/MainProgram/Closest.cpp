#include "Closest.h"
#include "Prophet.h"
#include "Follower.h"

Closest::Closest()
{
	std::cout << "2" << std::endl;
}

Closest::~Closest()
{

}

sf::Vector2f Closest::calculateRoute(GameEntity* thisObject, GameEntity* enemyObject, Follower* object)
{
	//if (sqrt(pow((enemyObject->getPosition().x + enemyObject->getBounds().width / 2) - (object->getPosition().x + object->getBounds().width / 2), 2) +
	//	pow((enemyObject->getPosition().y + enemyObject->getBounds().height / 2) - (object->getPosition().y + object->getBounds().height / 2), 2)) > object->getRange())
	//{
	//	//	cout << "get new random pos" << endl;
	//	object->getNewRandomPos(0, true);

	//}
	//if ((object->getRandomPos().x + (enemyObject->getPosition().x + enemyObject->getBounds().width / 2) + (object->getBounds().width / 2) > enemyObject->getBounds().left&& object->getRandomPos().x + (enemyObject->getPosition().x + enemyObject->getBounds().width / 2) - (object->getBounds().width / 2) < enemyObject->getBounds().left + enemyObject->getBounds().width) && (object->getRandomPos().y + (enemyObject->getPosition().y + enemyObject->getBounds().height / 2) + (object->getBounds().height / 2) > enemyObject->getBounds().top&& object->getRandomPos().y + (enemyObject->getPosition().y + enemyObject->getBounds().height / 2) - (object->getBounds().height / 2) < enemyObject->getBounds().top + enemyObject->getBounds().height))
	//{
	//	//std::cout << object->getRandomPos().x + thisObject->getPosition().x << " : " << object->getRandomPos().y + thisObject->getPosition().y << std::endl;
	//	object->getNewRandomPos(0, true);

	//}
	sf::Vector2f temp(0, 0);
	float magniTemp = 100000;
	int whichGroup;
	int whichFollower;
	attackProphetBool = true;
	for (int a = 0; a < 3; a++)
	{
		for (int i = 0; i <  dynamic_cast<Prophet*>(enemyObject)->getAllNrOfFollowers(a); i++)
		{
			if (magniTemp > sqrt(pow(dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i].getPosition().x - object->getPosition().x, 2) +
				pow(dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i].getPosition().y - object->getPosition().y, 2)))
			{
				temp = dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i].getPosition() - object->getPosition();
				magniTemp = sqrt(pow(temp.x, 2) + pow(temp.y, 2));
					//sqrt(pow(dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i].getPosition().x + object->getRandomPos().x - object->getPosition().x, 2) + pow(dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i].getPosition().y + object->getRandomPos().y - object->getPosition().y, 2));

				//+object->getRandomPos()
				attackProphetBool = false;
				whichFollower = i;
				whichGroup = a;

			}

		

		
		}

	}
		if (magniTemp > sqrt(pow((enemyObject)->getPosition().x - object->getPosition().x, 2) +
			pow((enemyObject)->getPosition().y - object->getPosition().y, 2)))
		{
			temp = (enemyObject)->getPosition() + object->getRandomPos() - object->getPosition();
			magniTemp = sqrt(pow(temp.x, 2) + pow(temp.y, 2));
				//sqrt(pow((enemyObject)->getPosition().x+ object->getRandomPos().x - object->getPosition().x, 2) + pow((enemyObject)->getPosition().y + object->getRandomPos().y - object->getPosition().y, 2));
			attackProphetBool = true;

		}


	/*if ((object->getRandomPos().x + (thisObject->getPosition().x + thisObject->getBounds().width / 2) + (object->getBounds().width / 2) > thisObject->getBounds().left&& object->getRandomPos().x + (thisObject->getPosition().x + thisObject->getBounds().width / 2) - (object->getBounds().width / 2) < thisObject->getBounds().left + thisObject->getBounds().width) && (object->getRandomPos().y + (thisObject->getPosition().y + thisObject->getBounds().height / 2) + (object->getBounds().height / 2) > thisObject->getBounds().top&& object->getRandomPos().y + (thisObject->getPosition().y + thisObject->getBounds().height / 2) - (object->getBounds().height / 2) < thisObject->getBounds().top + thisObject->getBounds().height))
	{
		std::cout << object->getRandomPos().x + thisObject->getPosition().x << " : " << object->getRandomPos().y + thisObject->getPosition().y << std::endl;
		object->getNewRandomPos(0, true);


	}*/
		//cout << magniTemp << endl;
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
			dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(whichGroup)[whichFollower].takeDamage(object->inflictDamage());
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

//GameEntity* Closest::calculateRoute(GameEntity* thisObject, GameEntity** object)
//{
//	return nullptr;
//}
