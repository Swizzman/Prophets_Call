#include "Bomb.h"

Bomb::Bomb(bool dummy) : Ability("bomb.png", 80, 1.f,0, dummy)
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
	return activateSound;
}

void Bomb::changeSoundBool(bool soundBool)
{
	activateSound = soundBool;
}
