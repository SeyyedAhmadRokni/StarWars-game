#ifndef _DEFS_
#define _DEFS_

#include <string>

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
    HOSTAGE_SHIP,
};

enum DifficultyLevel{
    EASY,
    MEDIUM, 
    HARD,
};

enum WinnerType{
    ENEMIES,
    PLAYERS,
};

enum ItemType{
    SPEED,
    GAURD,
};

const std::string GAME_TITLE = "Star Wars";
const std::string GAME_PATH = "/home/seyyedahmad/Documents/Term2/Taklif5/Last";
const std::string ENEMY_IMAGES_PATH = "/img/enemy";
const std::string PLAYER_IMAGES_PATH = "/img/player";
const std::string BACKGROUND_IMAGES_PATH = "/img/background";
const std::string ITEMS_IMAGES_PATH = "/img/items";

const int PLAYER_MOVE_RATE = 3;

const int ARROW_DAMAGE = 100;
const int ARROW_WIDHT = 20;
const int ARROW_HEIGHT = 20;
const int ARROW_RATE = 10;

const int ITEM_WIDTH = 30;
const int ITEM_HEIGHT = 30;
const int BONUS_SPEED_RATIO = 2;

const int STANDARD_BLOCK_WIDTH = 80;
const int STANDARD_BLOCK_HEIGHT = 80;
const int STANDARD_MARGIN_WIDTH = 80;
const int STANDARD_MARGIN_HEIGHT = 100;

const int TWO_SHOT_DIFFERENCE = 3;

const int MOVING_ENEMY_MOVE_RATE = 5;

const int BUTTON_STANDARD_WIDTH = 60;
const int BUTTON_STANDARD_HEIGHT = 40;

const int SPEED_ITEM_EXISTENCE_TIME = 5;
const int GAURD_ITEM_EXISTENCE_TIME = 5;

const std::string SOUNDS_PATH = "/sounds"; 

const std::string FONTS_PATH = "/fonts";

#endif