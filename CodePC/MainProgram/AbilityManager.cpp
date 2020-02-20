
#include "AbilityManager.h"

#include "Prophet.h"



AbilityManager::AbilityManager()
{
	this->currentAbility = new Bomb();
	this->enemyProphet = nullptr;
	this->followerGroup = nullptr;
	this->chosenAbility = 0;
	this->abilityActive = false;
	std::cout << "Exit from this hellhole\n";
}

AbilityManager::~AbilityManager()
{
	delete currentAbility;
}

int AbilityManager::switchAbility()
{
	delete currentAbility;
	chosenAbility++;
	if (chosenAbility >= 2)
	{
		chosenAbility = 0;
		switch (chosenAbility)
		{
		case 0:
			currentAbility = new Bomb();
			break;
		case 1:
			currentAbility = new Bomb();
			break;
		case 2:
			currentAbility = new Bomb();
			break;
		default:
			break;
		}
	}
	return chosenAbility;

}

int AbilityManager::getCurrentAbility()
{
	return chosenAbility;
}

int AbilityManager::getCurrentRadius()
{
	return currentAbility->getRadius();
}

bool AbilityManager::getAbilityActive() const
{
	return abilityActive;
}

void AbilityManager::startAbility()
{
	abilityActive = true;
	currentAbility->abilityActive();
}

void AbilityManager::stopAbility()
{
	abilityActive = false;
}

void AbilityManager::updateAbility(sf::Vector2f placement)
{
	currentAbility->setPosition(placement);
}

void AbilityManager::placeCurrentAbility(sf::Vector2f position)
{
	currentAbility->placeAbility(position);
}

void AbilityManager::recievePtr(Prophet* enemyPro, group* followerGroup)
{
	enemyProphet = enemyPro;
	this->followerGroup = followerGroup;
}

Ability* AbilityManager::getCurrentAbility() const
{
	return currentAbility;
}

