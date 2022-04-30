#ifndef _BITS_STARWARS_H
#define _BITS_STARWARS_H

#include <bits/stdc++.h>
#include "StarWars.hpp"
#include "Defines.cpp"


Enemy::Enemy(int x, int y, int width, int height, std::string imgAddress, int rate )
    : Box(x, y, width, height, imgAddress, rate){
}

Arrow* Enemy::shoot(){
    std::string imageAddress = GAME_PATH + ENEMY_IMAGES_PATH +
        "/fire.png";
    Arrow* arrow = new 
        Arrow(this->matchCenterDown(FIRE_WIDHT, FIRE_HEIGHT),
        imageAddress);
    return arrow;
}

MovingEnemy::MovingEnemy(int x, int y, int rate):
    Enemy(x, y, STANDARD_BLOCK_WIDTH,
    STANDARD_BLOCK_HEIGHT, GAME_PATH + ENEMY_IMAGES_PATH +
    "/moving.png", rate) {

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

FixedEnemy::FixedEnemy(int x, int y)
    :Enemy(x, y, STANDARD_BLOCK_WIDTH,
    STANDARD_BLOCK_HEIGHT, GAME_PATH +
    ENEMY_IMAGES_PATH +"/fixed.png" , 0){

}

void FixedEnemy::move(int windowWidth){

}
#endif