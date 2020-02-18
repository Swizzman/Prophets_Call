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
	sf::CircleShape convertCirc;
	group *group1;
	Prophet* otherProphet;
	sf::Vector2f getCircCenter() const;
public:
	Prophet();
	virtual ~Prophet();
	void convert(Follower** follArr, int nrOf);
	void convertsFollow();
	bool checkMovement();
	bool checkCollision(sf::FloatRect otherBoundingBox);
	void moveProphet();
	int getNrOfFollowers();
	void addFollower();
	void collectSouls();
	int getSouls();
	Follower* getFollowers();
	void recieveEnemyProphet(Prophet* other);
	int getCurrentAbility();
	void changeAbility();
	sf::CircleShape getConvertCirc() const;
	// Inherited via GameEntity
	virtual void die() override;
};

