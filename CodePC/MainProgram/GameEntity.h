#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <ctime>
#include "ANIMATIONSPRITEROW.h"
#include "FOLLOWERSPRITEROW.h"


class GameEntity : public sf::Drawable
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	int movingSpeedX;
	int movingSpeedY;
	int health;
	int healthLastFrame;
	bool canAttack;
	bool attackNotify;
	std::string textureName;
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
	bool deathNotify;
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

public:
	GameEntity(std::string textureName, int movingSpeedX, int movingSpeedY, int health, bool isProphet);
	GameEntity();
	virtual  ~GameEntity();

	void takeDamage(int damage);
	
	sf::FloatRect getBounds();
	void switchTexture(std::string newTexture);
	int getHealth();
	void setHealth(int health);
	void gainHealth(int health);
	bool hasLostHealth();
	bool getAttackBool();
	bool getAttackNotify() const;
	bool getDeathNotify() const;
	void otherDeathNotify();
	void otherAttackNotified();
	void move();
	void moveTowardsDest(sf::Vector2f dest, int currentCommand);
	void setMovingSpeed(int newSpeedX, int newSpeedY);
	int getMovingSpeedX();
	int getMovingSpeedY();
	void setPosition(float xPos, float yPos);
	void setPosition(sf::Vector2f position);
	std::string getTextureName() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getOrigin() const;
	sf::Vector2f getRandomPos() const;
	virtual void die() = 0;
	void getNewRandomPos(int currentCommand, bool reset);
	bool getCollidedBool() const;
	void touchedByAbility(bool abilityIsActive);
	bool checkIfEntityCanBeAffectedByAbility() const;
	bool getIfIsInRangeOfAbility(bool IsInRange);
	float getRange() const;
	void startAnimation(int nrOfRows, int nrOfColumms, int nrOfFramesBeforeNextIntRect, int priority);
	void updateAnimation();
	int getCurrentPriority() const;
	void setAnimation(int column, int row);
	bool hasAAnimation() const;
	int getCurrentRow() const;
	int getCurrentColummn() const;
	// Inherited via Drawable
	void followerDied();
	bool getAlive()const ;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

