#pragma once
#include "GameEntity.h"
#include "Follower.h"
#include <iostream>

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
	int convertingSpeed;
	int chosenGroup;
	int collectedSouls;
	int moveVertical;
	int moveHorizontal;
	int chosenAbility;
	
	group group1;
	Prophet* otherProphet;
public:
	Prophet();
	virtual ~Prophet();
	void convert();
	bool checkMovement();
	void moveProphet();
	int getNrOfFollowers();
	void addFollower();
	void collectSouls();
	int getSouls();
	Follower* getFollowers();
	void recieveEnemyProphet(Prophet* other);
	int getCurrentAbility();
	void changeAbility();


	// Inherited via GameEntity
	virtual void die() override;
};

