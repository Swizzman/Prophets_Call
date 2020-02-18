#include "Menu.h"

Menu::Menu()
{
	font.loadFromFile("c:/windows/Fonts/arial.ttf");
	playText.setFont(font);
	mainMenuText.setFont(font);
	CloseText.setFont(font);
	playText.setString("Play");
	mainMenuText.setString("Main Menu");
	CloseText.setString("Get me out of here");
	mainMenuText.setCharacterSize(80);
	mainMenuText.setPosition(810, 200);
	playText.setCharacterSize(40);
	playText.setPosition(810 +(mainMenuText.getGlobalBounds().width/2 - playText.getGlobalBounds().width/2),350);
	CloseText.setCharacterSize(40);
	CloseText.setPosition(810 + (mainMenuText.getGlobalBounds().width/2 - CloseText.getGlobalBounds().width/2), 420);

	currentHighlightedButton = 0;

	elapsedTimeSinceLastUpdate = sf::Time::Zero;
	timePerFrame = sf::seconds(1 / 60.f);
}

Menu::~Menu()
{
}

sf::Text Menu::renderText()
{
	return playText;
}

void Menu::handleEvents()
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
			if (event.key.code == sf::Keyboard::W)
			{
				if (currentHighlightedButton > 0)
				{
					currentHighlightedButton--;
				}
				else if(currentHighlightedButton <= 0)
				{
					currentHighlightedButton = 1;
				}
				std::cout << currentHighlightedButton << std::endl;
			}
			if (event.key.code == sf::Keyboard::S)
			{
				if (currentHighlightedButton < 1)
				{
					currentHighlightedButton++;
				}
				else if (currentHighlightedButton >= 1)
				{
					currentHighlightedButton = 0;
				}
				std::cout << currentHighlightedButton << std::endl;
			}
		}



	}
}

State Menu::update()
{
	State state = State::NO_CHANGE;

	while (window.isOpen())
	{
		elapsedTimeSinceLastUpdate += clock.restart();
		while (elapsedTimeSinceLastUpdate > timePerFrame)
		{
			elapsedTimeSinceLastUpdate -= timePerFrame;

			
			
				if (currentHighlightedButton == 0)
				{
					playText.setFillColor(sf::Color::Yellow);
					CloseText.setFillColor(sf::Color::White);
					
				}
				else if (currentHighlightedButton == 1)
				{
					CloseText.setFillColor(sf::Color::Yellow);
					playText.setFillColor(sf::Color::White);
					
				}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (currentHighlightedButton == 0)
			{
				state = State::PLAY;
			}


		}
		return state;
	}



	
}

void Menu::render()
{
	window.clear();
	window.draw(playText);
	window.draw(mainMenuText);
	window.draw(CloseText);
	window.display();
	window.setKeyRepeatEnabled(false);
}

