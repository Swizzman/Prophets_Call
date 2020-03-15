#pragma once
#include <SFML/Audio.hpp>
#include <string>

class SoundManager
{
private:
	
	sf::SoundBuffer attackBuffer;
	sf::SoundBuffer convertBuffer;
	sf::SoundBuffer bombBuffer;
	sf::SoundBuffer abilityBuffer;
	sf::SoundBuffer deathBuffer;
	sf::SoundBuffer healthRegenBuffer;
	sf::SoundBuffer takingDamageBuffer;
	sf::SoundBuffer reinforceBuffer;
 	sf::Sound** sound;
	int nrOf;

public:
	SoundManager();
	virtual ~SoundManager();
	void attack();
	void convert();
	void bomb();
	void ability();
	void takeDamage();
	void death();
	void healthRegen();
	void reinforce();
	void deleteAudio();
};

