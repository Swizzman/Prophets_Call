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
public:
	Follower();
	virtual ~Follower();
	void increaseDamageDone(int increase);
	void returnDamage();
	void checkCivMove();
	void placeFollower(int width, int height);
	void convert(bool force = false);
	bool getConverted() const;
	bool getClientNotified();
	int getConvertedAmount()const;
	void Collided(GameEntity *other);
	// Inherited via GameEntity
	virtual void die() override;
};

