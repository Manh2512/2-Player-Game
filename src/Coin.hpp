#include "Coin.hpp"
#include <random>

Coin::Coin(){
    size = 10;
    color = sf::Color(255, 226, 112);
    coin.setFillColor(color);
    coin.setRadius(size);
    coin.setOrigin(sf::Vector2f(size/2, size/2));
}
void Coin::initCoin(){
    posX = 200 + rand() % (400 - size);
    posY = 50 + rand() % (700 - size);
    coin.setPosition(sf::Vector2f(posX, posY));
}
