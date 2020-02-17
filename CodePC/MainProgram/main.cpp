#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameState.h"
#include "Game.h"

#ifdef _DEBUG
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#else
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-graphics.lib")
#endif

using namespace std;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	GameState* current = nullptr;
	State currentState = State::PLAY;

	srand((unsigned int)time(0));
	while (currentState != State::EXIT)
	{
		current->handleEvents();
		current->update();
		switch (currentState)
		{
		case State::PLAY:
			delete current;
			current = new Game();
			break;
		case State::MENU:
			break;
		default:
			break;
		}
		
		current->render();

	}
	delete current;
	return 0;
}