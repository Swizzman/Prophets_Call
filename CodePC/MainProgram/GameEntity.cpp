#include "GameEntity.h"

GameEntity::GameEntity()
{
}

GameEntity::~GameEntity()
{
}

void GameEntity::takeDamage(int damage)
{
}

int GameEntity::getHealth()
{
	return 0;
}

void GameEntity::gainHelth()
{
}


bool GameEntity::attackCooldown()
{
	return false;
}

void GameEntity::attack(GameEntity* enemy, float range)
{
}

void GameEntity::move(int x, int y)
{
}

int GameEntity::getMovingSpeed()
{
	return 0;
}

void GameEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

