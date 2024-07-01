#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <ctime>
#include "Coin.hpp"
#include "Player.hpp"
#include "Box.hpp"

//g++ -o prog main.cpp Box.cpp Player.cpp Coin.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-window -lsfml-system -lsfml-graphics

int main(){
    int width = 800;
    int height = 800;
    sf::RenderWindow window(sf::VideoMode(width, height), "Something");
    int framerate = 60;
    window.setFramerateLimit(framerate);

    //font
    sf::Font font;
    if(!font.loadFromFile("Data/pixelFont.TTF")){
        return -1;
    }

    //general parameter of players
    int size = 64;
    
    Player player1 = Player(1);
    player1.loadTexture("Data/Player1.PNG");

    Player player2 = Player(2);
    player2.loadTexture("Data/Player2.PNG");

    //base
    int baseW = 200;
    int baseH = 500;
    
    sf::RectangleShape base1;
    base1.setSize(sf::Vector2f(baseW, baseH));
    base1.setPosition(0, 150);
    base1.setOutlineThickness(5);
    base1.setOutlineColor(sf::Color(235, 86, 75));
    base1.setFillColor(sf::Color(0,0,0,0));

    sf::RectangleShape base2;
    base2.setSize(sf::Vector2f(baseW, baseH));
    base2.setPosition(width-baseW, 150);
    base2.setOutlineThickness(5);
    base2.setOutlineColor(sf::Color(75, 91, 171));
    base2.setFillColor(sf::Color(0,0,0,0));

    //seed of random
    time_t timer;
    time(&timer);
    srand(timer);

    //box
    Box onlyBox = Box();
    onlyBox.initBox(1 + rand()%3);

    //Coin
    Coin onlyCoin = Coin();
    onlyCoin.initCoin();

    //no.
    std::stringstream ss_score1;
    std::stringstream ss_HP1;
    std::string string_score1, string_HP1;
    sf::Text score1, HP1;

    std::stringstream ss_score2;
    std::stringstream ss_HP2;
    std::string string_score2, string_HP2;
    sf::Text score2, HP2;

    score1.setFont(font);
    HP1.setFont(font);
    score1.setCharacterSize(14);
    HP1.setCharacterSize(14);

    score1.setPosition(sf::Vector2f(30, 10));
    HP1.setPosition(sf::Vector2f(30, 24));

    score2.setFont(font);
    HP2.setFont(font);
    score2.setCharacterSize(14);
    HP2.setCharacterSize(14);
    
    score2.setPosition(sf::Vector2f(710, 10));
    HP2.setPosition(sf::Vector2f(710, 24));

    
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }

            //player 1
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::A && (player1.upMove == false && player1.downMove == false))    player1.leftMove = true;
                if(event.key.code == sf::Keyboard::D && (player1.upMove == false && player1.downMove == false))    player1.rightMove = true;
                if(event.key.code == sf::Keyboard::W && (player1.leftMove == false && player1.rightMove == false))    player1.upMove = true;
                if(event.key.code == sf::Keyboard::S && (player1.leftMove == false && player1.rightMove == false))    player1.downMove = true;
            }

            if(event.type == sf::Event::KeyReleased){
                if(event.key.code == sf::Keyboard::A)    player1.leftMove = false;
                if(event.key.code == sf::Keyboard::D)    player1.rightMove = false;
                if(event.key.code == sf::Keyboard::W)    player1.upMove = false;
                if(event.key.code == sf::Keyboard::S)    player1.downMove = false;
            }

            //player 2
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Left && (player2.upMove == false && player2.downMove == false))    player2.leftMove = true;
                if(event.key.code == sf::Keyboard::Right && (player2.upMove == false && player2.downMove == false))    player2.rightMove = true;
                if(event.key.code == sf::Keyboard::Up && (player2.leftMove == false && player2.rightMove == false))    player2.upMove = true;
                if(event.key.code == sf::Keyboard::Down && (player2.leftMove == false && player2.rightMove == false))    player2.downMove = true;
            }

            if(event.type == sf::Event::KeyReleased){
                if(event.key.code == sf::Keyboard::Left)    player2.leftMove = false;
                if(event.key.code == sf::Keyboard::Right)    player2.rightMove = false;
                if(event.key.code == sf::Keyboard::Up)    player2.upMove = false;
                if(event.key.code == sf::Keyboard::Down)    player2.downMove = false;
            }
        }

        sf::Text result;
        result.setFont(font);
        result.setCharacterSize(36);
        result.setPosition(205, 360);
        
        if(player1.score > 400 || player2.score > 400){
            if(player1.score > 400){
                result.setString("PLAYER 1 WINS");
            }else{
                result.setString("PLAYER 2 WIN");
            }
            window.clear(sf::Color(67, 67, 79));
            window.draw(result);
            window.display();
            continue;
        }
        
        if(onlyBox.cVStop(player1) || onlyBox.cVStop(player2)){
            onlyBox.vY = 0;
        }else{
            onlyBox.vY = onlyBox.v0;
        }
        onlyBox.moved(player1);
        onlyBox.moved(player2);
        ////update movement of objects
        //players
        player1.updateMove();
        player2.updateMove();
        player1.interact(player2);

        //coin
        player1.collisionCoin(onlyCoin);
        player2.collisionCoin(onlyCoin);

        onlyBox.box.move(onlyBox.vX, onlyBox.vY);

        if(player1.HP > onlyBox.value && onlyBox.getX() < 200 && onlyBox.getY() >= 150 && onlyBox.getY() <= 650){
            player1.score += onlyBox.value;
            player1.HP -= 2*onlyBox.value / 5;
            onlyBox.initBox(1 + rand()%3);
        }else if(player2.HP > onlyBox.value && onlyBox.getX() > width-baseW-onlyBox.size && onlyBox.getY() >= 150 && onlyBox.getY() <= 650){
            player2.score += onlyBox.value;
            player2.HP -= 2*onlyBox.value / 5;
            onlyBox.initBox(1 + rand()%3);
        }

        player1.upGrade();
        player2.upGrade();

        if(onlyBox.getY() > 880 || onlyBox.getX() > 800 || onlyBox.getX() < 0){
            onlyBox.initBox(1 + rand()%3);
        }
        ss_score1 << player1.score;
        ss_HP1 << player1.HP;
        ss_score1 >> string_score1;
        ss_HP1 >> string_HP1;

        ss_score2 << player2.score;
        ss_HP2 << player2.HP;
        ss_score2 >> string_score2;
        ss_HP2 >> string_HP2;

        score1.setString(string_score1);
        HP1.setString(string_HP1);

        score2.setString(string_score2);
        HP2.setString(string_HP2);

        window.clear(sf::Color(67, 67, 79));

        window.draw(base1);
        window.draw(base2);
        
        window.draw(player1.player);
        window.draw(player2.player);

        window.draw(onlyBox.box);
        window.draw(onlyCoin.coin);

        window.draw(score1);
        window.draw(HP1);
        window.draw(score2);
        window.draw(HP2);

        window.display();

        ss_score1.clear();
        ss_HP1.clear();
        ss_score2.clear();
        ss_HP2.clear();
    }
    window.close();
}
