#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameState.h"
#include "GameHost.h"
#include "Menu.h"

#ifdef _DEBUG
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#pragma comment(lib, "sfml-network-d.lib")


#else
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio.lib")
#pragma comment(lib, "sfml-network.lib")


#endif

using namespace std;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	GameState* current = nullptr;
	State currentState = State::MENU;
	current = new Menu();
	srand((unsigned int)time(0));
	while (currentState != State::EXIT)
	{
		current->handleEvents();
		currentState = current->update();
		switch (currentState)
		{
		case State::PLAY:
			delete current;
			current = new GameHost();
			break;
		case State::MENU:
			delete current;
			current = new Menu();
			break;
		default:
			break;
		}
		
		current->render();

	}
	delete current;
	return 1;
}