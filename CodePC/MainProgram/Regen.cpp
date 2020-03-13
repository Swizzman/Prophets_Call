#include "Regen.h"

Regen::Regen(bool dummy) :Ability("Regen.png", 100, 2.11f, 0.7f, dummy)
{
	this->health = 15;
	activateSound = false;

}

Regen::~Regen()
{
}

void Regen::abilityActive()
{
	/*if (abilityEffectPulse(0.2f))
	{
		cout << "asdasd" << endl;
		
	}*/
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
	//changeSoundBool(false);
	//cout << "Testing sound bool " << activateSound << endl;
}

void Regen::changeSoundBool(bool soundBool)
{
	activateSound = soundBool;
}


