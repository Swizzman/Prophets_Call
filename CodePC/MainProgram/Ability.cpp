
#include "Ability.h"

Ability::Ability(std::string texture, int radius, float activeTimer ,float pulseTime, bool fake)
{
	this->texture.loadFromFile("../images/" + texture);
	this->sprite.setTexture(this->texture);
	this->hitRadius = radius;
	this->circle.setRadius(radius);
	this->circle.setFillColor(sf::Color::Transparent);
	this->circle.setOutlineColor(sf::Color::Red);
	this->circle.setOutlineThickness(5.f);
	this->activeTime = activeTimer;
	this->pulseTimer = pulseTime;
	this->isActive = false;
	this->isDummy = fake;
	changeCircleColor(sf::Color::Magenta);
	//TimeBetweenAbilityPulse = sf::Time::Zero;
}

Ability::~Ability()
{
}



int Ability::getRadius()
{
	return this->hitRadius;
}

sf::Vector2f Ability::getPosition()
{
	return sprite.getPosition();
}

void Ability::setPosition(sf::Vector2f position)
{
	this->sprite.setPosition(sf::Vector2f(position.x - sprite.getGlobalBounds().width / 2, position.y - 
		sprite.getGlobalBounds().height / 2));
	this->circle.setPosition(sf::Vector2f(position.x - circle.getGlobalBounds().width / 2, position.y - 
		circle.getGlobalBounds().height / 2));
}

void Ability::turnBoolTrue()
{
	 isActive = true;
}

bool Ability::abilityLifeTime()
{
	elapsedTimeSinceLastUpdate += clock.restart();
	if (elapsedTimeSinceLastUpdate.asSeconds() > activeTime)
	{
		//delete[]currentAbility

		
		isActive = false;
		elapsedTimeSinceLastUpdate = sf::Time::Zero;
	}
	else
	{
		isActive = true;
		
	}
	return isActive;
	
}

bool Ability::abilityEffectPulse()
{
	
	TimeBetweenAbilityPulse += abilityClock.restart();

	if (TimeBetweenAbilityPulse.asSeconds() > pulseTimer)
	{
	
		

		TimeBetweenAbilityPulse = sf::Time::Zero;
		return true;
		
	}
	else
	{
		return false;
	}
}

void Ability::turnPulseOff()
{

}

void Ability::resetClock()
{
	abilityClock.restart();
}

void Ability::changeCircleColor(sf::Color color)
{
	circle.setOutlineColor(color);
}

bool Ability::getDummy() const
{
	return isDummy;
}

void Ability::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
	target.draw(this->circle);
}
