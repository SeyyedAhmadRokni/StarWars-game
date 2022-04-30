#ifndef _GE_
#define _GE_

#include <bits/stdc++.h>
#include <set>
#include "StarWars.hpp"

using namespace std;

Arrow::Arrow(Point p, string imageAddress, int damage):
    Box(p, ARROW_WIDHT, ARROW_HEIGHT, imageAddress, ARROW_RATE){

    this->damage = damage;
}

bool Arrow::isInScreen(int windowWidth, int windowHeight){
    if (x<=windowWidth && x>=0 
        && y<= windowHeight && windowHeight>=0){
        return true;
    }
    return false;
}

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

bool Item::hasExpired(){
    if (time(NULL) - creationTime > existsDuration){
        return true;
    }
    return false;
}

SpeedItem::SpeedItem(Point position):
    Item(position.x, position.y, SPEED_ITEM_EXISTENCE_TIME,
    GAME_PATH + ITEMS_IMAGES_PATH + "/speed.png"){
}

void SpeedItem::action(Player* player){
    player->getSpeed(duration, speedRatio);
}

GaurdItem::GaurdItem(Point position):
    Item(position.x, position.y, GAURD_ITEM_EXISTENCE_TIME,
    GAME_PATH + ITEMS_IMAGES_PATH + "/gaurd.png"){
}

void GaurdItem::action(Player* player){
    player->getGaurd(duration);
}

#endif