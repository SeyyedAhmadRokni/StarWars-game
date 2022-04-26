#ifndef _BITS_STARWARS_H
#define _BITS_STARWARS_H

#include <bits/stdc++.h>
#include "StarWars.hpp"
#include "Defines.cpp"


Enemy::Enemy(int x, int y, int width, int height, std::string imgAddress, int rate )
    : Box(x, y, width, height, imgAddress, rate){
}
void Enemy::shoot(){
    Arrow* arrow = new 
        Arrow(this->matchCenterDown(FIRE_WIDHT, FIRE_HEIGHT), 
            FIRE_DAMAGE, FIRE_RATE);
    arrows.push_back(arrow);
}
void Enemy::moveArrows(){
    for (int i = 0; i < arrows.size(); i++)
    {
        arrows[i]->moveDown();
    }
}
void Enemy::drawArrows(Window* window){
    for (int i = 0; i < arrows.size(); i++)
    {
        arrows[i]->draw(window);
    }
}

void Enemy::draw(Window* window){
    drawArrows(window);
    window->draw_rect(Rectangle(x, y, width, height));
}

void Enemy::earseExitedArrow(int windowWidth,
    int windowHeight){
    for (int i = 0; i < arrows.size(); i++)
    {
        if (!arrows[i]->isInScreen(windowWidth, windowHeight)){
            delete arrows[i];
            arrows.erase(arrows.begin()+i);
        }
    }
}

void Enemy::earseAllArrows(){
    for (int i = 0; i < arrows.size(); i++)
    {
        delete arrows[i];
    }
}

MovingEnemy::MovingEnemy(int x, int y, int rate=10)
    :Enemy(x, y, STANDARD_BLOCK_WIDTH
    ,STANDARD_BLOCK_HEIGHT, imageAddress, rate) {

}
bool MovingEnemy::moveIsPossible(int windowWidth){
    if (moveDiretion == RIGHT){
        if (x+moveRate+width <= windowWidth){
            return true;
        }
    }
    else {
        if (x-moveRate >= 0){
            return true;
        }
    }
    return false;
}

void MovingEnemy::moveToDirection(){
    switch (moveDiretion){
        case LEFT:
            this->moveLeft();
            break;
        case RIGHT:
            this->moveRight();
            break;
    }
}

void MovingEnemy::changeDirection(){
    if (moveDiretion == RIGHT){
        moveDiretion = LEFT;
    }
    else{
        moveDiretion= RIGHT;
    }
}

void MovingEnemy::move(int windowWidth){
    if (!moveIsPossible(windowWidth)){
        changeDirection();
    }
    moveToDirection();
}

FixedEnemy::FixedEnemy(int x, int y, int rate=10)
    :Enemy(x, y, STANDARD_BLOCK_WIDTH
    ,STANDARD_BLOCK_HEIGHT, imageAddress, rate){

}

void FixedEnemy::move(int windowWidth){

}
#endif