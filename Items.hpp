#ifndef _ITEMS_
#define _ITEMS_

#include <bits/stdc++.h>
#include "Defines.hpp"
#include "Player.hpp"
#include "rsdl.hpp"


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

#endif