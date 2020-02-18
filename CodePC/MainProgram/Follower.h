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
	bool converted;
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
	void convert();
	bool getConverted() const;
	// Inherited via GameEntity
	virtual void die() override;
};

