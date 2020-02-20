
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class Ability : public sf::Drawable
{
private:
	int hitRadius;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::CircleShape circle;

public:

	Ability(std::string texture, int radius);
	~Ability();
	int getRadius();
	void setPosition(sf::Vector2f position);
	virtual void abilityActive() = 0;
	virtual int getSpecificVar() = 0;
	virtual void placeAbility(sf::Vector2f position) = 0;




	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
