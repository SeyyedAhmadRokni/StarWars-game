#ifndef _MAIN_
#define _MAIN_
#include <bits/stdc++.h>
#include "StarWars.hpp"
#include "GameController.cpp"
#include "rsdl.hpp"

using namespace std;

int main(){
    string mapAddress = "map.txt";
    string gameLevel = "M";
    Game game(mapAddress, gameLevel);
    game.run();
    return 0;
}
//TODO: -taghire name khoroji be starwars.out
//      -voroodi dadane map be soorate argv
#endif