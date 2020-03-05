#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <ctime>

using namespace std;
class GameEntity : public sf::Drawable
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	int movingSpeedX;
	int movingSpeedY;
	int health;
	bool canAttack = true;
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


public:
	GameEntity(string textureName, int movingSpeedX, int movingSpeedY, int health);
	GameEntity();
	virtual  ~GameEntity();

	void takeDamage(int damage);
	sf::Vector2f getPos();
	sf::FloatRect getBounds();
	void switchTexture(std::string newTexture);
	int getHealth();
	void gainHealth(int health);
	//void attackCooldown();
	bool getAttackBool();
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

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

