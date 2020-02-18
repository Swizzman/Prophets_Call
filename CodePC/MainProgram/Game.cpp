#include "Game.h"



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
	elapsedTimeSinceLastUpdate = sf::Time::Zero;
	timePerFrame = sf::seconds(1 / 60.f);
	converting = false;
}

Game::~Game()
{
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
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Space:
				converting = true;
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
			}
		}
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
	for (int i = 0; i < nrOfTotalFollowers; i++)
	{
		window.draw(*allFollowers[i]);
	}
	window.display();
}
