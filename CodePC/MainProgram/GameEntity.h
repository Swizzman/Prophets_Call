#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <ctime>
#include "ANIMATIONSPRITEROW.h"
#include "FOLLOWERSPRITEROW.h"

using namespace std;
class GameEntity : public sf::Drawable
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	int movingSpeedX;
	int movingSpeedY;
	int health;
	bool canAttack;
	bool attackNotify;
	string textureName;
	sf::Vector2f randomPos;
	sf::Time moveTimer;
	sf::Clock clock;
	int maxTime;
	bool collided;
	float range;
	bool abilityHasTakenAffect;
	int maxHealth;
	bool isInRangeOfAbility;
	bool alive;

	int animationTimer;
	int currentColummn;
	int currentRow;
	int frameBeforeNextSpriteFrame;
	bool haveAnimation;
	int currentPriority;
	int lastWalkingDirection;
	float lastYDest;
	float lastXDest;
	int nrOfColumms;

	sf::IntRect textureRect;
	



	//	this->fps[cs[i]->nummberOfFollowersInGroup]->followerImage.setScale(60.f /
		//	followerProfileTexture[b].getSize().x, 60.f / followerProfileTexture[b].getSize().y);


public:
	GameEntity(string textureName, int movingSpeedX, int movingSpeedY, int health, bool isProphet);
	GameEntity();
	virtual  ~GameEntity();

	void takeDamage(int damage);
	sf::Vector2f getPos();
	sf::FloatRect getBounds();
	void switchTexture(std::string newTexture);
	int getHealth();
	void setHealth(int health);
	void gainHealth(int health);
	//void attackCooldown();
	bool getAttackBool();
	bool getAttackNotify() const;
	void otherAttackNotified();
	void attack(GameEntity *enemy, int damage);
	void move();
	void moveTowardsDest(sf::Vector2f dest, int currentCommand);
	void setMovingSpeed(int newSpeedX, int newSpeedY);
	int getMovingSpeedX();
	int getMovingSpeedY();
	void setPosition(float xPos, float yPos);
	void setPosition(sf::Vector2f position);
	string getTextureName();
	sf::Vector2f getPosition();
	sf::Vector2f getOrigin();
	sf::Vector2f getRandomPos();
	virtual void die() = 0;
	void getNewRandomPos(int currentCommand, bool reset);
//	void Collided(GameEntity* other);
	bool getCollidedBool();
	void touchedByAbility(bool abilityIsActive);
	bool CheckIfEntityCanBeAffectedByAbility();
	bool getIfIsInRangeOfAbility(bool IsInRange);
	float getRange();
	void GameEntity::startAnimation(int nrOfRows, int nrOfColumms, int nrOfFramesBeforeNextIntRect, int priority);
	void updateAnimation();
	int getCurrentPriority();
	bool hasAAnimation();
	int getCurrentRow();
	int getCurrentColummn();
	// Inherited via Drawable
	void followerDied();
	bool isAlive();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

