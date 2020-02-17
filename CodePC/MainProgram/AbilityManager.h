#pragma once
#include "Bomb.h"
#include "Reinforcement.h"
#include "Regen.h"
#include "Prophet.h"

class AbilityManager
{
private:
	int chosenAbility;
	Ability *currentAbility;
	group* followerGroup;
	Prophet* enemyProphet;

public:
	AbilityManager();
	~AbilityManager();
	void switchAbility();
	int getCurrentAbility();
	int getRadius();
	void placeAbility(sf::Vector2f position);
	void recievePtr(Prophet* enemyPro, group followerGroup);


};

