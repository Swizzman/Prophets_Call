#pragma once
#include <SFML/Graphics.hpp>
#include <string>

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

public:
	GameEntity(string textureName, int movingSpeedX, int movingSpeedY, int health);
	GameEntity();
	~GameEntity();

	void takeDamage(int damage);
	sf::Vector2f getPos();
	sf::FloatRect getBounds();

	int getHealth();
	void gainHelth();
	void attackCooldown();
	bool getAttackBool();
	void attack(GameEntity *enemy, float range, int damage);
	void move();
	void setMovingSpeed(int newSpeedX, int newSpeedY);
	int getMovingSpeedX();
	int getMovingSpeedY();
	void setPosition(float xPos, float yPos);
	sf::Vector2f getPosition();
	virtual void die() = 0;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
