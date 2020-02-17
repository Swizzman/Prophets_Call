#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
class GameEntity : public sf::Drawable
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	int movingSpeed;
	int health;
	bool canAttack;

public:
	GameEntity(string textureName, int movingSpeed, int health);
	GameEntity();
	~GameEntity();

	void takeDamage(int damage);
	int getHealth();
	void gainHelth();
	bool attackCooldown();
	void attack(GameEntity *enemy, float range);
	void move(int x, int y);
	int getMovingSpeed();
	virtual void die() = 0;

	//virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;



	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

