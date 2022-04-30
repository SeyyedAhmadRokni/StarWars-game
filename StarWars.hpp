#ifndef _m_
#define _m_
#include <bits/stdc++.h>
#include "rsdl.hpp"
#include "Defines.hpp"
#include "BasicStructures.hpp"
#include "Enemies.hpp"
#include "Items.hpp"
#include "Arrow.hpp"
#include "Managers.hpp"


using namespace std;


class Game{
private:
    Window* window;
    WinnerType winner;
    int columnsNumber;
    bool gameIsRunning = true;
    DifficultyLevel gameLevel;

    CollisionController collisionController;
    std::vector<std::string> map;
    EnemyManager* enemyManager;
    PlayerManager* playerManager = new PlayerManager();
    ItemManager* itemManager = new ItemManager();
    Pages* pages;


    void closeGame();
    void doEvent(Event event);
    void getInput();
    void update();
    void draw();
    void readMap(std::string address);
    Point getElementPosition(int i, int j);
    void addMapElement(char input, Point position);
    void addMapElements(std::string address);
    void makeWindow(std::string mapAddress);
    void drawBackGround();
    void setGameLevel(std::string gameLevel);
    void doCollisions();
    void playersCollision();
    void showGameResult();
    bool isGameEnded();
    void identifyWinner();
public:
    void run();
    Game(std::string mapAddress, std::string gameLevel);
};

#endif