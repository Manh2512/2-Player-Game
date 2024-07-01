#pragma once
#include <SFML/Graphics.hpp>

class Coin{
    int posX, posY;
    sf::Color color;

public:
    int size;
    sf::CircleShape coin;

    Coin();
    void initCoin();
};
