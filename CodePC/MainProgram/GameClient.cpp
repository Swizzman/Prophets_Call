#include "GameClient.h"

GameClient::GameClient() : networkThread(&GameClient::netWorking, this)
{
	thisProphet = new Prophet();
	otherProphet = nullptr;
	followerCap = 30;
	nrOfTotalFollowers = 0;
	allFollowers = new Follower * [followerCap] { nullptr };
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
	//thisProphet->recieveEnemyProphet(otherProphet);
	//otherProphet->recieveEnemyProphet(thisProphet);
	converting = false;
	abilityplaced = false;
}

GameClient::~GameClient()
{
	delete thisProphet;
	delete otherProphet;
	for (int i = 0; i < nrOfTotalFollowers; i++)
	{
		delete allFollowers[i];
	}
	delete[] allFollowers;
}

void GameClient::netWorking()
{
	client.run();
	otherProphet = new Prophet();
	thisProphet->recieveEnemyProphet(otherProphet);
	otherProphet->recieveEnemyProphet(thisProphet);
	Packet packet;
	while (client.getConnected())
	{
		packet = client.recieveAPacket();
		if (packet.type == 1)
		{
			otherProphet->setPosition(packet.posX, packet.posY);

		}
		else if (packet.type == 2)
		{
			if (allFollowers[packet.index] != nullptr)
			{

				allFollowers[packet.index]->setPosition(packet.posX, packet.posY);
			}
		}
		else if (packet.type == 4)
		{
			if (allFollowers[packet.index] != nullptr)
			{
				allFollowers[packet.index]->otherConvert();
				otherProphet->addFollower(allFollowers[packet.index]);
			}
		}
		else if (packet.type == 5)
		{
			if (allFollowers[packet.index] != nullptr)
			{
				std::cout << "Follower Took damage\n";
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
			otherProphet->placeAbil(pos, packet.abilType);
		}
	}
}

void GameClient::handleEvents()
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

				converting = true;
				break;
			case sf::Keyboard::Num1:
				thisProphet->changeAbility();
				thisProphet->getASingleFollower(rand() % thisProphet->getNrOfFollowers()).takeDamage(rand() % 20);
				thisProphet->takeDamage(rand() % 20);

				break;
			case sf::Keyboard::LControl:
				thisProphet->placeAbil((sf::Vector2f)mouse.getPosition());
				abilityplaced = true;
				break;
			case sf::Keyboard::Tab:
				uiManager.changeCS();
				thisProphet->changeCurrentCommandGroup();

				break;
			case sf::Keyboard::LShift:
				thisProphet->changeCurrentCommand();
				uiManager.updateCS(thisProphet->getcurrentGroupCommand());
				break;
			case sf::Keyboard::Enter:
				changeFullscreenMode();
				break;
			case  sf::Keyboard::Escape:

				window.close();
				std::exit(0);

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


	}
}

State GameClient::update()
{
	State state = State::NO_CHANGE;
	while (window.isOpen())
	{

		elapsedTimeSinceLastUpdate += clock.restart();
		while (elapsedTimeSinceLastUpdate > timePerFrame)
		{
			elapsedTimeSinceLastUpdate -= timePerFrame;
			//Move the playerProphet
			thisProphet->moveProphet();

			thisProphet->convertsFollow();

			client.sendProphetPos(thisProphet->getPosition());
			//Check All the civilians for movement


			for (int i = 0; i < nrOfTotalFollowers; i++)
			{
				if (allFollowers[i]->getConverted() && !allFollowers[i]->getConvertedByOther())
				{
					allFollowers[i]->checkCivMove();
				}
				if (allFollowers[i]->getOtherNotified())
				{
					client.sendConverted(i);
					allFollowers[i]->otherIsNotified();
				}
				if (!allFollowers[i]->getConvertedByOther() && allFollowers[i]->getConverted())
				{
					client.sendFollowerPos(allFollowers[i]->getPosition(), i);
				}
				if (allFollowers[i]->getAttackNotify())
				{
					std::cout << "Sent damage\n";
					allFollowers[i]->otherAttackNotified();
					client.sendFollowerDamage(i, allFollowers[i]->getHealth());

				}
				if (otherProphet->getAttackNotify())
				{
					otherProphet->otherAttackNotified();
					std::cout << otherProphet->getHealth() << std::endl;
					client.sendProphetDamage(otherProphet->getHealth());
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
			if (this->thisProphet->getNrOfFollowers() > uiManager.getNrOfCurrentGroup())
			{
				//cout << thisProphet->getNrOfFollowers() << endl;
				uiManager.addFps(thisProphet->getASingleFollower(this->thisProphet->getNrOfFollowers() - 1).getTextureName(), thisProphet->getASingleFollower(this->thisProphet->getNrOfFollowers() - 1).getHealth());
				uiManager.updateCSNumber(thisProphet->getNrOfFollowers());
				//uiManager.setUpFps();


			}
		}
		for (int i = 0; i < thisProphet->getNrOfFollowers(); i++)
		{
			uiManager.updateFps(thisProphet->getASingleFollower(i).getHealth(), i);
		}
		uiManager.updatePp(thisProphet->getHealth(), thisProphet->getSouls(), thisProphet->getCurrentAbility());
		return state;
	}

}

void GameClient::render()
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
	if (otherProphet->getIfAbilityIsActive())
	{
		window.draw(*this->otherProphet->getCurAbil());

	}
	if (thisProphet->getIfAbilityIsActive())
	{
		window.draw(*this->thisProphet->getCurAbil());
	}
	for (int i = 0; i < nrOfTotalFollowers; i++)
	{
		if (allFollowers[i] != nullptr)
		{

			window.draw(*allFollowers[i]);
		}
	}
	uiManager.drawUI(window);
	window.display();
}
