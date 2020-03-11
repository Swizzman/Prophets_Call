#include "AttackProphet.h"
#include "Follower.h"
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

sf::Vector2f AttackProphet::calculateRoute(GameEntity* thisObject, GameEntity* enemyObject, Follower* object)
{
	if (sqrt(pow((enemyObject->getPosition().x + enemyObject->getBounds().width / 2) - (object->getPosition().x + object->getBounds().width / 2), 2) +
		pow((enemyObject->getPosition().y + enemyObject->getBounds().height / 2) - (object->getPosition().y + object->getBounds().height / 2), 2)) > object->getRange())
	{
	//	cout << "get new random pos" << endl;
		object->getNewRandomPos(0, true);

	}
	if ((object->getRandomPos().x + (enemyObject->getPosition().x + enemyObject->getBounds().width / 2) + (object->getBounds().width / 2) > enemyObject->getBounds().left&& object->getRandomPos().x + (enemyObject->getPosition().x + enemyObject->getBounds().width / 2) - (object->getBounds().width / 2) < enemyObject->getBounds().left + enemyObject->getBounds().width) && (object->getRandomPos().y + (enemyObject->getPosition().y + enemyObject->getBounds().height / 2) + (object->getBounds().height / 2) > enemyObject->getBounds().top&& object->getRandomPos().y + (enemyObject->getPosition().y + enemyObject->getBounds().height / 2) - (object->getBounds().height / 2) < enemyObject->getBounds().top + enemyObject->getBounds().height))
	{
		//std::cout << object->getRandomPos().x + thisObject->getPosition().x << " : " << object->getRandomPos().y + thisObject->getPosition().y << std::endl;
		object->getNewRandomPos(0, true);

	}
	sf::Vector2f dist = enemyObject->getPosition() + object->getRandomPos() - object->getPosition();
	float magni = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
	sf::Vector2f dir = sf::Vector2f(dist.x / magni, dist.y / magni);
	if (object->getAttackCooldown() &&object->getRange() > magni )
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
	return dir;
	
}
