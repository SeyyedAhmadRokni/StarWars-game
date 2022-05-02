#ifndef _BS_
#define _BS_

#include <bits/stdc++.h>
#include "Defines.hpp"
#include "rsdl.hpp"

using namespace std;

class Controller
{
private:
    std::map<char, GameKey> keys;

public:
    Controller(char up, char down, char left,
               char right, char shoot);
    bool isAController(char input);
    GameKey getCommand(char input);
};

class Box
{
protected:
    int x, y;
    int width, height;
    std::string imageSource;
    int moveRate;

public:
    Box(int x, int y, int width, int height,
        std::string imgSource = "", int rate = 0);
    Box(Point p, int width, int height,
        std::string imgSource = "", int rate = 0);

    void moveDown();
    void moveUp();
    void moveRight();
    void moveLeft();
    Point getPosition();
    Point matchUpCenter(int otherWidth, int otherHeight);
    Point matchDownCenter(int otherWidth, int otherHeight);
    int centerDistanceX(Box *other);
    int centerDistanceY(Box *other);
    bool hasCollision(Box *other);
    virtual void draw(Window *window);
};

class Pages
{
private:
    Window *window;

public:
    Pages(Window *window);
    Point getCenterOfPageToShow();
    void showResult(WinnerType winner);
    void showResultPage(WinnerType winner);
};

#endif