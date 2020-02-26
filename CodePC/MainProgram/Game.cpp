#include "Game.h"


using namespace std;
Game::Game()
{
	thisProphet = new Prophet();
	otherProphet = new Prophet();
	followerCap = 30;
	nrOfTotalFollowers = 0;
	allFollowers = new Follower * [followerCap] { nullptr };
	for (int i = 0; i < followerCap; i++)
	{
		allFollowers[i] = new Follower();
		allFollowers[i]->placeFollower(WIDTH, HEIGHT);
		nrOfTotalFollowers++;
	}
	thisProphet->getNrOfCiv(nrOfTotalFollowers);
	
	elapsedTimeSinceLastUpdate = sf::Time::Zero;
	timePerFrame = sf::seconds(1 / 60.f);
	uiManager.setUpPp(thisProphet->getHealth());
	uiManager.setUpCS();
	thisProphet->recieveEnemyProphet(otherProphet);
	otherProphet->recieveEnemyProphet(thisProphet);
	//uiManager.updatePp(thisProphet->getHealth(), thisProphet->getSouls() ,thisProphet->getCurrentAbility());
	uiManager.setUpFps(nrOfTotalFollowers);
	converting = false;
	abilityplaced = false;
}

Game::~Game()
{
	std::cout << "Goodbye world" << std::endl;
}

void Game::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	
		if (event.type == sf::Event::KeyPressed )
		{
			
			switch (event.key.code)
			{
			case sf::Keyboard::Space:
			
				converting = true;
				break;
			case sf::Keyboard::Num1:
				thisProphet->changeAbility();
				if(thisProphet->getNrOfFollowers() > 0)
				thisProphet->getASingleFollower(rand() % thisProphet->getNrOfFollowers()).takeDamage(rand() % 20);
				thisProphet->takeDamage(rand()%20);
				
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

State Game::update()
{
	State state = State::NO_CHANGE;
	while (window.isOpen())
	{
		elapsedTimeSinceLastUpdate += clock.restart();
		while (elapsedTimeSinceLastUpdate > timePerFrame)
		{
			elapsedTimeSinceLastUpdate -= timePerFrame;
			thisProphet->moveProphet();
			thisProphet->convertsFollow();
			//Move the playerProphet
			//Check All the civilians for movement
			for (int i = 0; i < nrOfTotalFollowers; i++)
			{
				allFollowers[i]->checkCivMove();
			}

			
			//Check conversion and start if key is pressed
			if (converting)
			{
				thisProphet->convert(allFollowers, nrOfTotalFollowers);
				if (thisProphet->whichCivIsConverting() <= nrOfTotalFollowers)
				{
					//uiManager.convertingBar(allFollowers[thisProphet->whichCivIsConverting()]->getConvertedAmount, allFollowers[thisProphet->whichCivIsConverting()]->getBounds(), thisProphet->whichCivIsConverting());
				
				}
				
				
			}
			else
			{
				thisProphet->resetClock();
			}

			if (this->thisProphet->getNrOfFollowers() > uiManager.getNrOfCurrentGroup())
			{
				//cout << thisProphet->getNrOfFollowers() << endl;
				uiManager.addFps(thisProphet->getASingleFollower(this->thisProphet->getNrOfFollowers()-1).getTextureName(), thisProphet->getASingleFollower(this->thisProphet->getNrOfFollowers()-1).getHealth());
				uiManager.updateCSNumber(thisProphet->getNrOfFollowers());
			}

		}
		for (int i = 0; i < thisProphet->getNrOfFollowers(); i++)
		{
			uiManager.updateFps(thisProphet->getASingleFollower(i).getHealth(), i);
		}
		uiManager.updatePp(thisProphet->getHealth(), thisProphet->getSouls(), thisProphet->getCurrentAbility());
		


		/*for (int i = 0; i < thisProphet->getNrOfFollowers(); i++)
		{
			if (thisProphet->getASingleFollower(i).getHealth() <= 0)
			{
				cout << "DIE FOLLOWER DIE" << endl;

			}
		}*/
	

		return state;
	}

}

void Game::render()
{
	window.clear();
	
	window.draw(*thisProphet);
	window.draw(*otherProphet);
	if (converting)
	{
	window.draw(thisProphet->getConvertCirc());

	}
	if (abilityplaced)
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
