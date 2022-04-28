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

void PlayerManager::deleteShotedPlayers(
    std::vector<Arrow*>& enemiesArrows){
    for (int i = 0; i < players.size(); i++)
    {
        for (int j = 0; j < enemiesArrows.size(); j++)
        {
            if (players[i]->hasCollision(enemiesArrows[j])){
                delete players[i];
                players.erase(players.begin() + i);

                delete enemiesArrows[j];
                enemiesArrows.erase(enemiesArrows.begin() + j);
                break;
            }
        }
    }
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

void EnemyManager::deleteShotedEnemies(vector<Arrow*>& playerArrows){
    for (int i = 0; i < enemies.size(); i++)
    {
        for (int j = 0; j < playerArrows.size(); j++)
        {
            if (enemies[i]->hasCollision(playerArrows[j])){
                delete enemies[i];
                enemies.erase(enemies.begin() + i);

                delete playerArrows[j];
                playerArrows.erase(playerArrows.begin() + j);
            }
        }
    }
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
    doCollision();
    if(gameIsEnded()){
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

void Game::doCollision(){
    enemyManager->deleteShotedEnemies(
        playerManager->getArrows()
    );
    playerManager->deleteShotedPlayers(
        enemyManager->getArrows()
    );
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

bool Game::gameIsEnded(){
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