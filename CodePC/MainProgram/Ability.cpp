
#include "Ability.h"

Ability::Ability(std::string texture, int radius)
{
	this->texture.loadFromFile("../images/" + texture);
	this->sprite.setTexture(this->texture);
	this->hitRadius = radius;
	this->circle.setRadius(radius);
	this->circle.setFillColor(sf::Color::Transparent);
	this->circle.setOutlineColor(sf::Color::Red);
	this->circle.setOutlineThickness(5.f);
}

Ability::~Ability()
{
}



int Ability::getRadius()
{
	return this->hitRadius;
}

void Ability::setPosition(sf::Vector2f position)
{
	this->sprite.setPosition(sf::Vector2f(position.x - sprite.getGlobalBounds().width / 2, position.y - 
		sprite.getGlobalBounds().height / 2));
	this->circle.setPosition(sf::Vector2f(position.x - circle.getGlobalBounds().width / 2, position.y - 
		circle.getGlobalBounds().height / 2));
}

void Ability::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
	target.draw(this->circle);
}
