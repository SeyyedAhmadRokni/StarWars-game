#ifndef _BITS_STARWARS_H
#define _BITS_STARWARS_H

#include <bits/stdc++.h>
#include "StarWars.hpp"

Enemy::Enemy(int x, int y, int width, int height, std::string imgAddress, int rate)
    : Box(x, y, width, height, imgAddress, rate)
{
}

Arrow *Enemy::shoot()
{
    std::string imageAddress = GAME_PATH + ENEMY_IMAGES_PATH +
                               "/fire.png";
    Arrow *arrow = new Arrow(this->matchDownCenter(ARROW_WIDHT, ARROW_HEIGHT),
                             imageAddress);
    return arrow;
}

EnemyType Enemy::getType()
{
    return enemyType;
}

MovingEnemy::MovingEnemy(int x, int y, int rate) : Enemy(x, y, STANDARD_BLOCK_WIDTH,
                                                         STANDARD_BLOCK_HEIGHT, GAME_PATH + ENEMY_IMAGES_PATH + "/moving.png", rate)
{
    enemyType = MOVING;
}

bool MovingEnemy::moveIsPossible(int windowWidth)
{
    if (moveDiretion == RIGHT)
    {
        if (x + moveRate + width <= windowWidth)
        {
            return true;
        }
    }
    else
    {
        if (x - moveRate >= 0)
        {
            return true;
        }
    }
    return false;
}

void MovingEnemy::moveToDirection()
{
    switch (moveDiretion)
    {
    case LEFT:
        this->moveLeft();
        break;
    case RIGHT:
        this->moveRight();
        break;
    }
}

void MovingEnemy::changeDirection()
{
    if (moveDiretion == RIGHT)
    {
        moveDiretion = LEFT;
    }
    else
    {
        moveDiretion = RIGHT;
    }
}

void MovingEnemy::move(int windowWidth)
{
    if (!moveIsPossible(windowWidth))
    {
        changeDirection();
    }
    moveToDirection();
}

FixedEnemy::FixedEnemy(int x, int y)
    : Enemy(x, y, STANDARD_BLOCK_WIDTH,
            STANDARD_BLOCK_HEIGHT, GAME_PATH + ENEMY_IMAGES_PATH + "/fixed.png", 0)
{
    enemyType = FIXED;
}

void FixedEnemy::move(int windowWidth)
{
}

HostageShip::HostageShip(int x, int y)
    : Enemy(x, y, STANDARD_BLOCK_WIDTH,
            STANDARD_BLOCK_HEIGHT, GAME_PATH + ENEMY_IMAGES_PATH + "/hostage.png", 0)
{
    enemyType = HOSTAGE_SHIP;
}

void HostageShip::move(int windowWidth)
{
}

Arrow *HostageShip::shoot()
{
}
#endif