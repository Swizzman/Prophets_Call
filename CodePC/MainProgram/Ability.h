#pragma once
#include <SFML/Graphics.hpp>
#include <string>
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
	bool isActive;
	float pulseTimer;
	bool isDummy;

public:

	Ability(std::string texture, float radius, float activeTimer, float pulseTime, bool fake);
	virtual ~Ability();
	int getRadius();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);
	void turnBoolTrue();
	bool abilityLifeTime();
	bool abilityEffectPulse();
	void resetClock();
	void changeCircleColor(sf::Color color);
	virtual void abilityActive() = 0;
	virtual int getSpecificVar() = 0;
	virtual void placeAbility(sf::Vector2f position) = 0;
	virtual void changeSoundBool(bool soundBool) = 0;
	virtual bool makeSound() = 0;
	bool getDummy() const;



	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
