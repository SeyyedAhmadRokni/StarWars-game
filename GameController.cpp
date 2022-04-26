#ifndef _G_
#define _G_
#include <bits/stdc++.h>
#include "StarWars.hpp"

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

void PlayerManager::PlayerManager::eraseExitedArrows(int windowWidth, int windowHeight){
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->earseExitedArrow(windowWidth,
            windowHeight);
    }
}
void PlayerManager::erase(){
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->earseAllArrows();
        delete players[i];
    }
}

void PlayerManager::doCommand(char key, int windowWidth, int windowHeight){
    for (int i = 0; i < players.size(); i++)
    {
            if (players[i]->hasKey(key)){
                players[i]->doCommand(key, windowWidth, windowHeight);
                break;
            }  
    }
}

void PlayerManager::movePlayersElements(){
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->moveArrows();

    }   
}
void PlayerManager::draw(Window* window){
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->draw(window);
    }
}

void EnemyManager::addMovingEnemy(Point p){
    MovingEnemy* enemy = new MovingEnemy(p.x, p.y, FIRE_RATE);
    enemies.push_back(enemy);
}

void EnemyManager::addFixedEnemy(Point p){
    FixedEnemy* enemy = new FixedEnemy(p.x, p.y, FIRE_RATE);
    enemies.push_back(enemy);
}

void EnemyManager::erase(){
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->earseAllArrows();
        delete enemies[i];
    }
}

void EnemyManager::moveEnemiesElements(Window* window){
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->moveArrows();
        enemies[i]->move(window->get_width());
    }
}

void EnemyManager::draw(Window* window){
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->draw(window);
        enemies[i]->drawArrows(window);
    }
}

std::vector<std::string> Game::readFile(string address){
    std::ifstream file (address);
    vector<string> readed;
    string buf;
    while(getline(cin, buf)){
        readed.push_back(buf);
    }
    return readed;
}

void Game::makeWindow(std::string mapAddress){
    vector<string> gameMap = readFile(mapAddress);
    int windowWidth = gameMap[0].size()*STANDARD_BLOCK_WIDTH
        +(gameMap[0].size()+1)*STANDARD_SEPRATOR_WIDTH;
    int windowHeight = gameMap.size()*STANDARD_BLOCK_HEIGHT
        + (gameMap.size() + 1)*STANDARD_SEPRATOR_HEIGHT;
    window = new Window(windowWidth, windowHeight, GAME_TITLE);
}

void Game::closeGame(){
    enemyManager->erase();
    playerManager->erase();
    delete window;
    exit(0);
}

void Game::doEvent(Event event){
    switch(event.get_type()){
        case Event::QUIT:
            closeGame();
            break;
        case Event::KEY_PRESS:
            playerManager->doCommand(event.get_pressed_key(),
                window->get_width(), window->get_height());
            break;
    }
}

void Game::getInput(){
    if (window->has_pending_event()){
        Event event = window->poll_for_event();
        doEvent(event);
    }
}

void Game::moveElements(){
    playerManager->movePlayersElements();
    enemyManager->moveEnemiesElements(window);
}
void Game::update(){
    getInput();
    moveElements();
}
void Game::draw(){
    enemyManager->draw(window);
    playerManager->draw(window);
}
void Game::run(){
    while(gameIsRunning){
        update();
        draw();
        delay(15);
    }
    closeGame();
}

Point Game::getElementPosition(int i, int j){
    return Point(i*STANDARD_BLOCK_WIDTH+   
        (i+1)*STANDARD_SEPRATOR_WIDTH,
        i*STANDARD_BLOCK_HEIGHT + 
        (i+1)*STANDARD_SEPRATOR_HEIGHT);
}

void Game::addMapElement(char input, Point position){
    switch (input)
    {
    case 'E':
        enemyManager->addFixedEnemy(position);
        break;
    case 'M':
        enemyManager->addMovingEnemy(position);
        break;
    case 'S':

        break;
    case 'P':
        playerManager->addPlayer(position);
        break;
    default:
        break;
    }
}

void Game::addMapsElements(std::string address){
    vector<string> gameMap = readFile(address);
    for (int i = 0; i < gameMap.size(); i++)
    {
        for (int j = 0; j < gameMap[i].size(); j++)
        {
            Point position = getElementPosition(i, j);
            addMapElement(gameMap[i][j], position);
        }
    }
}
Game::Game(std::string mapAddress){
    makeWindow(mapAddress);
    addMapsElements(mapAddress);
}


#endif