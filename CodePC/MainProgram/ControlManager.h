#pragma once
#include <SFML/Graphics.hpp>


class ControlManager
{

private:
    sf::Mouse mouse;
    
public:

    ControlManager();
    ~ControlManager();
    int getMovementInput();
    sf::Vector2f getMousePos();
    sf::Keyboard::Key getKey();




};

