
#pragma once
#include "Ability.h"
class Regen :
	public Ability
{
private:
	int health;
	bool activateSound;

public:
	Regen(bool dummy);
	virtual ~Regen();
	// Inherited via Ability
	virtual void abilityActive() override;
	virtual int getSpecificVar() override;
	virtual void placeAbility(sf::Vector2f position) override;

	// Inherited via Ability
	virtual bool makeSound() override;

	// Inherited via Ability
	virtual void changeSoundBool(bool soundBool) override;
};
