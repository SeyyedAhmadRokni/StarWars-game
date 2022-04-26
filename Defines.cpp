
#ifndef _BITS_STARWARS_H
#define _BITS_STARWARS_H
#include <string>
#include "StarWars.hpp"

enum GameKey{
    UP,
    DOWN,
    RIGHT,
    LEFT,
    SHOOT,
};

enum EnemyType{
    FIXED,
    MOVING,
};

const std::string GAME_TITLE = "Star Wars";
const std::string GAME_PATH = "/home/seyyedahmad/Documents/Term2/Taklif5/Last";
const std::string ENEMY_IMAGES_PATH = "/img/enemy";
const std::string PLAYER_IMAGES_PATH = "/img/ship";
const int FIRE_WIDHT = 2;
const int FIRE_HEIGHT = 2;
const int ITEM_WIDTH = 3;
const int ITEM_HEIGHT = 3;
const int BONUS_SPEED_RATIO = 2;


#endif