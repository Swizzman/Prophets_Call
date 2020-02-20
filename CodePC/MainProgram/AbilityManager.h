#pragma once
#include "Ability.h"
#include "Bomb.h"
#include "Reinforcement.h"
#include "Regen.h"
#include <iostream>
class Prophet;
struct group;
class AbilityManager
{
private:
	int chosenAbility;
	Ability* currentAbility;
	group* followerGroup;
	Prophet* enemyProphet;
	bool abilityActive;

public:
	AbilityManager();
	virtual ~AbilityManager();
	int switchAbility();
	int getCurrentAbility();
	int getCurrentRadius();
	bool getAbilityActive() const;
	void startAbility();
	void stopAbility();
	void updateAbility(sf::Vector2f placement);
	void placeCurrentAbility(sf::Vector2f position);
	void recievePtr(Prophet* enemyPro, group* followerGroup);
	Ability* getCurrentAbility() const;


};