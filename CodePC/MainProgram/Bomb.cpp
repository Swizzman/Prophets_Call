#include "Bomb.h"

Bomb::Bomb(bool dummy) : Ability("bomb.png", 80, 0.4f,0, dummy)
{
	this->damage = 60;
	activateSound = false;
	soundCounter = 0;

}

Bomb::~Bomb()
{
}



void Bomb::abilityActive()
{
	
}

int Bomb::getSpecificVar()
{
	return damage;
}

void Bomb::placeAbility(sf::Vector2f position)
{
	setPosition(position);
}

bool Bomb::makeSound()
{
	/*	soundCounter++;
	
	if (soundCounter  >= 2)
	{

		cout << "Testing sound bool " << activateSound << endl;
		changeSoundBool(false);
		soundCounter = 0;
	}*/
	
	return activateSound;
}

void Bomb::changeSoundBool(bool soundBool)
{
	activateSound = soundBool;

}
