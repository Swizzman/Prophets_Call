
#pragma once
#include "Ability.h"
class Regen :
	public Ability
{
private:
	int health;

public:
	Regen(bool dummy);
	virtual ~Regen();
	// Inherited via Ability
	virtual void abilityActive() override;
	virtual int getSpecificVar() override;
	virtual void placeAbility(sf::Vector2f position) override;
};
