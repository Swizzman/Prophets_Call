#include "Menu.h"

Menu::Menu()
{
	font.loadFromFile("c:/windows/Fonts/arial.ttf");
	playText.setFont(font);
	mainMenuText.setFont(font);
	closeText.setFont(font);
	connectingText.setFont(font);
	playText.setString("Play");
	mainMenuText.setString("Prophets Call");
	closeText.setString("Quit");
	connectingText.setString("Connect");
	connectingText.setCharacterSize(40);
	mainMenuText.setCharacterSize(80);
	mainMenuText.setPosition(910 - mainMenuText.getGlobalBounds().width / 2, 200);
	playText.setCharacterSize(40);
	playText.setPosition(mainMenuText.getPosition().x + (mainMenuText.getGlobalBounds().width / 2 - playText.getGlobalBounds().width / 2), 350);
	closeText.setCharacterSize(40);
	connectingText.setPosition(mainMenuText.getPosition().x + (mainMenuText.getGlobalBounds().width / 2 - connectingText.getGlobalBounds().width / 2), 420);
	closeText.setPosition(mainMenuText.getPosition().x + (mainMenuText.getGlobalBounds().width / 2 - closeText.getGlobalBounds().width / 2), 490);
	iPText.setFont(font);
	iPText.setString("Please enter IP:");
	iPText.setCharacterSize(40);
	iPText.setPosition(((WIDTH / 2) - iPText.getGlobalBounds().width), ((HEIGHT / 2) - iPText.getGlobalBounds().height));
	currentHighlightedButton = 0;
	inputText.setFont(font);
	inputText.setPosition(iPText.getGlobalBounds().left + iPText.getGlobalBounds().width + 20, (HEIGHT / 2) - iPText.getGlobalBounds().height);
	inputText.setCharacterSize(40);
	window.setKeyRepeatEnabled(false);
	iPMode = false;
	inputDone = false;

	elapsedTimeSinceLastUpdate = sf::Time::Zero;
	timePerFrame = sf::seconds(1 / 60.f);
}

Menu::~Menu()
{
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
			if (event.key.code == sf::Keyboard::Insert)
			{

				changeFullscreenMode();
			}
		}
		if (event.type == sf::Event::TextEntered)
		{
			if (iPMode)
			{
				if (!inputDone)
				{
					if (event.text.unicode == 8)
					{
						if (!input.empty())
						{
							input.pop_back();
						}
						inputText.setString(input);
					}
					else if (event.text.unicode != 13)
					{
						input += event.text.unicode;
						inputText.setString(input);

					}
					else
					{
						inputDone = true;
					}
				}

			}
		}



	}
}

State Menu::update()
{

	while (window.isOpen())
	{
		State state = State::NO_CHANGE;
		elapsedTimeSinceLastUpdate += clock.restart();

		while (elapsedTimeSinceLastUpdate > timePerFrame)
		{
			elapsedTimeSinceLastUpdate -= timePerFrame;
			if (inputDone)
			{
				if (input.length() > 4)
				{

					iPOut.open("../datafiles/ip.txt");
					iPOut << input;
					iPOut.close();
				}
				state = State::CONNECT;
			}
			sf::Vector2f mousePos = (sf::Vector2f)mouse.getPosition(window);
			if (playText.getGlobalBounds().contains(mousePos))
			{
				playText.setFillColor(sf::Color::Yellow);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					state = State::HOST;
				}

			}
			else
			{
				playText.setFillColor(sf::Color::White);
			}

			if (closeText.getGlobalBounds().contains(mousePos))
			{
				closeText.setFillColor(sf::Color::Yellow);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					window.close();
					state = State::EXIT;
				}
			}
			else
			{
				closeText.setFillColor(sf::Color::White);
			}
			if (connectingText.getGlobalBounds().contains(mousePos))
			{
				connectingText.setFillColor(sf::Color::Yellow);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					iPMode = true;
				}
			}
			else
			{
				connectingText.setFillColor(sf::Color::White);
			}
			return state;
		}
	}
}

void Menu::render()
{
	window.clear();
	if (!iPMode)
	{

		window.draw(playText);
		window.draw(mainMenuText);
		window.draw(closeText);
		window.draw(connectingText);
	}
	else
	{
		window.draw(inputText);
		window.draw(iPText);
	}
	window.display();


}

