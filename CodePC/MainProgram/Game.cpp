#include "Game.h"



Game::Game()
{
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
		}

	}
	return state;
}

void Game::render()
{
	window.clear();
	window.display();
}
