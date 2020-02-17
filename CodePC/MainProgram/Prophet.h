#pragma once
#include "GameEntity.h"
#include "Follower.h"
class Prophet :
	public GameEntity
{
private:
	int convertingSpeed;
	int chosenGroup;
	int collectedSouls;
	struct group
	{
		int capacity = 20;
		int nrOfFollowers = 0;
		int currentCommand = 0;
		Follower* *followers;
	};
	group group1;
	Prophet* otherProphet;
public:
	Prophet();
	virtual ~Prophet();
	void convert();
	bool checkMovement();
	int getNrOfFollowers();
	void addFollower();
	void collectSouls();
	int getSouls();
	Follower* getFollowers();
	void recieveEnemyProphet(Prophet* other);
};

