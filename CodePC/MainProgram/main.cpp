#include <SFML/Graphics.hpp>
#include <iostream>

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
	std::cout << "esgrmtpero" << std::endl;
	float lele = 124.f;
	double geroptrgs = 3;
	(void)getchar();
	//well he hello there.
	std::string textis;
	getline(cin, textis);
	cout << textis << endl;
	cout << "look how easy it is when you don't have to write std before cout and endl " << endl;
	cout << "Jag orkar inte mer";
	cout << "Vill inte vara kvar";
	return 6;
}