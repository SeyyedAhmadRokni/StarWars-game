#include <bits/stdc++.h>
#include <StarWars.hpp>
#include "Classes.cpp"

Controller::Controller(char up, char down, char left, char right, char shoot){
    keys.insert(std::pair<char, GameKey>(up, UP));
    keys.insert(std::pair<char, GameKey>(down, DOWN));
    keys.insert(std::pair<char, GameKey>(right, RIGHT));
    keys.insert(std::pair<char, GameKey>(left, LEFT));
    keys.insert(std::pair<char, GameKey>(shoot, SHOOT));
}

bool Controller::isAController(char input){
    return keys.count(input);
}
GameKey Controller::getCommand(char input){
    return keys.at(input);
};