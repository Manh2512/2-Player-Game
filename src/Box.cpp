#include "Box.hpp"
#include <random>

Box::Box(){}
Box::~Box(){}

int Box::getX(){
    return box.getPosition().x;
}
int Box::getY(){
    return box.getPosition().y;
}

void Box::initBox(int type){
    switch(type){
        case 1:
            value = 20;
            size = 40;
            vY = 3;
            color = sf::Color(186, 97, 86);
            break;
        case 2:
            value = 30;
            size = 48;
            vY = 5;
            color = sf::Color(143, 222, 93);
            break;
        case 3:
            value = 40;
            size = 52;
            vY = 6;
            color = sf::Color(176, 48, 92);
    }
    posX = 200 + rand() % (400-size);
    vX = 0;
    posY = 0;
    v0 = vY;

    box.setPosition(sf::Vector2f(posX, posY));
    box.setFillColor(color);
    box.setSize(sf::Vector2f(size, size));
}

bool Box::interactPlayer(Player& player){
    return (box.getGlobalBounds().intersects(player.player.getGlobalBounds()));
}
bool Box::cVPlayer(Player& player){
    return (getY() >= player.getY() - size - 32);
}
bool Box::cHPlayer_Left(Player& player){
    return (getX() + size >= player.getX() - 32);
}
bool Box::cHPlayer_Right(Player& player){
    return (getX() <= player.getX() + 32);
}

bool Box::cVStop(Player& player){
    return (interactPlayer(player) && cVPlayer(player));
}

void Box::moved(Player& player){
    if(interactPlayer(player) && player.HP > value){
        if(cHPlayer_Left(player) && player.leftMove){
            vY = 0;
            vX = -player.velocity;
        }else if(cHPlayer_Right(player) && player.rightMove){
            vY = 0;
            vX = player.velocity;
        }
    }
}
