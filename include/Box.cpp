#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"

class Box{
    int posX, posY;   //initial position
    sf::Color color;
public:
    int value;
    int size;
    int vX, vY;
    int v0;
    sf::RectangleShape box;
    Box();
    ~Box();

    int getX();
    int getY();
    void initBox(int type);
    bool interactPlayer(Player& player);
    bool cVPlayer(Player& player);
    bool cHPlayer_Left(Player& player);
    bool cHPlayer_Right(Player& player);
    bool cVStop(Player& player);
    void moved(Player& player);
};
