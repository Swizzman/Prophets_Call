#pragma once
#include "GameEntity.h"
#include "Follower.h"
#include <iostream>
#include "AbilityManager.h"
#include "Ability.h"
#include "Commands.h"
#include "CommandManager.h"
#include "ANIMATIONSPRITEROW.h"
#include "FOLLOWERSPRITEROW.h"

struct group
{
	int capacity;
	int nrOfFollowers;
	int currentCommand;
	Follower** followers;
};
class Prophet :
	public GameEntity

{
private:
	static const int GROUPNR = 3;

	int convertingSpeed;
	int chosenGroup;
	int collectedSouls;
	int xSpeed;
	int ySpeed;
	int chosenAbility;
	int convertingTimeMax;
	sf::CircleShape convertCirc;
	sf::Time convertingTime;
	sf::Clock clock;
	group group[GROUPNR];
	Prophet* otherProphet;



	AbilityManager abilityMan;
	CommandManager commandMan;
	sf::Mouse abilityMouse;
	bool abilityActive;
	int currentCommandGroup;

	bool abilityAnimation;
	int lastWalkingDirection;
	sf::Vector2f getCircCenter() const;
public:
	Prophet();
	virtual ~Prophet();
	void convert(Follower** follArr, int nrOf);
	void convertsFollow();
	void resetClock();
	bool checkCollision(sf::FloatRect otherBoundingBox);
	void moveProphet();
	int getNrOfFollowers();
	int getAllNrOfFollowers(int thisGroup);
	void collectSouls(Follower* follower);
	void placeAbil(sf::Vector2f position,int force = -1);
	int getSouls() const;
	void decreaseSouls(int amount);
	Follower* getFollowers() const;
	Follower& getASingleFollower(int whichOne) const;
	Follower** getAllFollowers(int thisGroup) const;
	void recieveEnemyProphet(Prophet* other);
	int getCurrentAbility() const;
	void changeAbility();
	sf::CircleShape getConvertCirc() const;
	void changeCurrentCommandGroup();
	int getCurrentGroupCommand();
	Ability* getCurAbil() const;
	bool getIfSoundBoolIsActive() ;
	void changeCurrentCommand();
	bool getIfAbilityIsActive();
	void timerForAbility();
	void endingReinforcementAbility();
	bool returnReinforceBool();
	int getWalkingDirection() const;
	int getCurrentGroup() const;


	void addFollower(Follower* follower);
	void removeFollower(Follower* follower);
	// Inherited via GameEntity
	virtual void die() override;

};

