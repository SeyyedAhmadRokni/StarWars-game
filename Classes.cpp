#include <bits/stdc++.h>
#include <StarWars.hpp>

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
