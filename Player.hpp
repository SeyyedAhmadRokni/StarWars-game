#ifndef _PLAYER_
#define _PLAYER_

#include <bits/stdc++.h>
#include "Defines.hpp"
#include "BasicStructures.hpp"
#include "Arrow.hpp"
#include "rsdl.hpp"

class Player:public Box{
private:
    Controller* controls;
    int health;
    bool doLastCommand = false;
    
    bool hasGaurdItem = false;
    int gaurdDuration;
    time_t getGaurdTime;
    std::string gaurededImage;

    bool hasBonusSpeed = false;
    int speedDuration;
    time_t getSpeedTime;

    bool movingRight = false;
    bool movingLeft = false;
    bool movingUP = false;
    bool movingDown = false;

    void disableSpeedItem();
    void disableGaurdItem();

public:
    Player(Controller cont, Point p, int playerNumber);
    bool hasKey(char released);
    Arrow* shoot();
    void getGaurd(int duration);
    void getSpeed(int duration, int ratio);
    bool isMovePossible(GameKey direction, int windowWidth, int windowHeight);
    void manageKeyPress(char input, Window* window, std::vector<Arrow*>& arrows);
    void draw(Window* winodws);
    bool hasGaurd();
    void move(int windowWidth, int windowHeight);
    void disableExpiredItems();
    void manageKeyRelease(char input);
};

#endif