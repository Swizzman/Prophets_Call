
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using namespace std;
class Ability : public sf::Drawable
{
private:
	int hitRadius;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::CircleShape circle;
	sf::Clock clock;
	sf::Time timePerFrame;
	sf::Time elapsedTimeSinceLastUpdate;
	sf::Clock abilityClock;
	sf::Time TimeBetweenAbilityPulse;
	float activeTime;
	bool isActive = false;
	float pulseTimer;
	

public:

	Ability(std::string texture, int radius, float activeTimer, float pulseTime);
	virtual ~Ability();
	int getRadius();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);
	void turnBoolTrue();
	bool abilityLifeTime();
	bool abilityEffectPulse();
	void turnPulseOff();
	void resetClock();
	void changeCircleColor(sf::Color color);
	virtual void abilityActive() = 0;
	virtual int getSpecificVar() = 0;
	virtual void placeAbility(sf::Vector2f position) = 0;




	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
