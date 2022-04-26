#ifndef _BITS_STARWARS_H
#define _BITS_STARWARS_H

#include <bits/stdc++.h>
#include <StarWars.hpp>
#include "Classes.cpp"

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
    std::string imgSource, int rate = 10){
    this->y = y;
    this->x = x;
    this->width = width;
    this->height = height;
    imageSource = imgSource;
    moveRate = rate;
}
Box::Box(Point p, int width, int height, 
    std::string imgSource, int rate = 10){
    this->y = p.y;
    this->x = p.x;
    this->width = width;
    this->height = height;
    imageSource = imgSource;
    moveRate = rate;
}
void Box::setLoc(Point p){
    x = p.x;
    y = p.y;
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

Point Box::matchCenterUp(int otherWidth, int otherHeight){//change name
    return Point((x + width - otherWidth)/2, y);
}
Point Box::matchCenterDown(int otherWidth, int otherHeight){//cahnge name
    return Point((x + width - otherWidth)/2
    ,y + height);
}
virtual void Box::draw(Window* window)=0;
#endif