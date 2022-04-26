#include <bits/stdc++.h>
#include "StarWars.hpp"
#include "Defines.cpp"

Arrow::Arrow(int x, int y, int damage = 100, int rate = 6):
    Box(x, y, FIRE_WIDHT, FIRE_HEIGHT, 
        imageAddress, rate){
    this->damage = damage;
}
Arrow::Arrow(Point p, int damage = 100, int rate = 6):
    Box(p, FIRE_WIDHT, FIRE_HEIGHT, 
        imageAddress, rate){

    this->damage = damage;
}

bool Arrow::isInScreen(int windowWidth, int windowHeight){
    if (x<=windowWidth && x>=0 
        && y<= windowHeight && windowHeight>=0){
        return true;
    }
    return false;
}

//--------------------------------------------------

Item::Item(int x, int y, int sec, std::string imgAddress): Box(x, y, ITEM_WIDTH,
    ITEM_HEIGHT, imgAddress, 0){
    time(&creationTime);
    existsDuration = sec;
}
bool Item::isDeleteTime(){
    if (time(NULL)-creationTime > existsDuration){
        return true;
    }
    return false;
}

void SpeedItem::action(Player* player){
    player->getSpeed(duration, speedRatio);
}

void PowerItem::action(Player* player){
    player->getGaurd(duration);
}