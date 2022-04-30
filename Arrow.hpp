#ifndef _ARROW_
#define _ARROW_

#include <bits/stdc++.h>
#include "Defines.hpp"
#include "rsdl.hpp"


class Arrow:public Box{
private:
    int damage;
public:
    Arrow(Point p, std::string imageAddress, int damage = ARROW_DAMAGE);
    bool isInScreen(int windowWidth,
        int windowHeight);
};

#endif