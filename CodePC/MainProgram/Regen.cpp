#include "Regen.h"

Regen::Regen(bool dummy) :Ability("Regen.png", 100,1, 0.2f, dummy)
{
	this->health = 10;

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


