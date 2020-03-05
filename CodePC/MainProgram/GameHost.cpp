#include "GameHost.h"



GameHost::GameHost() : netWorkThread(&GameHost::networking, this)
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
	/*thisProphet->recieveEnemyProphet(otherProphet);
	otherProphet->recieveEnemyProphet(thisProphet);*/

	elapsedTimeSinceLastUpdate = sf::Time::Zero;
	timePerFrame = sf::seconds(1 / 60.f);
	uiManager.setUpPp(thisProphet->getHealth());
	uiManager.setUpCS();
	uiManager.setUpFps(nrOfTotalFollowers);
	converting = false;
	abilityplaced = false;
	activeClient = false;
	thisProphet->setPosition(500, 500);
}

void GameHost::networking()
{

	server.run();




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

				converting = true;
				break;
			case sf::Keyboard::Num1:
				thisProphet->changeAbility();
				if (thisProphet->getNrOfFollowers() > 0)
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
				//case  sf::Keyboard::Escape:
				//	
				//		window.close();
				//		std::exit(0);
				//		break;

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
			
				thisProphet->placeAbil(tempVec);
				abilityplaced = true;
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
			thisProphet->moveProphet();
			if (otherProphet != nullptr && activeClient)
			{
				server.sendProphetPos(thisProphet->getPosition());

			}
			Packet packet;
			packet = server.recieveAPacket();
			if (packet.type == 1)
			{
				otherProphet->setPosition(packet.posX, packet.posY);

			}

			thisProphet->convertsFollow();
			//Move the playerProphet
			//Check All the civilians for movement
			for (int i = 0; i < nrOfTotalFollowers; i++)
			{
				
				for (int a = 0; a < nrOfTotalFollowers; a++)
				{
					//allFollowers[i]->Collided(allFollowers[a]);
					if (allFollowers[i]->getBounds().intersects(allFollowers[a]->getBounds()) && i != a)
					{
						allFollowers[i]->Collided(allFollowers[a]);
					}
				
					
				}
				allFollowers[i]->checkCivMove();
				if (otherProphet != nullptr)
				{
					server.sendFollowerPos(allFollowers[i]->getPosition(), i);

				}
				if (allFollowers[i]->getClientNotified())
				{
					std::cout << "Sent converted!\n";
					server.sendConverted(i);
					allFollowers[i]->clientIsNotified();
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
				uiManager.addFps(thisProphet->getASingleFollower(this->thisProphet->getNrOfFollowers() - 1).getTextureName(), thisProphet->getASingleFollower(this->thisProphet->getNrOfFollowers() - 1).getHealth());
				uiManager.updateCSNumber(thisProphet->getNrOfFollowers());
			}

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
	for (int i = 0; i < nrOfTotalFollowers; i++)
	{
		window.draw(*allFollowers[i]);
	}
	uiManager.drawUI(window);
	window.display();
}
