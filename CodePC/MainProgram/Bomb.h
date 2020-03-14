#pragma once
#include "Ability.h"
class Bomb :
	public Ability
{
private:
	int damage;
	bool activateSound;
	int soundCounter;
	
public:
	Bomb(bool dummy);
	virtual ~Bomb();
	// Inherited via Ability
	virtual void abilityActive() override;
	virtual int getSpecificVar() override;
	virtual void placeAbility(sf::Vector2f position) override;

	// Inherited via Ability
	virtual bool makeSound() override;

	// Inherited via Ability
	virtual void changeSoundBool(bool soundBool) override;
};

