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
	Follower** temp;



	AbilityManager abilityMan;
	CommandManager commandMan;
	sf::Mouse abilityMouse;
	bool abilityActive;
	sf::Vector2f getCircCenter() const;
	int currentCommandGroup;
	int nrOfCivs;

	bool abilityAnimation;
	int lastWalkingDirection;
public:
	Prophet();
	virtual ~Prophet();
	void convert(Follower** follArr, int nrOf);
	void convertsFollow();
	void resetClock();
	bool checkMovement();
	bool checkCollision(sf::FloatRect otherBoundingBox);
	void moveProphet();
	int getNrOfFollowers();
	int getAllNrOfFollowers(int thisGroup);
	void collectSouls();
	void placeAbil(sf::Vector2f position,int force = -1);
	int getSouls();
	Follower** getFollowers();
	Follower& getASingleFollower(int whichOne);
	Follower** getAllFollowers(int thisGroup);
	void recieveEnemyProphet(Prophet* other);
	int getCurrentAbility();
	void changeAbility();
	void checkAbility();
	sf::CircleShape getConvertCirc() const;
	void changeCurrentCommandGroup();
	int getcurrentGroupCommand();
	Ability* getCurAbil() const;
	void aFollowerGotKilled(int whichFollower);
	void changeCurrentCommand();
	bool getIfAbilityIsActive();
	void timerForAbility();
	void endingReinforcementAbility();
	bool returnReinforceBool();
	int getWalkingDirection();
	int getCurrentGroup();


	void addFollower(Follower* follower);
	void removeFollower(Follower* follower);
	// Inherited via GameEntity
	virtual void die() override;

};

