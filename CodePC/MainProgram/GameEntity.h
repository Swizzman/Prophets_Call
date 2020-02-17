#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
class GameEntity : public sf::Drawable
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	int movingSpeed = 0;
	int health= 0;
	bool canAttack = true;

public:
	GameEntity(string textureName, int movingSpeed, int health);
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
	void move(int x, int y);
	int getMovingSpeed();
	virtual void die() = 0;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

