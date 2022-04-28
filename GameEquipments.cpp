#ifndef _GE_
#define _GE_

#include <bits/stdc++.h>
#include <set>
#include "StarWars.hpp"
#include "Defines.cpp"

using namespace std;

Arrow::Arrow(int x, int y, string imageAddress, int damage):
    Box(x, y, FIRE_WIDHT, FIRE_HEIGHT, imageAddress, FIRE_RATE){
    this->damage = damage;
}

Arrow::Arrow(Point p, string imageAddress, int damage):
    Box(p, FIRE_WIDHT, FIRE_HEIGHT, imageAddress, FIRE_RATE){

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

bool Item::hasExpired(){
    if (time(NULL) - creationTime > existsDuration){
        return true;
    }
    return false;
}

SpeedItem::SpeedItem(Point position):
    Item(position.x, position.y, SPEED_ITEM_EXISTS_TIME,
    GAME_PATH + THINGS_IMAGES_PATH + "/speed.png"){
}

void SpeedItem::action(Player* player){
    player->getSpeed(duration, speedRatio);
}

GaurdItem::GaurdItem(Point position):
    Item(position.x, position.y, GAURD_ITEM_EXISTS_TIME,
    GAME_PATH + THINGS_IMAGES_PATH + "/gaurd.png"){
}

void GaurdItem::action(Player* player){
    player->getGaurd(duration);
}

//----------------------------------

Button::Button(string title, Point position):Box(position, 
    BUTTON_STANDARD_WIDTH, BUTTON_STANDARD_HEIGHT){
    this->title = title;
}

bool Button::isInClicked(Point mousPosition){
    if (mousPosition.x >x && mousPosition.y < x+width &&
        mousPosition.y >y && mousPosition.y < y+height){
        return true;
    }
    return false;
}

void Button::draw(Window* window){
    window->fill_rect(Rectangle(x, y, width, height), BLUE);
    window->show_text(title, Point(x, y), WHITE,
    GAME_PATH + FONTS_PATH + "/OpenSans.ttf");
}
#endif