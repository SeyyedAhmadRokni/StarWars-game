#ifndef _BITS_STARWARS_H
#define _BITS_STARWARS_H

#include <bits/stdc++.h>
#include "StarWars.hpp"
#include "Defines.cpp"

Controller::Controller(char up, char down, char left, char right, char shoot){
    keys.insert(std::pair<char, GameKey>(up, UP));
    keys.insert(std::pair<char, GameKey>(down, DOWN));
    keys.insert(std::pair<char, GameKey>(right, RIGHT));
    keys.insert(std::pair<char, GameKey>(left, LEFT));
    keys.insert(std::pair<char, GameKey>(shoot, SHOOT));
}

bool Controller::isAController(char input){
    return keys.count(input);
}
GameKey Controller::getCommand(char input){
    return keys.at(input);
};


Box::Box(int x, int y, int width, int height, 
    std::string imgSource, int rate){
    this->y = y;
    this->x = x;
    this->width = width;
    this->height = height;
    imageSource = imgSource;
    moveRate = rate;
}
Box::Box(Point p, int width, int height, 
    std::string imgSource, int rate){
    this->y = p.y;
    this->x = p.x;
    this->width = width;
    this->height = height;
    imageSource = imgSource;
    moveRate = rate;
}

void Box::moveDown(){
    y+=moveRate;    
}
void Box::moveUp(){
    y-=moveRate;
}
void Box::moveRight(){
    x+=moveRate;
}
void Box::moveLeft(){
    x-=moveRate;
}

// Point Box::PositionToMatchCenters(Box* other){
//     return Point(x+(width - other->width)/2,
//         y+(height - other->height)/2);
// }

Point Box::getPosition(){
    return Point(x,y);
}

int Box::centerDistanceX(Box* other){
    return abs(x+width/2 - (other->x+other->width/2));
}

int Box::centerDistanceY(Box* other){
    return abs(y+height/2 - (other->y+other->height/2));
}

bool Box::hasCollision(Box* other){
    if (centerDistanceX(other) < (other->width + width)/2 &&
        centerDistanceY(other) < (other->height + height)/2){
        return true; 
    }
    return false;
}

Point Box::matchCenterUp(int otherWidth, int otherHeight){//change name
    return Point((2*x + width - otherWidth)/2, y);
}
Point Box::matchCenterDown(int otherWidth, int otherHeight){//cahnge name
    return Point((2*x + width - otherWidth)/2
    ,y + height);
}
void Box::draw(Window* window){
    window->draw_img(imageSource,
        Rectangle(x, y, width, height));
}


Pages::Pages(Window* window){
    this->window = window;
}

Point Pages::getCenterOfPageToShow(){
    return Point((window->get_width() - BUTTON_STANDARD_WIDTH)/2,
        (window->get_height() - BUTTON_STANDARD_HEIGHT)/2);
}
void Pages::showResult(WinnerType winner){
    std::string result;
    switch (winner)
    {
    case ENEMIES:
        result = "Enemies Win :(";
        break;
    
    default:
        result = "Players Win! :)";
        break;
    }
    window->show_text(result, getCenterOfPageToShow(),
        WHITE, GAME_PATH + FONTS_PATH + "/OpenSans.ttf");

}
void Pages::showResultPage(WinnerType winner){
    window->clear();
    window->draw_img(GAME_PATH+BACKGROUND_IMAGES_PATH+"/end.jpg");
    showResult(winner);
    window->update_screen();
    delay(5000);
}


#endif