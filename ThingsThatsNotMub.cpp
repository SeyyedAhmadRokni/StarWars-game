#include <bits/stdc++.h>
#include <set>
#include "StarWars.hpp"
#include "Defines.cpp"

using namespace std;

Arrow::Arrow(int x, int y, string imageAddress, int damage):
    Box(x, y, FIRE_WIDHT, FIRE_HEIGHT, imageAddress, FIRE_RATE){
    this->damage = damage;
}

Arrow::Arrow(Point p, string imageAddress, int damage):
    Box(p, FIRE_WIDHT, FIRE_HEIGHT, imageAddress, FIRE_RATE){

    this->damage = damage;
}

bool Arrow::isInScreen(int windowWidth, int windowHeight){
    if (x<=windowWidth && x>=0 
        && y<= windowHeight && windowHeight>=0){
        return true;
    }
    return false;
}

//--------------------------------------------------

Item::Item(int x, int y, int sec, std::string imgAddress): Box(x, y, ITEM_WIDTH,
    ITEM_HEIGHT, imgAddress, 0){
    time(&creationTime);
    existsDuration = sec;
}
bool Item::isDeleteTime(){
    if (time(NULL)-creationTime > existsDuration){
        return true;
    }
    return false;
}

bool Item::hasExpired(){
    if (time(NULL) - creationTime > existsDuration){
        return true;
    }
    return false;
}

SpeedItem::SpeedItem(Point position):
    Item(position.x, position.y, SPEED_ITEM_EXISTS_TIME,
    GAME_PATH + THINGS_IMAGES_PATH + "/speed.png"){
}

void SpeedItem::action(Player* player){
    player->getSpeed(duration, speedRatio);
}

GaurdItem::GaurdItem(Point position):
    Item(position.x, position.y, GAURD_ITEM_EXISTS_TIME,
    GAME_PATH + THINGS_IMAGES_PATH + "/gaurd.png"){
}

void GaurdItem::action(Player* player){
    player->getGaurd(duration);
}



//----------------------------------


set<int> EnemyShootTimer::chooseColumns(int number){
    set<int> columns; 
    while(columns.size() < number){
        columns.insert((rand()%number+1));
    }
    return columns;
    
}

set<int> EnemyShootTimer::chooseColumnsEasy(){
    const int CHANCE_3_COLUMNS = 6;
    const int CHANCE_4_COLUMNS = 3;
    const int CHANCE_5_COLUMNS = 1;
    int totalChances = CHANCE_3_COLUMNS + 
    CHANCE_4_COLUMNS + CHANCE_5_COLUMNS;
    set<int> emptyColumns;
    int emptyColumnsDeterminative = random()%totalChances;
    if (emptyColumnsDeterminative < CHANCE_3_COLUMNS){
        emptyColumns = chooseColumns(3);
    }
    else if (emptyColumnsDeterminative < CHANCE_4_COLUMNS){
        emptyColumns = chooseColumns(4);
    }
    else if (emptyColumnsDeterminative < CHANCE_5_COLUMNS){
        emptyColumns = chooseColumns(5);
    }
    
    return emptyColumns;
}

set<int> EnemyShootTimer::chooseColumnsMedium(){
    const int CHANCE_2_COLUMNS = 6;
    const int CHANCE_3_COLUMNS = 3;
    const int CHANCE_4_COLUMNS = 1;
    int totalChances = CHANCE_2_COLUMNS + 
    CHANCE_3_COLUMNS + CHANCE_4_COLUMNS;
    set<int> emptyColumns;
    int emptyColumnsDeterminative = random()%totalChances;
    if (emptyColumnsDeterminative < CHANCE_2_COLUMNS){
        emptyColumns = chooseColumns(2);
    }
    else if (emptyColumnsDeterminative < CHANCE_3_COLUMNS){
        emptyColumns = chooseColumns(3);
    }
    else if (emptyColumnsDeterminative < CHANCE_4_COLUMNS){
        emptyColumns = chooseColumns(4);
    }
    
    return emptyColumns;
}

set<int> EnemyShootTimer::chooseColumnsHard(){
    const int CHANCE_1_COLUMNS = 6;
    const int CHANCE_2_COLUMNS = 3;
    const int CHANCE_3_COLUMNS = 1;
    int totalChances = CHANCE_1_COLUMNS + 
    CHANCE_2_COLUMNS + CHANCE_3_COLUMNS;
    set<int> emptyColumns;
    int emptyColumnsDeterminative = random()%totalChances;
    if (emptyColumnsDeterminative < CHANCE_1_COLUMNS){
        emptyColumns = chooseColumns(3);
    }
    else if (emptyColumnsDeterminative < CHANCE_2_COLUMNS){
        emptyColumns = chooseColumns(4);
    }
    else if (emptyColumnsDeterminative < CHANCE_3_COLUMNS){
        emptyColumns = chooseColumns(5);
    }
    return emptyColumns;
}

EnemyShootTimer::EnemyShootTimer(int col, DifficultyLevel level){
    srand(time(NULL));
    numberOfColumns;
    this->level = level;
    time(&lastShot);
    // lastShot -= 7;
}

bool EnemyShootTimer::isTimeToShot(){
    if (time(NULL) - lastShot > TWO_SHOT_DIFFERENCE){
        return true;
    }
    return false;
}

vector<int> EnemyShootTimer::getColumnsToShoot(){
    time(&lastShot);
    set<int> choosedColumns;
    switch (level)
    {
    case EASY:
        choosedColumns = chooseColumnsEasy();
        break;
    case MEDIUM:
        choosedColumns = chooseColumnsMedium();
        break;
    
    case HARD:
        choosedColumns = chooseColumnsHard();
        break;
    }
    return vector<int>(choosedColumns.begin(), choosedColumns.end());
}



Button::Button(string title, Point position):Box(position, 
    BUTTON_STANDARD_WIDTH, BUTTON_STANDARD_HEIGHT){
    this->title = title;
}

bool Button::isInClicked(Point mousPosition){
    if (mousPosition.x >x && mousPosition.y < x+width &&
        mousPosition.y >y && mousPosition.y < y+height){
        return true;
    }
    return false;
}

void Button::draw(Window* window){
    window->fill_rect(Rectangle(x, y, width, height), BLUE);
    window->show_text(title, Point(x, y), WHITE,
    GAME_PATH + FONTS_PATH + "/OpenSans.ttf");
}