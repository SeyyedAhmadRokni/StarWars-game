#ifndef _E_
#define _E_

#include <bits/stdc++.h>
#include "StarWars.hpp"
#include "Defines.cpp"

void EnemyManager::addMovingEnemy(Point p){
    MovingEnemy* enemy = new MovingEnemy(p.x, p.y);
    enemies.push_back(enemy);
}

std::vector<Arrow*>& EnemyManager::getArrows(){
    return arrows;
}

void EnemyManager::addFixedEnemy(Point p){
    FixedEnemy* enemy = new FixedEnemy(p.x, p.y);
    enemies.push_back(enemy);
}

void EnemyManager::eraseAllArrows(){
    for (int i = 0; i < arrows.size(); i++)
    {
        delete arrows[i];
    }
}

void EnemyManager::eraseAllEnemies(){
    for (int i = 0; i < enemies.size(); i++)
    {
        delete enemies[i];
    }
}

void EnemyManager::erase(){
    eraseAllArrows();
    eraseAllEnemies();
}

void EnemyManager::moveArrows(){
    for (int i = 0; i < arrows.size(); i++)
    {
        arrows[i]->moveDown();
    }
}

void EnemyManager::moveEnemies(int windowWidth){
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->move(windowWidth);
    }
}

void EnemyManager::moveElements(int windowWidth){
    moveEnemies(windowWidth);
    moveArrows();
}

void EnemyManager::drawArrows(Window* window){
    for (int i = 0; i < arrows.size(); i++)
    {
        arrows[i]->draw(window);
    }
}

void EnemyManager::drawEnemies(Window* window){
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->draw(window);
    }
}

void EnemyManager::draw(Window* window){
    drawEnemies(window);
    drawArrows(window);
}

void EnemyManager::eraseExitedArrows(int windowWidth, int windowHeight){
    for (int i = 0; i < arrows.size(); i++)
    {
        if (!arrows[i]->isInScreen(windowWidth, windowHeight)){
            delete arrows[i];
            arrows.erase(arrows.begin()+i);
        }
    }
}

EnemyManager::EnemyManager(int columnsNumber, DifficultyLevel level){
    enemyShootTimer = new EnemyShootTimer(columnsNumber, level);
}

bool EnemyManager::isInColumn(Enemy* enemy, int col){
    Point position = enemy->getPosition();
    int colStart = col*STANDARD_BLOCK_WIDTH +
        (col+1)*STANDARD_SEPRATOR_WIDTH;
    if (position.x >= colStart && position.x <= colStart+STANDARD_BLOCK_WIDTH){
        return true;
    }
    return false;
}

void EnemyManager::enemiesShoot(){
    if (!enemyShootTimer->isTimeToShot()){
        return;
    }
    vector<int> columnsToShot = enemyShootTimer->getColumnsToShoot();
    for (int i = 0; i < columnsToShot.size(); i++)
    {
        for (int j = 0; j < enemies.size(); j++)
        {
            if(!isInColumn(enemies[j], columnsToShot[i])){
                arrows.push_back(enemies[j]->shoot());
            }
        }
    }
}

bool EnemyManager::allEnemiesAreDead(){
    if (enemies.size() == 0){
        return true;
    }
    return false;
}

vector<Enemy*>& EnemyManager::getEnemies(){
    return enemies;
}




#endif