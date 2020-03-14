#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <ctime>
class Background : public sf::Drawable
{
private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

public:
	Background();
	virtual ~Background();
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

