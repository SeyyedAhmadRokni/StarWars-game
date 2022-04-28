#ifndef _C_
#define _C_

#include <bits/stdc++.h>
#include "StarWars.hpp"
#include "Defines.cpp"

using namespace std;

Controller PlayerManager::getDefaultsControllers(int playerN){
    switch (playerN)
    {
    case 1:
        return Controller ('w', 's', 'a', 'd', ' ');
        break;
    default:
        return Controller ('i', 'k', 'j', 'l', 'o');
    }
}

void PlayerManager::addPlayer(Point p){
    Controller control = getDefaultsControllers(players.size()+1);
    Player *player = new Player(control, p);
    players.push_back(player);
}

void PlayerManager::doCommand(char key, int windowWidth, int windowHeight){
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->hasKey(key)){
            players[i]->doCommand(key, windowWidth, windowHeight,
                arrows);
            break;
        }  
    }
}

void PlayerManager::moveArrows(){
    for (int i = 0; i < arrows.size(); i++)
    {
        arrows[i]->moveUp();
    }
}

void PlayerManager::moveElements(){
     moveArrows();  
}

void PlayerManager::drawArrows(Window* window){
    for (int i = 0; i < arrows.size(); i++)
    {
        arrows[i]->draw(window);
    }
}

void PlayerManager::drawPlayers(Window* window){
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->draw(window);
    }
}

void PlayerManager::draw(Window* window){
    drawArrows(window);
    drawPlayers(window); 
}

void PlayerManager::eraseExitedArrow(int windowWidth,
    int windowHeight){
    for (int i = 0; i < arrows.size(); i++)
    {
        if (!arrows[i]->isInScreen(windowWidth, windowHeight)){
            delete arrows[i];
            arrows.erase(arrows.begin()+i);
        }
    }
}

void PlayerManager::eraseAllArrows(){

    for (int i = 0; i < arrows.size(); i++)
    {
        delete arrows[i];
    } 
}

void PlayerManager::eraseAllPlayers(){
    for (int i = 0; i < players.size(); i++)
    {
        delete players[i];
    }
}

void PlayerManager::erase(){
    eraseAllArrows();
    eraseAllPlayers();
}

vector<Arrow*>& PlayerManager::getArrows(){
    return arrows;
}

bool PlayerManager::allPlayersAreDead(){
    if (players.size() == 0){
        return true;
    }
    return false;
}

vector<Player*>& PlayerManager::getPlayers(){
    return players;
}

void PlayerManager::disableExpiredItems(){
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->disableExpiredItems();
    }
}

#endif