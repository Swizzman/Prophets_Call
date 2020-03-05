#include "AttackProphet.h"

AttackProphet::AttackProphet()
{
	std::cout << "3" <<std::endl;
}

AttackProphet::~AttackProphet()
{
}

//GameEntity* AttackProphet::calculateRoute(GameEntity* thisObject, GameEntity** object)
//{
//	return nullptr;
//}

sf::Vector2f AttackProphet::calculateRoute(GameEntity* thisObject, GameEntity* enemyObject, GameEntity* object)
{
	if ((object->getRandomPos().x + (thisObject->getPosition().x + thisObject->getBounds().width / 2) + (object->getBounds().width / 2) > thisObject->getBounds().left&& object->getRandomPos().x + (thisObject->getPosition().x + thisObject->getBounds().width / 2) - (object->getBounds().width / 2) < thisObject->getBounds().left + thisObject->getBounds().width) && (object->getRandomPos().y + (thisObject->getPosition().y + thisObject->getBounds().height / 2) + (object->getBounds().height / 2) > thisObject->getBounds().top&& object->getRandomPos().y + (thisObject->getPosition().y + thisObject->getBounds().height / 2) - (object->getBounds().height / 2) < thisObject->getBounds().top + thisObject->getBounds().height))
	{
		//std::cout << object->getRandomPos().x + thisObject->getPosition().x << " : " << object->getRandomPos().y + thisObject->getPosition().y << std::endl;
		object->getNewRandomPos(0, true);


	}
	sf::Vector2f dist = enemyObject->getPosition() + object->getRandomPos() - object->getPosition();
	float magni = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
	sf::Vector2f dir = sf::Vector2f(dist.x / magni, dist.y / magni);
	return dir;
	
}
