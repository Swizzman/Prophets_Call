#include "GameHost.h"



void GameHost::expand(Follower** arr, int& cap, int nrOf)
{
	cap += 10;
	Follower** temp = new Follower * [cap] {nullptr};
	for (int i = 0; i < nrOf; i++)
	{
		temp[i] = arr[i];
	}
	delete[] arr;
	arr = temp;
}

GameHost::GameHost() : netWorkThread(&GameHost::networking, this)
{
	thisProphet = new Prophet();
	otherProphet = nullptr;
	nrOfDead = 0;
	deadCap = 30;
	followerCap = 30;
	nrOfTotalFollowers = 0;
	allFollowers = new Follower * [followerCap] { nullptr };
	deadFollowers = new Follower * [deadCap] {nullptr};
	for (int i = 0; i < followerCap; i++)
	{
		allFollowers[i] = new Follower();
		allFollowers[i]->placeFollower(WIDTH, HEIGHT);
		nrOfTotalFollowers++;
	}

	elapsedTimeSinceLastUpdate = sf::Time::Zero;
	timePerFrame = sf::seconds(1 / 60.f);
	uiManager.setUpPp(thisProphet->getHealth());
	uiManager.setUpCS();
	uiManager.setUpFps(nrOfTotalFollowers);
	converting = false;
	abilityplaced = false;
	activeClient = false;
	thisProphet->setPosition(500, 500);
	//otherProphet = new Prophet();
	//thisProphet->recieveEnemyProphet(otherProphet);
	//otherProphet->recieveEnemyProphet(thisProphet);
	//activeClient = true;
}

void GameHost::networking()
{

	server.run();
	Packet packet;

	while (server.getClientConnected())
	{
		packet = server.recieveAPacket();
		if (packet.type == 1)
		{
			otherProphet->setPosition(packet.posX, packet.posY);

		}
		if (packet.type == 2)
		{
			allFollowers[packet.index]->setPosition(packet.posX, packet.posY);
		}
		else if (packet.type == 4)
		{
			allFollowers[packet.index]->otherConvert();
			otherProphet->addFollower(allFollowers[packet.index]);
		}
		else if (packet.type == 5)
		{
			if (allFollowers[packet.index] != nullptr)
			{
				allFollowers[packet.index]->setHealth(packet.health);
			}
		}
		else if (packet.type == 6)
		{
			thisProphet->setHealth(packet.health);
			std::cout << thisProphet->getHealth() << std::endl;
		}
		else if (packet.type == 7)
		{
			sf::Vector2f pos;
			pos.x = packet.posX;
			pos.y = packet.posY;
			if (otherProphet != nullptr)
			{
				otherProphet->placeAbil(pos, packet.abilType);

			}
		}
		else if (packet.type == 8)
		{
			allFollowers[packet.index]->setAnimation(packet.column, packet.row);
		}
		else if (packet.type == 9)
		{
			otherProphet->setAnimation(packet.column, packet.row);
		}
		else if (packet.type == 10)
		{
			//delete allFollowers[packet.index];
			deadFollowers[nrOfDead] = allFollowers[packet.index];
			nrOfDead++;
			allFollowers[packet.index] = new Follower();
			allFollowers[packet.index]->placeFollower(WIDTH, HEIGHT);
		}
	}
}

GameHost::~GameHost()
{
	delete thisProphet;
	delete otherProphet;
	for (int i = 0; i < nrOfTotalFollowers; i++)
	{
		delete allFollowers[i];
	}
	delete[] allFollowers;
}

void GameHost::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		if (event.type == sf::Event::KeyPressed)
		{

			switch (event.key.code)
			{
			case sf::Keyboard::Space:
				if (activeClient)
				{

					converting = true;
				}
				break;
			case sf::Keyboard::Num1:
				thisProphet->changeAbility();
				//if (thisProphet->getNrOfFollowers() > 0)
				//	thisProphet->getASingleFollower(rand() % thisProphet->getNrOfFollowers()).takeDamage(rand() % 20);
				//thisProphet->takeDamage(rand() % 20);

				break;
			case sf::Keyboard::LControl:
				thisProphet->placeAbil((sf::Vector2f)mouse.getPosition());
				if (thisProphet->getIfAbilityIsActive())
				{
					thisProphet->startAnimation(thisProphet->getWalkingDirection() - 4, 7, 15, 1);

					server.sendAbilPlace((sf::Vector2f)mouse.getPosition(), thisProphet->getCurrentAbility());
					abilityplaced = true;
				}

				break;
			case sf::Keyboard::Tab:
				if (activeClient)
				{

					uiManager.changeCS();
					thisProphet->changeCurrentCommandGroup();
				}

				break;
			case sf::Keyboard::LShift:
				thisProphet->changeCurrentCommand();
				uiManager.updateCS(thisProphet->getcurrentGroupCommand());
				break;
			case sf::Keyboard::Enter:
				changeFullscreenMode();
				break;

			default:
				break;
			}
		}
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Space:
				converting = false;
				break;
			default:
				break;
			}
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			switch (event.mouseButton.button)
			{
			case sf::Mouse::Right:

				thisProphet->placeAbil((sf::Vector2f)sf::Mouse::getPosition());
				if (thisProphet->getIfAbilityIsActive())
				{
					thisProphet->startAnimation(thisProphet->getWalkingDirection() - 4, 7, 15, 1);

					server.sendAbilPlace((sf::Vector2f)mouse.getPosition(), thisProphet->getCurrentAbility());
					abilityplaced = true;
				}

				break;
			default:
				break;
			}
		}


	}

}

State GameHost::update()
{
	State state = State::NO_CHANGE;
	while (window.isOpen())
	{

		elapsedTimeSinceLastUpdate += clock.restart();
		while (elapsedTimeSinceLastUpdate > timePerFrame)
		{
			if (deadCap - nrOfDead < 4)
			{
				expand(deadFollowers, deadCap, nrOfDead);
			}
			elapsedTimeSinceLastUpdate -= timePerFrame;
			if (!activeClient)
			{
				if (server.getClientConnected())
				{
					otherProphet = new Prophet();
					activeClient = true;
					thisProphet->recieveEnemyProphet(otherProphet);
					otherProphet->recieveEnemyProphet(thisProphet);
				}
			}
			if (activeClient)
			{

				thisProphet->moveProphet();
			}
			if (otherProphet != nullptr && activeClient)
			{
				server.sendProphetPos(thisProphet->getPosition());
				server.sendProphetAnim(thisProphet->getCurrentColummn(), thisProphet->getCurrentRow());
			}


			thisProphet->convertsFollow();
			//Move the playerProphet
			//Check All the civilians for movement
			for (int i = 0; i < nrOfTotalFollowers; i++)
			{
				if (allFollowers[i] != nullptr)
				{

					if (allFollowers[i]->getHealth() <= 0 && allFollowers[i]->isAlive())
					{
						allFollowers[i]->die();
						if (allFollowers[i]->getConvertedByOther())
						{
							otherProphet->removeFollower(allFollowers[i]);

						}
						else
						{
							thisProphet->removeFollower(allFollowers[i]);
							for (int i = 0; i < 3; i++)
							{
								uiManager.decreaseCsNumber(thisProphet->getAllNrOfFollowers(i), i);
							}
						}
						soundManager.death();
					}
					if (allFollowers[i]->hasLostHealth() == true && allFollowers[i]->isAlive())
					{
						cout << "taking damage" << endl;
						soundManager.takeDamage();
					}

					allFollowers[i]->checkCivMove();
					if (otherProphet != nullptr)
					{
						if ((allFollowers[i]->getConvertedByOther() == false && allFollowers[i]->getConverted()) || !allFollowers[i]->getConverted())
						{
							if (allFollowers[i]->isAlive())
							{

								server.sendFollowerPos(allFollowers[i]->getPosition(), i);
								server.sendFollowerAnim(i, allFollowers[i]->getCurrentColummn(), allFollowers[i]->getCurrentRow());
							}
						}
						if (allFollowers[i]->getConvertedByOther() && !allFollowers[i]->isAlive())
						{
							thisProphet->collectSouls(allFollowers[i]);
						}
					}
					if (allFollowers[i]->getOtherNotified())
					{
						server.sendConverted(i);
						allFollowers[i]->otherIsNotified();
					}
					if (activeClient)
					{

						if (allFollowers[i]->getAttackNotify())
						{
							std::cout << "Sent damage\n";
							allFollowers[i]->otherAttackNotified();
							server.sendFollowerDamage(i, allFollowers[i]->getHealth());

						}
						if (otherProphet->getAttackNotify())
						{
							otherProphet->otherAttackNotified();
							std::cout << otherProphet->getHealth() << std::endl;
							server.sendProphetDamage(otherProphet->getHealth());
						}
					}
				}
				if (allFollowers[i]->getSoulCollected())
				{
					server.sendSoulCollected(i);
					deadFollowers[nrOfDead] = allFollowers[i];
					nrOfDead++;
					//delete allFollowers[i];
					allFollowers[i] = new Follower();
					allFollowers[i]->placeFollower(WIDTH, HEIGHT);
				}
			}
			if (activeClient)
			{

				if (thisProphet->getCurAbil() != nullptr)
				{
					if (thisProphet->getIfSoundBoolIsActive())
					{
						cout << "activate" << endl;
						if (thisProphet->getCurrentAbility() == 0)
						{
							soundManager.bomb();
						}
						else if (thisProphet->getCurrentAbility() == 1)
						{
							soundManager.healthRegen();
						}
						else
						{
							soundManager.reinforce();
						}

					}
				}
				if (thisProphet->getIfAbilityIsActive())
				{

					thisProphet->timerForAbility();

				}
				else
				{
					if (thisProphet->getCurrentAbility() == 2 && thisProphet->returnReinforceBool())
					{
						thisProphet->endingReinforcementAbility();

					}
					abilityplaced = false;


				}
				if (otherProphet->getIfAbilityIsActive())
				{

					otherProphet->timerForAbility();

				}
				else
				{
					if (otherProphet->getCurrentAbility() == 2 && otherProphet->returnReinforceBool())
					{
						otherProphet->endingReinforcementAbility();

					}


				}
				//Check conversion and start if key is pressed
				if (converting)
				{
					thisProphet->convert(allFollowers, nrOfTotalFollowers);


				}
				else
				{
					thisProphet->resetClock();
				}
			}

			if (this->thisProphet->getNrOfFollowers() > uiManager.getNrOfCurrentGroup())
			{
				uiManager.addFps(thisProphet->getASingleFollower(this->thisProphet->getNrOfFollowers() - 1).getTextureName(), thisProphet->getASingleFollower(this->thisProphet->getNrOfFollowers() - 1).getHealth(), thisProphet->getAllNrOfFollowers(thisProphet->getCurrentGroup()));

				uiManager.updateCSNumber(thisProphet->getNrOfFollowers());
				cout << "working " << endl;

			}

			soundManager.deleteAudio();
			//thisProphet->updateAnimation((int)ANIMATIONSPRITEROW::DIE, 2, 60);

		}
		for (int i = 0; i < thisProphet->getNrOfFollowers(); i++)
		{
			uiManager.updateFps(thisProphet->getASingleFollower(i).getHealth(), i);
		}
		uiManager.updatePp(thisProphet->getHealth(), thisProphet->getSouls(), thisProphet->getCurrentAbility());
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			netWorkThread.join();
			state = State::EXIT;
		}

		return state;
	}

}

void GameHost::render()
{
	window.clear();

	window.draw(*thisProphet);
	if (otherProphet != nullptr)
	{
		window.draw(*otherProphet);

	}
	if (converting)
	{
		window.draw(thisProphet->getConvertCirc());

	}
	if (thisProphet->getIfAbilityIsActive())
	{
		window.draw(*this->thisProphet->getCurAbil());
	}
	if (activeClient)
	{
		if (otherProphet != nullptr)
		{

			if (otherProphet->getCurAbil() != nullptr)
			{

				if (otherProphet->getIfAbilityIsActive())
				{
					window.draw(*this->otherProphet->getCurAbil());
				}
			}
		}
	}
	for (int i = 0; i < nrOfTotalFollowers; i++)
	{
		if (!allFollowers[i]->getSoulCollected())
		{

			window.draw(*allFollowers[i]);
		}
	}
	uiManager.drawUI(window);
	window.display();
}
