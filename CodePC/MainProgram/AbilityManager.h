#pragma once
#include "Ability.h"
#include "Bomb.h"
#include "Reinforcement.h"
#include "Regen.h"
class Prophet;
struct group;
class AbilityManager
{
private:
	int chosenAbility;
	Ability* currentAbility;
	group* followerGroup;
	Prophet* enemyProphet;
	Prophet* thisProphet;
	bool abilityActive;
	sf::Clock clock;
	sf::Time timePerFrame;
	sf::Time elapsedTimeSinceLastUpdate;
	bool reinforcementIsOn;
	bool makeASoundBool;
	int soundCounter;
	int cost;
	bool hasPlacedAbility;


public:
	AbilityManager();
	virtual ~AbilityManager();
	int switchAbility();
	int getCurrentAbility();
	int getCurrentRadius();
	bool getAbilityActive() const;
	void startAbility();
	
	void stopAbility();
	void stopReinforceAbility();
	bool returnReinforcementBool();
	void updateAbility(sf::Vector2f placement);
	void placeCurrentAbility(sf::Vector2f position, int force = -1);
	void recievePtr(Prophet* enemyPro, Prophet* thisProphet,group* followerGroup);
	void whileAbilityIsActive();
	bool getActivateSoundBool();
	Ability* getCurrentAbility() const;


};