#include "GameLostMode.h"

GameLostMode::GameLostMode()
{
	this->done = false;
	font.loadFromFile("c:/windows/fonts/arial.ttf");
	gameLostText.setFont(font);
	gameLostText.setCharacterSize(80);
	gameLostText.setString("You Lost!");
	gameLostText.setPosition((WIDTH / 2) - (gameLostText.getGlobalBounds().width / 2), (HEIGHT / 2) - (gameLostText.getGlobalBounds().height / 2));
}

GameLostMode::~GameLostMode()
{
}

void GameLostMode::handleEvents()
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
			case sf::Keyboard::Enter:
				done = true;
				break;
			default:
				break;
			}
		}
	}
}

State GameLostMode::update()
{
	State state = State::NO_CHANGE;
	if (done)
	{
		state = State::MENU;
	}
	return state;
}

void GameLostMode::render()
{
	window.clear();
	window.draw(gameLostText);
	window.display();
}
