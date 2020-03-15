#include "SoundManager.h"

SoundManager::SoundManager()
{
	this->attackBuffer.loadFromFile("../Sounds/attack.wav");
	this->abilityBuffer.loadFromFile("../Sounds/ability.wav");
	this->convertBuffer.loadFromFile("../Sounds/convert.wav");
	this->bombBuffer.loadFromFile("../Sounds/bomb.wav");
	this->deathBuffer.loadFromFile("../Sounds/death.wav");
	this->healthRegenBuffer.loadFromFile("../Sounds/HealthRegen.wav");
	this->takingDamageBuffer.loadFromFile("../Sounds/hurt.wav");
	this->reinforceBuffer.loadFromFile("../Sounds/reinforce.wav");
	this->nrOf = 0;
	this->sound = new sf::Sound * [50]{ nullptr };
}

SoundManager::~SoundManager()
{
	if (nrOf > 0)
	{
		for (int i = 0; i < nrOf; i++)
		{
			if (sound[i]->getStatus() == sf::Sound::Status::Playing)
			{
				sound[i]->stop();
			}
			delete sound[i];
		}
	}

	delete[] sound;


}




void SoundManager::attack()
{
	sound[nrOf] = new sf::Sound;

	sound[nrOf]->setBuffer(attackBuffer);
	sound[nrOf]->play();
	nrOf++;
}

void SoundManager::convert()
{
	sound[nrOf] = new sf::Sound;

	sound[nrOf]->setBuffer(convertBuffer);
	sound[nrOf]->play();
	nrOf++;
}

void SoundManager::bomb()
{
	sound[nrOf] = new sf::Sound;

	sound[nrOf]->setBuffer(bombBuffer);
	sound[nrOf]->play();
	nrOf++;
}

void SoundManager::ability()
{
	sound[nrOf] = new sf::Sound;

	sound[nrOf]->setBuffer(abilityBuffer);
	sound[nrOf]->play();
	nrOf++;
}

void SoundManager::takeDamage()
{
	sound[nrOf] = new sf::Sound;

	sound[nrOf]->setBuffer(takingDamageBuffer);
	sound[nrOf]->play();
	nrOf++;

}

void SoundManager::death()
{


	sound[nrOf] = new sf::Sound;

	sound[nrOf]->setBuffer(deathBuffer);
	sound[nrOf]->play();
	nrOf++;

}

void SoundManager::healthRegen()
{
	sound[nrOf] = new sf::Sound;

	sound[nrOf]->setBuffer(healthRegenBuffer);
	sound[nrOf]->play();
	nrOf++;
}

void SoundManager::reinforce()
{
	sound[nrOf] = new sf::Sound;

	sound[nrOf]->setBuffer(reinforceBuffer);
	sound[nrOf]->play();
	nrOf++;
}

void SoundManager::deleteAudio()
{
	if (nrOf > 0)
	{
		for (int i = 0; i < nrOf; i++)
		{
			if (sound[i]->getStatus() != sf::Sound::Status::Playing)
			{
				delete sound[i];
				for (int b = i; b < nrOf; b++)
				{
					sound[b] = sound[b + 1];
				}
				sound[nrOf] = nullptr;
				nrOf--;

			}
		}
	}
}
