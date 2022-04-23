#include <bits/stdc++.h>
#include <StarWars.hpp>
#include "Classes.cpp"
#include "Generals.cpp"

class Arrow:public Box{
private:
    int damage;
    std::string imageAddress = GAME_PATH +
        PLAYER_IMAGES_PATH + "fire.png";
public:
    Arrow(int x, int y, int damage = 100, int rate = 6):
        Box(x, y, FIRE_WIDHT, FIRE_HEIGHT, 
            imageAddress, rate){
        this->damage = damage;
    }
    Arrow(Point p, int damage = 100, int rate = 6):
        Box(p, FIRE_WIDHT, FIRE_HEIGHT, 
            imageAddress, rate){
        this->damage = damage;
    }
    void draw(Window* window){
        window->draw_img(imageAddress,
            Rectangle(x, y, width, height));
    }
};
