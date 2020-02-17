#include "ControlManager.h"

ControlManager::ControlManager()
{
}

ControlManager::~ControlManager()
{
}

int ControlManager::getMovementInput()
{
	return 0;
}

sf::Vector2f ControlManager::getMousePos()
{
	return sf::Vector2f();
}

sf::Keyboard::Key ControlManager::getKey()
{
	return sf::Keyboard::Key();
}
