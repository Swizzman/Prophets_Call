#include "LowestHP.h"
#include "Prophet.h"

LowestHP::LowestHP()
{
	std::cout << "1" << std::endl;
}

LowestHP::~LowestHP()
{
}
//
//GameEntity* LowestHP::calculateRoute(GameEntity* thisObject, GameEntity** object)
//{
//	return nullptr;
//}

sf::Vector2f LowestHP::calculateRoute(GameEntity* thisObject, GameEntity* enemyObject, GameEntity* object)
{
	sf::Vector2f temp(0, 0);
	float magniTemp = 100000;
	float health = 100000;
	sf::Vector2f thisEnemy(0,0);
	for (int a = 0; a < 3; a++)
	{

		for (int i = 0; i < dynamic_cast<Prophet*>(enemyObject)->getAllNrOfFollowers(a); i++)
		{
			thisEnemy = dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i].getPosition() - object->getPosition();
			if (range > sqrt(pow(thisEnemy.x - object->getPosition().x, 2) + pow(thisEnemy.y - object->getPosition().y, 2)))
			{

				if (health > dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i].getHealth())
				{
					temp = dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i].getPosition() - object->getPosition();
					magniTemp = sqrt(pow(dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i].getPosition().x - object->getPosition().x, 2) + pow(dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i].getPosition().y - object->getPosition().y, 2));
					health = dynamic_cast<Prophet*>(enemyObject)->getAllFollowers(a)[i].getHealth();
				}
			}




		}
	}
	thisEnemy = (enemyObject)->getPosition() - object->getPosition();
	if (range > sqrt(pow(thisEnemy.x - object->getPosition().x, 2) + pow(thisEnemy.y - object->getPosition().y, 2)))
	{
		if (health > (enemyObject)->getHealth())
		{
			temp = (enemyObject)->getPosition() - object->getPosition();
			magniTemp = sqrt(pow((enemyObject)->getPosition().x - object->getPosition().x, 2) + pow((enemyObject)->getPosition().y - object->getPosition().y, 2));
			health = dynamic_cast<Prophet*>(enemyObject)->getHealth();

		}

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

	//cout << dist.x << " : " << dist.y << endl;

	return dir;
}
