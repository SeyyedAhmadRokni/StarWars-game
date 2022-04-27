#ifndef _G_
#define _G_
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

void PlayerManager::PlayerManager::eraseExitedArrows(int windowWidth, int windowHeight){
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->eraseExitedArrow(windowWidth,
            windowHeight);
    }
}
void PlayerManager::erase(){
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->eraseAllArrows();
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
    MovingEnemy* enemy = new MovingEnemy(p.x, p.y);
    enemies.push_back(enemy);
}

void EnemyManager::addFixedEnemy(Point p){
    FixedEnemy* enemy = new FixedEnemy(p.x, p.y);
    enemies.push_back(enemy);
}

void EnemyManager::erase(){
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->eraseAllArrows();
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
                enemies[j]->shoot();
            }
        }
    }
}

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
    playerManager->movePlayersElements();
    enemyManager->moveEnemiesElements(window);
}
void Game::update(){
    getInput();
    moveElements();
    enemyManager->enemiesShoot();
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
    window->update_screen();
}
void Game::run(){
    while(gameIsRunning){
        update();
        draw();
        delay(15);
    }
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
    setGameLevel(gameLevel);
    enemyManager = new EnemyManager(map.size(), this->gameLevel);
    addMapsElements(mapAddress);
}



#endif