#include "Regen.h"

Regen::Regen(bool dummy) :Ability("Regen.png", 100, 2.11f, 0.7f, dummy)
{
	this->health = 15;
	this->activateSound = false;

}

Regen::~Regen()
{
}

void Regen::abilityActive()
{

}

int Regen::getSpecificVar()
{

	return health;

}

void Regen::placeAbility(sf::Vector2f position)
{
	setPosition(position);
}

bool Regen::makeSound()
{

	return activateSound;
}

void Regen::changeSoundBool(bool soundBool)
{
	activateSound = soundBool;
}


