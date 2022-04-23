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