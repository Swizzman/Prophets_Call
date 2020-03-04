#include "Closest.h"
#include "Prophet.h"


Closest::Closest()
{
	std::cout << "2" << std::endl;
}

Closest::~Closest()
{

}

sf::Vector2f Closest::calculateRoute(GameEntity* thisObject, GameEntity* enemyObject, GameEntity* object)
{

	sf::Vector2f temp(0, 0);
	float magniTemp = 100000;
	
		for (int i = 0; i <  dynamic_cast<Prophet*>(enemyObject)->getNrOfFollowers(); i++)
		{
			if (magniTemp > sqrt(pow(dynamic_cast<Prophet*>(enemyObject)->getASingleFollower(i).getPosition().x - object->getPosition().x, 2) +
				pow(dynamic_cast<Prophet*>(enemyObject)->getASingleFollower(i).getPosition().y - object->getPosition().y, 2)))
			{
				temp = dynamic_cast<Prophet*>(enemyObject)->getASingleFollower(i).getPosition() - object->getPosition();
				magniTemp = sqrt(pow(dynamic_cast<Prophet*>(enemyObject)->getASingleFollower(i).getPosition().x - object->getPosition().x, 2) + pow(dynamic_cast<Prophet*>(enemyObject)->getASingleFollower(i).getPosition().y - object->getPosition().y, 2));

			


			}

		

		
		}
		if (magniTemp > sqrt(pow((enemyObject)->getPosition().x - object->getPosition().x, 2) +
			pow((enemyObject)->getPosition().y - object->getPosition().y, 2)))
		{
			temp = (enemyObject)->getPosition() - object->getPosition();
			magniTemp = sqrt(pow((enemyObject)->getPosition().x - object->getPosition().x, 2) + pow((enemyObject)->getPosition().y - object->getPosition().y, 2));


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

//GameEntity* Closest::calculateRoute(GameEntity* thisObject, GameEntity** object)
//{
//	return nullptr;
//}
