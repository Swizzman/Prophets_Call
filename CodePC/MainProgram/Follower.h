#pragma once
#include "GameEntity.h"
class Follower :
	public GameEntity
{
private:
	int damage;
	int startDamage;
	int soulValue;
	float attackRange;
	bool alive;
	bool converted;
	bool collided;
	int maxTime;
	int windowWidth;
	int windowHeight;
	int convertedAmount;
	sf::Time moveTimer;
	sf::Clock clock;
	sf::Clock attackClock;
	sf::Time attackTime;
	bool canAttack;
	float attackCooldownTime;
	float followerRange = 100;
	int test;
public:
	Follower();
	virtual ~Follower();
	void increaseDamageDone(int increase);
	void returnDamage();
	void checkCivMove();
	void placeFollower(int width, int height);
	int inflictDamage();
	void attackCooldown();
	bool getAttackCooldown();
	void resetAttackClock();
	void convert();
	bool getConverted() const;
	int getConvertedAmount()const;
	void Collided(GameEntity *other);
	float getFollowerRange();
	// Inherited via GameEntity
	virtual void die() override;
};

