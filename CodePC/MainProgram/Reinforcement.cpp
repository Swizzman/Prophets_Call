#include "Reinforcement.h"

Reinforcement::Reinforcement() : Ability("reinforcement.png", 100,5,5.f)
{
	damageIncrease = 10;
}

Reinforcement::~Reinforcement()
{
}

void Reinforcement::abilityActive()
{
}

int Reinforcement::getSpecificVar()
{
	return damageIncrease;
}

void Reinforcement::placeAbility(sf::Vector2f position)
{
	setPosition(position);
}

