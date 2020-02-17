#include "SoundManager.h"

SoundManager::SoundManager()
{
	attackBuffer.loadFromFile("../Sounds/attack.wav");
	abilityBuffer.loadFromFile("../Sounds/ability.wav");
	convertBuffer.loadFromFile("../Sounds/convert.wav");
	bombBuffer.loadFromFile("../Sounds/bomb.wav");
	sound.setBuffer(attackBuffer);
}

SoundManager::~SoundManager()
{
}

void SoundManager::attack()
{
	sound.setBuffer(attackBuffer);
	sound.play();
}

void SoundManager::convert()
{
	sound.setBuffer(convertBuffer);
	sound.play();
}

void SoundManager::bomb()
{
	sound.setBuffer(bombBuffer);
	sound.play();
}

void SoundManager::ability()
{
	sound.setBuffer(abilityBuffer);
	sound.play();
}
