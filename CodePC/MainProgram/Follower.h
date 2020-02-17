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
	int maxTime;
	int windowWidth;
	int windowHeight;
	sf::Time moveTimer;
	sf::Clock clock;
public:
	Follower();
	virtual ~Follower();
	void increaseDamageDone(int increase);
	void checkCivMove();
	void placeFollower(int width, int height);
	// Inherited via GameEntity
	virtual void die() override;
};

