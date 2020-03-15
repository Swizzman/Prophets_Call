#include "Reinforcement.h"

Reinforcement::Reinforcement(bool dummy) : Ability("reinforcement.png", 100,5,5.f, dummy)
{
	this->damageIncrease = 10;
	this->activateSound = false;
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

bool Reinforcement::makeSound()
{
	return activateSound;
}

void Reinforcement::changeSoundBool(bool soundBool)
{
	activateSound = soundBool;

}

