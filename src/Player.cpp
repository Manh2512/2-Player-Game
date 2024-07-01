#include "Player.hpp"
#include "Coin.hpp"
#include <SFML/Graphics.hpp>

Player::Player(int num){
    switch(num){
            case 1:
                x = 250, y = 500;
                break;
            case 2:
                x = 486, y = 500;
        }
    size = 64;
    velocity = 3;
    orgV = velocity;
    score = 0;
    HP = 100;
    leftMove = false, rightMove = false, upMove = false, downMove = false;
    player.setPosition(sf::Vector2f(x, y));
    player.setOrigin(sf::Vector2f(size/2, size/2));
}

int Player::getX(){
    return player.getPosition().x;
}

int Player::getY(){
    return player.getPosition().y;
}

void Player::loadTexture(std::string filename){
    if(!texture.loadFromFile(filename)){
        return;
    }
    player.setTexture(texture);
}

void Player::updateMove(){
    if(leftMove){
        player.setRotation(90);
        player.move(-velocity, 0);
    }
    if(rightMove){
        player.setRotation(-90);
        player.move(velocity, 0);
    }
    if(upMove){
        player.setRotation(180);
        player.move(0, -velocity);
    }
    if(downMove){
        player.setRotation(0);
        player.move(0, velocity);
    }
}

void Player::interact(Player& otherPlayer){
    if(player.getGlobalBounds().intersects(otherPlayer.player.getGlobalBounds())){
        if((leftMove && otherPlayer.rightMove && getX() > otherPlayer.getX())
        || (rightMove && otherPlayer.leftMove && getX() < otherPlayer.getX())
        || (upMove && otherPlayer.downMove && getY() > otherPlayer.getY())
        || (downMove && otherPlayer.upMove && getY() < otherPlayer.getY())){
            velocity = 0;
            otherPlayer.velocity = 0;
            HP--;
            otherPlayer.HP--;
        }else{
            velocity = orgV;
            otherPlayer.velocity = otherPlayer.orgV;
        }
    }
}

void Player::collisionCoin(Coin& coin){
    if(player.getGlobalBounds().intersects(coin.coin.getGlobalBounds())){
        coin.initCoin();
        HP += 30;
    }
}

void Player::upGrade(){
    if(score > 300){
        velocity = 6;
    }else if(score > 180){
        velocity = 4;
    }
}
