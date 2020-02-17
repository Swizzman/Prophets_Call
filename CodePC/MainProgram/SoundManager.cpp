#include "SoundManager.h"

SoundManager::SoundManager()
{
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
