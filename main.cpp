#ifndef _MAIN_
#define _MAIN_
#include <bits/stdc++.h>
#include "StarWars.hpp"

using namespace std;

int main(int argc, char *argv[])
{

    string mapAddress = string(argv[1]);
    string gameLevel = (argc==2) ?"M" :string(argv[2]);
    cout << gameLevel << endl;
    Game game(mapAddress, gameLevel);
    game.run();
    return 0;
}
#endif