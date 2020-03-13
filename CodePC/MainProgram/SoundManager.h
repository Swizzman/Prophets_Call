#pragma once
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;
class SoundManager
{
private:
	
 	sf::Sound** sound;
	sf::SoundBuffer attackBuffer;
	sf::SoundBuffer convertBuffer;
	sf::SoundBuffer bombBuffer;
	sf::SoundBuffer abilityBuffer;
	sf::SoundBuffer DeathBuffer;
	sf::SoundBuffer HealthRegenBuffer;
	sf::SoundBuffer takingDamageBuffer;
	sf::SoundBuffer reinforceBuffer;
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

