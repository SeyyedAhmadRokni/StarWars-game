#ifndef _MAIN_
#define _MAIN_
#include <bits/stdc++.h>
#include "StarWars.hpp"
#include "GameController.cpp"
#include "rsdl.hpp"

using namespace std;

int main(){
    string mapAddress = "map.txt";
    Game game(mapAddress);
    // game.run();
    return 0;
}

#endif