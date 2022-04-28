#ifndef _m_
#define _m_
#include <bits/stdc++.h>
#include "/home/seyyedahmad/Documents/Term2/Taklif5/RSDL/src/rsdl.hpp"
#include "Defines.cpp"

using namespace std;

enum GameKey{
    UP,
    DOWN,
    RIGHT,
    LEFT,
    SHOOT,
};

enum EnemyType{
    FIXED,
    MOVING,
};

enum DifficultyLevel{
    EASY,
    MEDIUM, 
    HARD,
};

enum WinnerType{
    ENEMIES,
    PLAYERS,
};

enum ItemType{
    SPEED,
    GAURD,
};

class Controller{
private:
    std::map<char, GameKey> keys;
public:
    Controller(char up, char down, char left,
        char right, char shoot);
    bool isAController(char input);
    GameKey getCommand(char input);
};

class Box{
protected:
    int x, y;
    int width, height;
    std::string imageSource;
    int moveRate;
public:
    Box(int x, int y, int width, int height, 
        std::string imgSource="", int rate=0);
    Box(Point p, int width, int height, 
        std::string imgSource="", int rate=0);

    void moveDown();
    void moveUp();
    void moveRight();
    void moveLeft();
    Point getPosition();
    Point matchCenterUp(int otherWidth, int otherHeight);
    Point matchCenterDown(int otherWidth, int otherHeight);
    int centerDistanceX(Box* other);
    int centerDistanceY(Box* other);
    bool hasCollision(Box* other);
    // Point PositionToMatchCenters(Box* other);
    virtual void draw(Window* window);
   
};

class Arrow:public Box{
private:
    int damage;
public:
    Arrow(int x, int y, std::string imageAddress, int damage = FIRE_DAMAGE);
    Arrow(Point p, std::string imageAddress, int damage = FIRE_DAMAGE);
    bool isInScreen(int windowWidth,
        int windowHeight);
};


class Enemy:public Box{
private:
    int health;
public:
    Enemy(int x, int y, int width, int height,
        std::string imgAddress, int rate );
    Arrow* shoot();
    virtual void move(int windowWidth) = 0;
};

class MovingEnemy:public Enemy{
private:
    GameKey moveDiretion = RIGHT;
public:
    MovingEnemy(int x, int y, int rate = MOVING_ENEMY_MOVE_RATE);
    bool moveIsPossible(int windowWidth);
    void moveToDirection();
    void changeDirection();
    void move(const int windowWidth);
};

class FixedEnemy:public Enemy{
private:
public:
    FixedEnemy(int x, int y);
    void move(int windowWidth);
};


class Player:public Box{
private:
    Controller* controls;
    int health;
    
    bool hasGaurdItem = false;
    int gaurdDuration;
    time_t getGaurdTime;

    bool hasBonusSpeed = false;
    int speedDuration;
    time_t getSpeedTime;


    void lossGaurd();
    void lossBonusSpeed();
public:
    Player(Controller cont, Point p);
    Player(char up, char down, char left,
        char right, char shoot);
    bool hasKey(char released);
    Arrow* shoot();
    void getGaurd(int duration);
    void getSpeed(int duration, int ratio);
    bool moveIsPossible(GameKey direction, int windowWidth, int windowHeight);
    void doCommand(char input, int windowWidth, int windowHeight,
        std::vector<Arrow*>& arrows);
    void draw(Window* winodws);
};

class Item:public Box{
protected:
    time_t creationTime;
    int existsDuration;
public:
    Item(int x, int y, int sec, std::string imgAddress);
    bool isDeleteTime();
    bool hasExpired();
    virtual void action(Player* player) = 0;
};

class SpeedItem:public Item{
private:
    int duration = 5;
    int speedRatio = 2;
public:
    SpeedItem(Point position);
    void action(Player* player);
};

class GaurdItem:public Item{
private:
    int duration = 5;
public:
    GaurdItem(Point position);
    void action(Player* player);
};

class PlayerManager{
private:
    std::vector<Player*> players;
    std::vector<Arrow*> arrows;
public:
    Controller getDefaultsControllers(int playerN);
    void addPlayer(Point p);
    void doCommand(char key, int windowWidth,
        int windowHeight);
    std::vector<Arrow*>&  getArrows();
    void moveArrows();
    void moveElements();
    void drawPlayers(Window* window);
    void drawArrows(Window* window);
    void draw(Window* window);
    void eraseExitedArrow(int windowWidth,
        int windowHeight);
    void eraseAllPlayers();
    void eraseAllArrows();
    void erase();
    void deleteShotedPlayers(std::vector<Arrow*>& enemiesArrow);
    bool allPlayersAreDead();
};

class EnemyShootTimer{
private:
    time_t lastShot;
    int numberOfColumns;
    DifficultyLevel level;
    std::set<int> chooseColumns(int number);
    std::set<int> chooseColumnsEasy();
    std::set<int> chooseColumnsMedium();
    std::set<int> chooseColumnsHard();

public:
    EnemyShootTimer(int col, DifficultyLevel level);
    bool isTimeToShot();
    std::vector<int> getColumnsToShoot();
};


class EnemyManager{
private:
    EnemyShootTimer* enemyShootTimer;
    std::vector<Enemy*> enemies;
    std::vector<Arrow*> arrows;
    void moveArrows();
    void moveEnemies(int windowWidth);
    void drawEnemies(Window* window);
    void drawArrows(Window* window);
    void eraseAllArrows();
    void eraseAllEnemies();
public:
    EnemyManager(int gameColumnsNumber, DifficultyLevel gameLevel);
    std::vector<Arrow*>& getArrows();
    void addMovingEnemy(Point p);
    void addFixedEnemy(Point p);
    void erase();
    void moveElements(int windowWidth);
    void eraseExitedArrows(int windowWidth,
        int windowHeight);
    void draw(Window* window);
    void enemiesShoot();
    std::vector<Point> getMustDeleteEnemiesPositions(
        vector<Arrow*>& playerArrows
    );
    bool isInColumn(Enemy* enemy, int column);
    void deleteShotedEnemies(std::vector<Arrow*>& playerArrows);
    bool allEnemiesAreDead();
};

class Button:Box{
private:
    string title;
public:
    Button(string title, Point position);
    bool isInClicked(Point mousPosition);
    void draw(Window* window);
};

class Pages{
private:
    Window* window;
    std::vector<Button*> buttons;
public:
    Pages(Window* window);
    Point getCenterOfPageToShow();
    void showResult(WinnerType winner);
    void showResultPage(WinnerType winner);
};

class ItemManager{
private:
    std::vector<Item*> items;
public:
    void addGaurdItem(Point position);
    void addSpeedItem(Point position);
    bool isChanceWithMakingItem();
    ItemType whichItemToMake();
    void addItemIfPossible(Point position);
    void addItemIfPossible(vector<Point> positions);
    void deleteExpiredItems();
    void draw(Window* window);
};

class Game{
private:
    Window* window;
    WinnerType winner;
    int columnsNumber;
    bool gameIsRunning = true;
    DifficultyLevel gameLevel;

    std::vector<std::string> map;
    EnemyManager* enemyManager;
    PlayerManager* playerManager = new PlayerManager();
    ItemManager* itemManager = new ItemManager();
    Pages* pages;

public:
    void closeGame();
    void doEvent(Event event);
    void getInput();
    void moveElements();
    void update();
    void draw();
    void run();
    void readMap(std::string address);
    Point getElementPosition(int i, int j);
    void addMapElement(char input, Point position);
    void addMapsElements(std::string address);
    void makeWindow(std::string mapAddress);
    void drawBackGround();
    void setGameLevel(std::string gameLevel);
    void doCollisions();
    void playersCollision();
    void showGameResult();
    bool gameIsEnded();
    void identifyWinner();
    Game(std::string mapAddress, std::string gameLevel);
};
#endif