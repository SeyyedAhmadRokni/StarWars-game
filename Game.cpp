#ifndef _G_
#define _G_
#include <bits/stdc++.h>
#include "StarWars.hpp"
#include "Defines.cpp"

using namespace std;


void Game::readMap(string address){
    std::ifstream file (address);
    string buf;
    while(getline(file, buf)){
        map.push_back(buf);
    }
    file.close();
}

void Game::makeWindow(std::string mapAddress){
    int windowWidth = map[0].size()*STANDARD_BLOCK_WIDTH
        +(map[0].size()+1)*STANDARD_SEPRATOR_WIDTH;
    int windowHeight = map.size()*STANDARD_BLOCK_HEIGHT
        + (map.size() + 1)*STANDARD_SEPRATOR_HEIGHT;
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
    playerManager->moveElements();
    enemyManager->moveElements(window->get_width());
}

void Game::update(){
    getInput();
    moveElements();
    enemyManager->enemiesShoot();
    doCollisions();
    itemManager->deleteExpiredItems();
    playerManager->disableExpiredItems();
    if(isGameEnded()){
        gameIsRunning = false;
        identifyWinner();
    }
}

void Game::drawBackGround(){
    string backgroundAddress = GAME_PATH +
        BACKGROUND_IMAGES_PATH + "/space.png";
    window->draw_img(backgroundAddress);
}

void Game::draw(){
    window->clear();
    drawBackGround();
    enemyManager->draw(window);
    playerManager->draw(window);
    itemManager->draw(window);
    window->update_screen();
}

void Game::run(){
    while(gameIsRunning){
        update();
        draw();
        delay(15);
    }
    pages->showResultPage(winner);
    closeGame();
}

Point Game::getElementPosition(int x, int y){
    return Point(x*STANDARD_BLOCK_WIDTH+   
        (x+1)*STANDARD_SEPRATOR_WIDTH,
        y*STANDARD_BLOCK_HEIGHT + 
        (y+1)*STANDARD_SEPRATOR_HEIGHT);
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
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            Point elementPosition = getElementPosition(j, i);
            addMapElement(map[i][j], elementPosition);
        }
    }
}

void Game::doCollisions(){
    vector<Point> newItemsPositions = collisionController.getAddItemsPosition
    (playerManager->getArrows(), enemyManager->getEnemies());
    collisionController.controlAllCollisions(
        playerManager->getPlayers(), enemyManager->getEnemies(),
        playerManager->getArrows(), enemyManager->getArrows(),
        itemManager->getItems()
    );
    itemManager->addItemIfPossible(newItemsPositions);
}

void Game::setGameLevel(string gameLevel){
    if (gameLevel == "E"){
        this->gameLevel = EASY;
    }
    else if (gameLevel == "M"){
        this->gameLevel = MEDIUM;
    }
    else if (gameLevel == "H"){
        this->gameLevel = HARD;
    }
}

Game::Game(std::string mapAddress, std::string gameLevel){
    readMap(mapAddress);
    makeWindow(mapAddress);
    pages = new Pages(window);
    setGameLevel(gameLevel);
    enemyManager = new EnemyManager(map.size(), this->gameLevel);
    addMapsElements(mapAddress);
}

bool Game::isGameEnded(){
    if (enemyManager->allEnemiesAreDead() || 
        playerManager->allPlayersAreDead()){
        return true;
    }
    return false;
}

void Game::identifyWinner(){
    if (enemyManager->allEnemiesAreDead()){
        winner = PLAYERS;
    }
    else{
        winner = ENEMIES;
    }
}

#endif