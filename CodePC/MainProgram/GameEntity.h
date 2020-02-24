#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

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

public:
	GameEntity(string textureName, int movingSpeedX, int movingSpeedY, int health);
	GameEntity();
	~GameEntity();

	void takeDamage(int damage);
	sf::Vector2f getPos();
	sf::FloatRect getBounds();
	void switchTexture(std::string newTexture);
	int getHealth();
	void gainHelth();
	void attackCooldown();
	bool getAttackBool();
	void attack(GameEntity *enemy, float range, int damage);
	void move();
	void moveTowardsDest(sf::Vector2f dest);
	void setMovingSpeed(int newSpeedX, int newSpeedY);
	int getMovingSpeedX();
	int getMovingSpeedY();
	void setPosition(float xPos, float yPos);
	string getTextureName();
	sf::Vector2f getPosition();
	sf::Vector2f getOrigin();
	virtual void die() = 0;
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

