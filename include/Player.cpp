#pragma once
#include <SFML/Graphics.hpp>

class Coin;
class Player{
    int x, y;
    int size;
    sf::Texture texture;
public:
    bool leftMove, rightMove, upMove, downMove;
    int velocity;
    int orgV;
    int score;
    int HP;
    sf::Sprite player;

    Player(int num);
    int getX();
    int getY();
    void loadTexture(std::string filename);
    void updateMove();
    void interact(Player& otherPlayer);
    void collisionCoin(Coin& coin);
    void upGrade();
};
