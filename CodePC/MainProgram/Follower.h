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
	bool alive;
	bool converted;
	bool convertedByOther;
	bool otherNotified;
	bool soulCollected;
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
	float followerRange;
	int lastWalkingDirection;
public:
	Follower();
	virtual ~Follower();
	void increaseDamageDone(int increase);
	void resetDamage();
	void checkCivMove();
	void placeFollower(int width, int height);
	int inflictDamage();
	int getSoulValue() const;
	void setSoulCollected();
	bool getSoulCollected() const;
	void attackCooldown();
	bool getAttackCooldown() const;
	void resetAttackClock();
	void otherIsNotified();
	bool getOtherNotified() const;
	void convert();
	void otherConvert();
	bool getConverted() const;
	bool getConvertedByOther() const;
	int getConvertedAmount()const;
	float getFollowerRange() const;
	bool getIfAlive() const;

	// Inherited via GameEntity
	virtual void die() override;

};

