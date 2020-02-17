#include "Game.h"



Game::Game()
{
	thisProphet = new Prophet();
	otherProphet = new Prophet();
	followerCap = 30;
	nrOfTotalFollowers = 0;
	allFollowers = new Follower*[followerCap] { nullptr };
	for (int i = 0; i < followerCap; i++)
	{
		allFollowers[i] = new Follower();
		nrOfTotalFollowers++;
	}
	elapsedTimeSinceLastUpdate = sf::Time::Zero;
	timePerFrame = sf::seconds(1 / 60.f);
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
			//Move the playerProphet
			//Check All the civilians for movement
		}
		return state;
	}

}

void Game::render()
{
	window.clear();
	window.draw(*thisProphet);
	window.draw(*otherProphet);
	for (int i = 0; i < nrOfTotalFollowers; i++)
	{
		window.draw(*allFollowers[i]);
	}
	window.display();
}
