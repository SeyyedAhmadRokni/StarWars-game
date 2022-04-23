#include <bits/stdc++.h>
#include <StarWars.hpp>

const std::string GAME_TITLE = "Star Wars";
const std::string GAME_PATH = "/home/seyyedahmad/Documents/Term2/Taklif5/Last";
const std::string ENEMY_IMAGES_PATH = "/img/enemy";
const std::string PLAYER_IMAGES_PATH = "/img/ship";
const int FIRE_WIDHT = 2;
const int FIRE_HEIGHT = 2;
const int ITEM_WIDTH = 3;
const int ITEM_HEIGHT = 3;
const int BONUS_SPEED_RATIO = 2;

class Controller{
private:
    std::map<char, GameKey> keys;
public:
    Controller(char up, char down, char left, char right, char shoot);
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
        std::string imgSource, int rate = 10);
    Box(Point p, int width, int height, 
        std::string imgSource, int rate = 10);

    void setLoc(Point p);
    void moveDown();
    void moveUp();
    void moveRight();
    void moveLeft();

    Point matchCenterUp(int otherWidth, int otherHeight);
    Point matchCenterDown(int otherWidth, int otherHeight);
    virtual void draw(Window* window)=0;
};

class Arrow:public Box{
private:
    int damage;
    std::string imageAddress = GAME_PATH +
        PLAYER_IMAGES_PATH + "fire.png";
public:
    Arrow(int x, int y, int damage = 100, int rate = 6):
        Box(x, y, FIRE_WIDHT, FIRE_HEIGHT, 
            imageAddress, rate);
    Arrow(Point p, int damage = 100, int rate = 6):
        Box(p, FIRE_WIDHT, FIRE_HEIGHT, 
            imageAddress, rate);
    void draw(Window* window);
};

class Item:public Box{
private:
    time_t creationTime;
    int existsDuration;
public:
    Item(int x, int y, int sec, std::string imgAddress): Box(x, y, ITEM_WIDTH,
        ITEM_HEIGHT, imgAddress, 0);
    bool isDeleteTime();
    void draw(Window* window);
    virtual void action(Player* player) = 0;
};

class SpeedItem:public Item{
private:
    int speedRatio = 2;
    int duration = 5;
public:
    void action(Player* player);
};

class PowrItem:public Item{
private:
    int duration = 5;
public:
    void action(Player* player);
};


class Enemy:public Box{
private:
    int health;
    std::vector<Arrow*> arrows;
public:
    Enemy(int x, int y, int width, int height, std::string imgAddress, int rate )
        : Box(x, y, width, height, imgAddress, rate);
    void shoot();
    void moveArrows();
    void drawArrows(Window* window);
    virtual void move(int windowWidth) = 0;
};