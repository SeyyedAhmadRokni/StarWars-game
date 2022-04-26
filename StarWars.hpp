#include <bits/stdc++.h>
#include "/home/seyyedahmad/Documents/Term2/Taklif5/RSDL/src/rsdl.hpp"

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
// class Controller{
// private:
//     std::map<char, GameKey> keys;
// public:
//     Controller(char up, char down, char left, char right, char shoot);
//     bool isAController(char input);
//     GameKey getCommand(char input);
// };


// class Box{
// protected:
//     int x, y;
//     int width, height;
//     std::string imageSource;
//     int moveRate;
// public:
//     Box(int x, int y, int width, int height, 
//         std::string imgSource, int rate = 10);
//     Box(Point p, int width, int height, 
//         std::string imgSource, int rate = 10);

//     void setLoc(Point p);
//     void moveDown();
//     void moveUp();
//     void moveRight();
//     void moveLeft();

//     Point matchCenterUp(int otherWidth, int otherHeight);
//     Point matchCenterDown(int otherWidth, int otherHeight);
//     virtual void draw(Window* window)=0;
// };

// class Arrow:public Box{
// private:
//     int damage;
//     std::string imageAddress = GAME_PATH +
//         PLAYER_IMAGES_PATH + "fire.png";
// public:
//     Arrow(int x, int y, int damage = 100, int rate = 6):
//         Box(x, y, FIRE_WIDHT, FIRE_HEIGHT, 
//             imageAddress, rate);
//     Arrow(Point p, int damage = 100, int rate = 6):
//         Box(p, FIRE_WIDHT, FIRE_HEIGHT, 
//             imageAddress, rate);
//     void draw(Window* window);
// };

// class Item:public Box{
// private:
//     time_t creationTime;
//     int existsDuration;
// public:
//     Item(int x, int y, int sec, std::string imgAddress): Box(x, y, ITEM_WIDTH,
//         ITEM_HEIGHT, imgAddress, 0);
//     bool isDeleteTime();
//     void draw(Window* window);
//     virtual void action(Player* player) = 0;
// };

// class SpeedItem:public Item{
// private:
//     int speedRatio = 2;
//     int duration = 5;
// public:
//     void action(Player* player);
// };

// class PowrItem:public Item{
// private:
//     int duration = 5;
// public:
//     void action(Player* player);
// };


// class Enemy:public Box{
// private:
//     int health;
//     std::vector<Arrow*> arrows;
// public:
//     Enemy(int x, int y, int width, int height, std::string imgAddress, int rate )
//         : Box(x, y, width, height, imgAddress, rate);
//     void shoot();
//     void moveArrows();
//     void drawArrows(Window* window);
//     virtual void move(int windowWidth) = 0;
// };

// class MovingEnemy:public Enemy{
// private:
//     GameKeys moveDiretion = RIGHT;
//     std::string imageAddress = GAME_PATH + ENEMY_IMAGES_PATH + "/moving.png";
// public:
//     MovingEnemy(int x, int y, int rate=10)
//         :Enemy(x, y, STANDARD_BLOCK_WIDTH
//         ,STANDARD_BLOCK_HEIGHT, imageAddress, rate) 
//     bool moveIsPossible(int windowWidth);
//     void moveToDirection();
//     void changeDirection();
//     void move(const int windowWidth);
//     void draw(Window* window);
// };

// class FixedEnemy:public Enemy{
// private:
//     std::string imageAddress = GAME_PATH +
//         ENEMY_IMAGES_PATH +"/fixed.png";
// public:
//     FixedEnemy(int x, int y, int rate=10)
//         :Enemy(x, y, STANDARD_BLOCK_WIDTH
//         ,STANDARD_BLOCK_HEIGHT, imageAddress, rate);
//     void draw(Window* window);
//     void move(int windowWidth);
// };


// class Player:public Box{
// private:
//     Controller* controls;
//     std::vector<Arrow*> arrows;
//     int health;
    
//     bool hasGaurdItem = false;
//     int gaurdDuration;
//     time_t getGaurdTime;

//     bool hasBonusSpeed = false;
//     int speedRatio = 1;
//     int speedDuration;
//     time_t getSpeedTime;

//     void lossGaurd();
//     void lossBonusSpeed();
//     std::string imageAddress = GAME_PATH +
//         PLAYER_IMAGES_PATH + "/1.png";
// public:
//     Player(Controller cont, int x, int y)
//         :Box(x, y, STANDARD_BLOCK_WIDTH, STANDARD_BLOCK_HEIGHT,
//         imageAddress, PLAYER_MOVE_RATE);

//     Player(char up, char down, char left, char right, char shoot)
//         :Box(x, y, STANDARD_BLOCK_WIDTH, STANDARD_BLOCK_HEIGHT,
//         imageAddress, PLAYER_MOVE_RATE);
//     bool hasKey(char released);
//     void shoot();
//     void getGaurd(int duration);
//     void getSpeed(int duration, int ratio);
//     void moveArrows();
//     void drawArrows(Window* window);
//     bool moveIsPossible(GameKeys direction, int windowWidth, int windowHeight);
//     void doCommand(char input, int windowWidth, int windowHeight);
// };
