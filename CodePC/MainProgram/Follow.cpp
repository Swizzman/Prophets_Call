#include "Follow.h"

Follow::Follow()
{
	std::cout << "0" << std::endl;

}

Follow::~Follow()
{
}

//sf::Vector2f Follow::calculateVectorRoute(GameEntity* thisObject, GameEntity* enemyObject, GameEntity* object)
//{
//	//sf::Vector2f dist = thisObject->getPosition() - object->getPosition;
//	//float magni = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
//	//sf::Vector2f dir = sf::Vector2f(dist.x / magni, dist.y / magni);
//	////this->sprite.move(dir.x * movingSpeedX, dir.y * movingSpeedY);
//	//return dir;
//}

//GameEntity* Follow::calculateRoute(GameEntity* thisObject, GameEntity** object)
//{
//
//	return nullptr;
//}

sf::Vector2f Follow::calculateRoute(GameEntity* thisObject, GameEntity* enemyObject, GameEntity* object)
{
	//if follower destination is inside prophet get a new randomPos
	if ((object->getRandomPos().x + (thisObject->getPosition().x+thisObject->getBounds().width/2) + (object->getBounds().width/2) > thisObject->getBounds().left&& object->getRandomPos().x + (thisObject->getPosition().x + thisObject->getBounds().width / 2) - (object->getBounds().width / 2) < thisObject->getBounds().left + thisObject->getBounds().width) && (object->getRandomPos().y +( thisObject->getPosition().y + thisObject->getBounds().height / 2) + (object->getBounds().height / 2) > thisObject->getBounds().top&& object->getRandomPos().y + (thisObject->getPosition().y + thisObject->getBounds().height / 2) - (object->getBounds().height / 2) < thisObject->getBounds().top + thisObject->getBounds().height))
	{
		//std::cout << object->getRandomPos().x + thisObject->getPosition().x << " : " << object->getRandomPos().y + thisObject->getPosition().y << std::endl;
		object->getNewRandomPos(0,true);


	}
	sf::Vector2f dist = thisObject->getPosition() + object->getRandomPos() - object->getPosition();
	float magni = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
	sf::Vector2f dir = sf::Vector2f(dist.x / magni, dist.y / magni);
	
	
	return dir;
}
