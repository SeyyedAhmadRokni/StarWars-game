#include <bits/stdc++.h>
#include <StarWars.hpp>

const int FIRE_WIDHT = 2;
const int FIRE_HEIGHT = 2;


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
