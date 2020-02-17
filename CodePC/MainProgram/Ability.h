#pragma once
#include <SFML/Graphics.hpp>
class Ability 
{
private:
	int hitRadie;
	sf::Sprite sprite;
	sf::Texture texture;


public:

	Ability();
	~Ability();
	int getRadius();
	virtual int getSpecificVar() = 0;



};

