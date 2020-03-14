#include "Reinforcement.h"

Reinforcement::Reinforcement(bool dummy) : Ability("reinforcement.png", 100,5,5.f, dummy)
{
	damageIncrease = 10;
	activateSound = false;
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
	//changeSoundBool(false);
	cout << "Testing sound bool " << activateSound << endl;
}

void Reinforcement::changeSoundBool(bool soundBool)
{
	activateSound = soundBool;

}

