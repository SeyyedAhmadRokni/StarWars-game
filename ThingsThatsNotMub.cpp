#include <bits/stdc++.h>
#include <StarWars.hpp>
#include "Classes.cpp"

Arrow::Arrow(int x, int y, int damage = 100, int rate = 6):
    Box(x, y, FIRE_WIDHT, FIRE_HEIGHT, 
        imageAddress, rate){
    this->damage = damage;
}
Arrow::Arrow(Point p, int damage = 100, int rate = 6):
    Box(p, FIRE_WIDHT, FIRE_HEIGHT, 
        imageAddress, rate
    this->damage = damage;
}
void Arrow::draw(Window* window){
    window->draw_img(imageAddress,
        Rectangle(x, y, width, height));
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

void Item::draw(Window* window){
    window->draw_img(imageSource, Rectangle(x, y, width, height));
}

virtual Item:void action(Player* player) = 0;

void SpeedItem::action(Player* player){
    player->getSpeed(duration, speedRatio);
}

void PowerItem::action(Player* player){
    player->getGaurd(duration);
}

//------
Enemy::Enemy(int x, int y, int width, int height, std::string imgAddress, int rate )
    : Box(x, y, width, height, imgAddress, rate){
}
void Enemy::shoot(){
    Arrow* arrow = new 
        Arrow(this->matchCenterDown(FIRE_WIDHT, FIRE_HEIGHT));
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
virtual Enemy::void move(int windowWidth) = 0;


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

void MovingEnemy::move(const int windowWidth){
    if (!moveIsPossible(windowWidth)){
        changeDirection();
    }
    moveToDirection();
}

void MovingEnemy::draw(Window* window){
    window->draw_img(imageAddress,
        Rectangle(x, y, width, height));
}
