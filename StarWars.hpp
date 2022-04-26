#include <bits/stdc++.h>
#include "/home/seyyedahmad/Documents/Term2/Taklif5/RSDL/src/rsdl.hpp"
#include "Defines.cpp"

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
        std::string imgSource, int rate);
    Box(Point p, int width, int height, 
        std::string imgSource, int rate);

    void setLoc(Point p);
    void moveDown();
    void moveUp();
    void moveRight();
    void moveLeft();

    Point matchCenterUp(int otherWidth, int otherHeight);
    Point matchCenterDown(int otherWidth, int otherHeight);
    virtual void draw(Window* window);
};

class Arrow:public Box{
private:
    int damage;
    std::string imageAddress = GAME_PATH +
        PLAYER_IMAGES_PATH + "fire.png";
public:
    Arrow(int x, int y, int damage, int rate);
    Arrow(Point p, int damage, int rate);
    bool isInScreen(int windowWidth,
        int windowHeight);
};


class Enemy:public Box{
private:
    int health;
    std::vector<Arrow*> arrows;
public:
    Enemy(int x, int y, int width, int height,
        std::string imgAddress, int rate );
    void shoot();
    void moveArrows();
    void drawArrows(Window* window);
    void draw(Window* window);
    virtual void move(int windowWidth) = 0;
};

class MovingEnemy:public Enemy{
private:
    GameKey moveDiretion = RIGHT;
    std::string imageAddress = GAME_PATH + ENEMY_IMAGES_PATH + "/moving.png";
public:
    MovingEnemy(int x, int y, int rate);
    bool moveIsPossible(int windowWidth);
    void moveToDirection();
    void changeDirection();
    void move(const int windowWidth);
};

class FixedEnemy:public Enemy{
private:
    std::string imageAddress = GAME_PATH +
        ENEMY_IMAGES_PATH +"/fixed.png";
public:
    FixedEnemy(int x, int y, int rate);
    void move(int windowWidth);
};


class Player:public Box{
private:
    Controller* controls;
    std::vector<Arrow*> arrows;
    int health;
    
    bool hasGaurdItem = false;
    int gaurdDuration;
    time_t getGaurdTime;

    bool hasBonusSpeed = false;
    int speedRatio = 1;
    int speedDuration;
    time_t getSpeedTime;

    void lossGaurd();
    void lossBonusSpeed();
    std::string imageAddress = GAME_PATH +
        PLAYER_IMAGES_PATH + "/1.png";
public:
    Player(Controller cont, Point p);
    Player(char up, char down, char left,
        char right, char shoot);
    bool hasKey(char released);
    void shoot();
    void getGaurd(int duration);
    void getSpeed(int duration, int ratio);
    void moveArrows();
    void drawArrows(Window* window);
    bool moveIsPossible(GameKey direction, int windowWidth, int windowHeight);
    void doCommand(char input, int windowWidth, int windowHeight);
    void draw(Window* winodws);
    void earseExitedArrow(int windowWidth,
        int windowHeight);
    void earseAllArrows();
    void erase();

};

class Item:public Box{
private:
    time_t creationTime;
    int existsDuration;
public:
    Item(int x, int y, int sec, std::string imgAddress);
    bool isDeleteTime();
    virtual void action(Player* player) = 0;
};

class SpeedItem:public Item{
private:
    int speedRatio = 2;
    int duration = 5;
public:
    void action(Player* player);
};

class PowerItem:public Item{
private:
    int duration = 5;
public:
    void action(Player* player);
};


class PlayerManger{
private:
    std::vector<Player*> players;
public:
    Controller getDefaultsControllers(int playerN);
    void addPlayer(Point p);
    void eraseExitedArrows(int windowWidth, int windowHeight);
    void doCommand(char key);
    void movePlayerElements();
    void draw(Window* window);
    void erase();
};