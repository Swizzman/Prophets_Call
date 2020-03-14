#include "GameWonMode.h"

GameWonMode::GameWonMode()
{
	this->done = false;
	font.loadFromFile("c:/windows/fonts/arial.ttf");
	gameWonText.setFont(font);
	gameWonText.setCharacterSize(80);
	gameWonText.setString("You Won!");
	gameWonText.setPosition((WIDTH / 2) - (gameWonText.getGlobalBounds().width / 2), (HEIGHT / 2) - (gameWonText.getGlobalBounds().height / 2));
}

GameWonMode::~GameWonMode()
{
}

void GameWonMode::handleEvents()
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

State GameWonMode::update()
{
	State state = State::NO_CHANGE;
	if (done)
	{
		state = State::MENU;
	}
	return state;
}

void GameWonMode::render()
{
	window.clear();
	window.draw(gameWonText);
	window.display();
}
