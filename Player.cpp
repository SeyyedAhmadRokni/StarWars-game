#ifndef _BITS_STARWARS_H
#define _BITS_STARWARS_H

#include <bits/stdc++.h>
#include "StarWars.hpp"
#include "Defines.cpp"

void Player::lossGaurd(){
    if (time(NULL) - getGaurdTime > gaurdDuration){
        hasGaurdItem = false;
    }
}
void Player::lossBonusSpeed(){
    if (time(NULL)- getSpeedTime > speedDuration){
        hasBonusSpeed = false;
    }
}
Player::Player(Controller cont, Point p)
    :Box(p, STANDARD_BLOCK_WIDTH, STANDARD_BLOCK_HEIGHT,
    GAME_PATH + PLAYER_IMAGES_PATH +
    "/1.png", PLAYER_MOVE_RATE){

    controls = new Controller(cont);
}

Player::Player(char up, char down, char left, char right, char shoot)
    :Box(x, y, STANDARD_BLOCK_WIDTH, STANDARD_BLOCK_HEIGHT,
    GAME_PATH + PLAYER_IMAGES_PATH +
    "/1.png", PLAYER_MOVE_RATE){
    controls = new Controller(up, down, left, right, shoot);
}
bool Player::hasKey(char released){
    return controls->isAController(released);
}
void Player::shoot(){
    std::string imageAddress = GAME_PATH + THINGS_IMAGES_PATH +
        "/player_fire.png";
    Arrow* arrow = new Arrow(
            matchCenterUp(FIRE_WIDHT, FIRE_HEIGHT),
            imageAddress);
    arrows.push_back(arrow);
}
void Player::getGaurd(int duration){
    hasGaurdItem = true;
    time(&getGaurdTime);
    gaurdDuration = duration;
}
void Player::getSpeed(int duration, int ratio){
    hasBonusSpeed = true;
    moveRate = ratio;
    time(&getSpeedTime);
    speedDuration = duration;
}

void Player::moveArrows(){
    for (int i = 0; i < arrows.size(); i++)
    {
        arrows[i]->moveUp();
    }
}

void Player::drawArrows(Window* window){
    for (int i = 0; i < arrows.size(); i++)
    {
        arrows[i]->draw(window);
    }
}

bool Player::moveIsPossible(GameKey direction, int windowWidth, int windowHeight){
    switch(direction){
        case UP:
            if (y-moveRate<0){
                return false;
            }
            break;
        case DOWN:
            if (y+moveRate+height > windowHeight){
                return false;
            }
            break;
        case RIGHT:
            if (x+moveRate+width > windowWidth){
                return false;
            }
            break;
        case LEFT:
            if (x-moveRate < 0){
                return false;
            }
            break;
    }
    return true;

}

void Player::doCommand(char input, int windowWidth, int windowHeight){
    GameKey direction = controls->getCommand(input);
    switch (direction){
        case UP:
            if (moveIsPossible(direction, windowWidth, windowHeight))
                this->moveUp();
            break;
        case DOWN:
            if (moveIsPossible(direction, windowWidth, windowHeight))
                this->moveDown();
            break;
        case LEFT:
            if (moveIsPossible(direction, windowWidth, windowHeight))
                this->moveLeft();
            break;
        case RIGHT:
            if (moveIsPossible(direction, windowWidth, windowHeight))
                this->moveRight();
            break;
        case SHOOT:
            this->shoot();
            break;
    }
}
void Player::draw(Window* window){
    drawArrows(window);
    window->draw_img(imageSource, Rectangle(x, y, width, height));//imageAddress->imageSource
}

void Player::eraseExitedArrow(int windowWidth,
    int windowHeight){
    for (int i = 0; i < arrows.size(); i++)
    {
        if (!arrows[i]->isInScreen(windowWidth, windowHeight)){
            delete arrows[i];
            arrows.erase(arrows.begin()+i);
        }
    }
}

void Player::eraseAllArrows(){
    for (int i = 0; i < arrows.size(); i++)
    {
        delete arrows[i];
    } 
}

#endif