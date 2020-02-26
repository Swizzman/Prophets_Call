#include "Menu.h"

Menu::Menu()
{
	font.loadFromFile("c:/windows/Fonts/arial.ttf");
	playText.setFont(font);
	mainMenuText.setFont(font);
	CloseText.setFont(font);
	ConnectingText.setFont(font);
	playText.setString("Play");
	mainMenuText.setString("Prophets Call");
	CloseText.setString("Quit");
	ConnectingText.setString("Connect");
	ConnectingText.setCharacterSize(40);
	mainMenuText.setCharacterSize(80);
	mainMenuText.setPosition(910 - mainMenuText.getGlobalBounds().width/2, 200);
	playText.setCharacterSize(40);
	playText.setPosition(mainMenuText.getPosition().x +(mainMenuText.getGlobalBounds().width/2 - playText.getGlobalBounds().width/2),350);
	CloseText.setCharacterSize(40);
	ConnectingText.setPosition(mainMenuText.getPosition().x + (mainMenuText.getGlobalBounds().width/2 - ConnectingText.getGlobalBounds().width/2), 420);
	CloseText.setPosition(mainMenuText.getPosition().x + (mainMenuText.getGlobalBounds().width/2 - CloseText.getGlobalBounds().width / 2), 490);

	currentHighlightedButton = 0;

	window.setKeyRepeatEnabled(false);



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
			if (event.key.code == sf::Keyboard::Q)
			{
				
				changeFullscreenMode();
			}
		}
		/*if (event.type == sf::Event::KeyPressed)
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
		}*/



	}
}

State Menu::update()
{
	State state = State::NO_CHANGE;

	while (window.isOpen())
	{
		elapsedTimeSinceLastUpdate += clock.restart();
		sf::Vector2f tempVec = static_cast<sf::Vector2f>(mouse.getPosition(window));
		//sf::FloatRect fr(tempVec.x, tempVec.y,10,10);
		//sf::FloatRect fr(mouse.getPosition().x, mouse.getPosition().y, 10, 10);
		if (playText.getGlobalBounds().contains(tempVec))
		{
			playText.setFillColor(sf::Color::Yellow);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				state = State::PLAY;
			}

		}
		else
		{
			playText.setFillColor(sf::Color::White);
		}

		if (CloseText.getGlobalBounds().contains(tempVec))
		{
			CloseText.setFillColor(sf::Color::Yellow);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				window.close();
				state = State::EXIT;
			}
		}
		else
		{
			CloseText.setFillColor(sf::Color::White);
		}
		if (ConnectingText.getGlobalBounds().contains(tempVec))
		{
			ConnectingText.setFillColor(sf::Color::Yellow);
		}
		else
		{
			ConnectingText.setFillColor(sf::Color::White);
		}

		
		
		while (elapsedTimeSinceLastUpdate > timePerFrame)
		{
			elapsedTimeSinceLastUpdate -= timePerFrame;

			
		
				/*if (currentHighlightedButton == 0)
				{
					playText.setFillColor(sf::Color::Yellow);
					CloseText.setFillColor(sf::Color::White);
					
				}
				else if (currentHighlightedButton == 1)
				{
					CloseText.setFillColor(sf::Color::Yellow);
					playText.setFillColor(sf::Color::White);
					
				}*/
		}
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (currentHighlightedButton == 0)
			{
				state = State::PLAY;
			}


		}*/
		return state;
	}



	
}

void Menu::render()
{
	window.clear();
	window.draw(playText);
	window.draw(mainMenuText);
	window.draw(CloseText);
	window.draw(ConnectingText);
	window.display();
	
	
}

