#ifndef _ENEMIES_
#define _ENEMIES_

#include <bits/stdc++.h>
#include "Defines.hpp"
#include "BasicStructures.hpp"
#include "rsdl.hpp"
#include "Arrow.hpp"

class Enemy : public Box
{
private:
    int health;

protected:
    EnemyType enemyType;

public:
    Enemy(int x, int y, int width, int height,
          std::string imgAddress, int rate);
    virtual void move(int windowWidth) = 0;
    virtual Arrow *shoot();
    EnemyType getType();
};

class MovingEnemy : public Enemy
{
private:
    GameKey moveDiretion = RIGHT;

public:
    MovingEnemy(int x, int y, int rate = MOVING_ENEMY_MOVE_RATE);
    bool moveIsPossible(int windowWidth);
    void moveToDirection();
    void changeDirection();
    void move(const int windowWidth);
};

class FixedEnemy : public Enemy
{
private:
public:
    FixedEnemy(int x, int y);
    void move(int windowWidth);
};

class HostageShip : public Enemy
{
private:
public:
    HostageShip(int x, int y);
    void move(int windowWidth);
    Arrow *shoot();
};

#endif