#pragma once
#include "GameEntity.h"
#include "FOLLOWERSPRITEROW.h"
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
	bool convertedByOther;
	bool otherNotified;
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

	int lastWalkingDirection;
//	sf::IntRect textureRect;
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
	void otherIsNotified();
	bool getOtherNotified() const;
	void convert();
	void otherConvert();
	bool getConverted() const;
	bool getConvertedByOther() const;
	int getConvertedAmount()const;
	void Collided(GameEntity *other);
	float getFollowerRange();


	// Inherited via GameEntity
	virtual void die() override;
};

