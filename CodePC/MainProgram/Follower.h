#pragma once
#include "GameEntity.h"
class Follower :
	public GameEntity
{
private:
	int damage;
	int soulValue;
	float attackRange;
	bool alive;
public:
	Follower();
	virtual ~Follower();
	void increaseDamageDone(int increase);
	void placeFollower(int width, int height);
	// Inherited via GameEntity
	virtual void die() override;
};

