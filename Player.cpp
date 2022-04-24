
#include <bits/stdc++.h>
#include <StarWars.hpp>

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
Player::Player(Controller cont, int x, int y)
    :Box(x, y, STANDARD_BLOCK_WIDTH, STANDARD_BLOCK_HEIGHT,
    imageAddress, PLAYER_MOVE_RATE){
    controls = new Controller(cont);
}

Player::Player(char up, char down, char left, char right, char shoot)
    :Box(x, y, STANDARD_BLOCK_WIDTH, STANDARD_BLOCK_HEIGHT,
    imageAddress, PLAYER_MOVE_RATE){
    controls = new Controller(up, down, left, right, shoot);
}
bool Player::hasKey(char released){
    return controls->isAController(released);
}
void Player::shoot(){
    Arrow* arrow = new Arrow(
            this->matchCenterUp(FIRE_WIDHT, FIRE_HEIGHT));
    arrows.push_back(arrow);
}
void Player::getGaurd(int duration){
    hasGaurdItem = true;
    time(&getGaurdTime);
    gaurdDuration = duration;
}
void Player::getSpeed(int duration, int ratio){
    hasBonusSpeed = true;
    speedRatio = ratio;
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
bool Player::moveIsPossible(GameKeys direction, int windowWidth, int windowHeight){
    switch(direction){
        case UP:
            if (y-speedRatio<0){
                return false;
            }
            break;
        case DOWN:
            if (y+speedRatio > windowHeight){
                return false;
            }
            break;
        case RIGHT:
            if (x+speedRatio > windowWidth){
                return false;
            }
            break;
        case LEFT:
            if (x-speedRatio < 0){
                return false;
            }
            break;
    }
    return true;

}
void Player::doCommand(char input, int windowWidth, int windowHeight){
    switch (controls->getCommand(input)){
        case UP:
            if (moveIsPossible)
                this->moveUp();
            break;
        case DOWN:
            if (moveIsPossible)
                this->moveDown();
            break;
        case LEFT:
            if (moveIsPossible)
                this->moveLeft();
            break;
        case RIGHT:
            if (moveIsPossible)
                this->moveRight();
            break;
        case SHOOT:
            this->shoot();
            break;
    }
}