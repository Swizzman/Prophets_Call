#pragma once
#include <SFML/Audio.hpp>
class SoundManager
{
private:
	sf::Sound sound;
	sf::SoundBuffer attackBuffer;
	sf::SoundBuffer convertBuffer;
	sf::SoundBuffer bombBuffer;
	sf::SoundBuffer abilityBuffer;

public:
	SoundManager();
	virtual ~SoundManager();

	void attack();
	void convert();
	void bomb();
	void ability();
};

