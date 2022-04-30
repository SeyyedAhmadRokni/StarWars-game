#ifndef _BITS_STARWARS_H
#define _BITS_STARWARS_H

#include <bits/stdc++.h>
#include "StarWars.hpp"
#include "Defines.cpp"

Player::Player(Controller cont, Point p, int playerNumber)
    :Box(p, STANDARD_BLOCK_WIDTH, STANDARD_BLOCK_HEIGHT,
    GAME_PATH + PLAYER_IMAGES_PATH + "/"+ to_string(playerNumber) + ".png",
    PLAYER_MOVE_RATE){

    controls = new Controller(cont);
    gaurededImage = GAME_PATH + PLAYER_IMAGES_PATH + "/"+
        to_string(playerNumber) + "_gaurded.png";
}

bool Player::hasKey(char released){
    return controls->isAController(released);
}
Arrow* Player::shoot(){
    std::string imageAddress = GAME_PATH + PLAYER_IMAGES_PATH +
        "/fire.png";
    Arrow* arrow = new Arrow(
            matchCenterUp(ARROW_WIDHT, ARROW_HEIGHT),
            imageAddress);
    return arrow;
}
void Player::getGaurd(int duration){
    if (!hasGaurdItem){
        swap(imageSource, gaurededImage);
    }
    hasGaurdItem = true;
    time(&getGaurdTime);
    gaurdDuration = duration;
}
void Player::getSpeed(int duration, int ratio){
    hasBonusSpeed = true;
    moveRate = ratio * PLAYER_MOVE_RATE;
    time(&getSpeedTime);
    speedDuration = duration;
}

bool Player::isMovePossible(GameKey direction, int windowWidth, int windowHeight){
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

void Player::manageKeyRelease(char input){

    GameKey direction = controls->getCommand(input);

        switch (direction){
            case UP:
                movingUP = false;
                break;
            case DOWN:
                movingDown = false;
                break;
            case LEFT:
                movingLeft = false;
                break;
            case RIGHT:
                movingRight = false;
                break;
        }
}

void Player::manageKeyPress(char input, Window* window, std::vector<Arrow*>& arrows){

    GameKey direction = controls->getCommand(input);

        switch (direction){
            case UP:
                    movingUP = true;
                break;
            case DOWN:
                    movingDown = true;
                break;
            case LEFT:
                    movingLeft = true;
                break;
            case RIGHT:
                    movingRight = true;
                break;
            case SHOOT:
                arrows.push_back(this->shoot());
                window->play_sound_effect(GAME_PATH + SOUNDS_PATH +
                    "/fire_sound.wav");
                break;
        }
}


void Player::move(int windowWidth, int windowHeight){
    if (movingDown){
        if (isMovePossible(DOWN, windowWidth, windowHeight))
            moveDown();
    }
    if (movingLeft){
        if (isMovePossible(LEFT, windowWidth, windowHeight))
            moveLeft();
    }
    if (movingRight){
        if (isMovePossible(RIGHT, windowWidth, windowHeight))
            moveRight();
    }
    if (movingUP){
        if (isMovePossible(UP, windowWidth, windowHeight))
            moveUp();
    }
}


void Player::draw(Window* window){
    window->draw_img(imageSource, Rectangle(x, y, width, height));//imageAddress->imageSource
}

bool Player::hasGaurd(){
    return hasGaurdItem;
}

void Player::disableSpeedItem(){
    if (hasBonusSpeed && 
        time(NULL)-getSpeedTime > speedDuration){
        hasBonusSpeed = false;
        moveRate = PLAYER_MOVE_RATE; 
    }
}

void Player::disableGaurdItem(){
    if (hasGaurdItem &&
        time(NULL)-getGaurdTime > gaurdDuration){
        hasGaurdItem = false;
        swap(gaurededImage, imageSource);
    }
}

void Player::disableExpiredItems(){
    disableSpeedItem();
    disableGaurdItem();
}


#endif