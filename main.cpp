#ifndef _MAIN_
#define _MAIN_
#include <bits/stdc++.h>
#include "StarWars.hpp"

using namespace std;

int main(int argc, char *argv[])
{

    string mapAddress = str(argv[0]);
    string gameLevel;
    if (argc == 1)
    {
        gameLevel = "M";
    }
    else
    {
        gameLevel = str(argv[1]);
    }
    Game game(mapAddress, gameLevel);
    game.run();
    return 0;
}
#endif