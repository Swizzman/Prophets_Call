#include "SoundManager.h"

SoundManager::SoundManager()
{
	nrOf = 0;
	//sound.setBuffer(attackBuffer);
	sound = new sf::Sound * [5]{nullptr};
}

SoundManager::~SoundManager()
{
	if (nrOf > 0)
	{
		for (int i = 0; i < nrOf; i++)
		{
			delete sound[i];
		}
	}
	delete[] sound;
	
	
}

void SoundManager::loadSounds()
{
	attackBuffer.loadFromFile("../Sounds/attack.wav");
	abilityBuffer.loadFromFile("../Sounds/ability.wav");
	convertBuffer.loadFromFile("../Sounds/convert.wav");
	bombBuffer.loadFromFile("../Sounds/bomb.wav");
	DeathBuffer.loadFromFile("../Sounds/death.wav");
	HealthRegenBuffer.loadFromFile("../Sounds/HealthRegen.wav");
	takingDamageBuffer.loadFromFile("../Sounds/hurt.wav");
	reinforceBuffer.loadFromFile("../Sounds/reinforce.wav");
}

void SoundManager::attack()
{
	if (nrOf > 0)
	{
		for (int i = 0; i < nrOf; i++)
		{
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

	sound[nrOf]->setBuffer(DeathBuffer);
	sound[nrOf]->play();
	nrOf++;

}

void SoundManager::healthRegen()
{
	sound[nrOf] = new sf::Sound;

	sound[nrOf]->setBuffer(HealthRegenBuffer);
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
				delete[] sound[i];
				//sound[i] = nullptr;
			//	cout << i << endl;
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
