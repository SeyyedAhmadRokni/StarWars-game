#ifndef _O_
#define _O_
#include <bits/stdc++.h>
#include "StarWars.hpp"
#include "Defines.cpp"

bool ItemManager::isChanceWithMakingItem(){
    const int YES_CHANCE = 100;
    const int NO_CHANCE = 0;
    int totalChances = YES_CHANCE + NO_CHANCE;
    int identifier = random()%totalChances;
    if (identifier<YES_CHANCE){
        return true;   
    }
    else{
        return false;
    }
}

ItemType ItemManager::whichItemToMake(){
    const int SPEED_CHANCE = 50;
    const int GAURD_CHANCE = 50;
    int totalChances = SPEED_CHANCE + GAURD_CHANCE;
    int identifier = random()%totalChances;
    if(identifier< SPEED_CHANCE){
        return SPEED;
    }
    else{
        return GAURD;
    }
}

void ItemManager::addGaurdItem(Point position){
    SpeedItem* item = new SpeedItem(position);
    items.push_back(item);
}

void ItemManager::addSpeedItem(Point position){
    GaurdItem* item = new GaurdItem(position);
    items.push_back(item);
}

void ItemManager::addItemIfPossible(Point position){
    if (isChanceWithMakingItem()){
        ItemType itemToMake = whichItemToMake();
        switch (itemToMake)
        {
        case SPEED:
            addSpeedItem(position);
            break;

        case GAURD:
            addGaurdItem(position);
            break;
        }
    }
}

void ItemManager::addItemIfPossible(vector<Point> positions){
    for (int i = 0; i < positions.size(); i++)
    {
        addItemIfPossible(positions[i]);
    }
}

void ItemManager::deleteExpiredItems(){
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->hasExpired()){
            delete items[i];
            items.erase(items.begin() + i);
        }
    }
}

void ItemManager::draw(Window* window){
    for (int i = 0; i < items.size(); i++)
    {
        items[i]->draw(window);
    }
    
}

vector<Item*>& ItemManager::getItems(){
    return items;
}

void ItemManager::erase(){
    for (int i = 0; i < items.size(); i++)
    {
        delete items[i];
    }
}

void CollisionController::ArrowAndPlayer(vector<Arrow*>& arrows,
    vector<Player*>& players, Window* window){
    for (int i = 0; i < players.size(); i++)
    {
        for (int j = 0; j < arrows.size(); j++)
        {
            if (players[i]->hasCollision(arrows[j])&&
                !players[i]->hasGaurd()){
                delete players[i];
                players.erase(players.begin() + i);

                delete arrows[j];
                arrows.erase(arrows.begin() + j);
                window->play_sound_effect(GAME_PATH + SOUNDS_PATH+
                    "/player_collision_sound.wav");
                break;
            }
        }
    }
}

void CollisionController::ArrowAndEnemy(vector<Arrow*>& arrows, vector<Enemy*>& enemies){
    for (int i = 0; i < enemies.size(); i++)
    {
        for (int j = 0; j < arrows.size(); j++)
        {
            if (enemies[i]->hasCollision(arrows[j])){
                delete enemies[i];
                enemies.erase(enemies.begin() + i);

                delete arrows[j];
                arrows.erase(arrows.begin() + j);
                break;
            }
        }
    }
}

void CollisionController::PlayerAndEnemy(vector<Player*>& players,
    vector<Enemy*>& enemies, Window* window){
    for (int i = 0; i < enemies.size(); i++)
    {
        for (int j = 0; j < players.size(); j++)
        {
            if (enemies[i]->hasCollision(players[j])
                && !players[j]->hasGaurd()){
                delete enemies[i];
                enemies.erase(enemies.begin() + i);

                delete players[j];
                players.erase(players.begin() + j);
                window->play_sound_effect(GAME_PATH + SOUNDS_PATH + 
                    "/player_collision_sound.wav");
                break;
            }
        }
    }
}

void CollisionController::PlayerAndItem(vector<Player*>& players,
    vector<Item*>& items, Window* window){
    for (int i = 0; i < players.size(); i++)
    {
        for (int j = 0; j < items.size(); j++)
        {
            if (players[i]->hasCollision(items[j])){
                items[j]->action(players[i]);

                delete items[j];
                items.erase(items.begin() + j);
                window->play_sound_effect(GAME_PATH + SOUNDS_PATH +
                    "/get_item_sound.wav");
                
                break;
            }
        }
    }
}

vector<Point> CollisionController::getAddItemsPosition(
    const vector<Arrow*>& arrows, const vector<Enemy*> enemies){
    vector<Point> positions;
    for (int i = 0; i < enemies.size(); i++)
    {
        for (int j = 0; j < arrows.size(); j++)
        {
            if (enemies[i]->hasCollision(arrows[j])){
                positions.push_back(enemies[i]->getPosition());
                break;
            }
        }
    }
    return positions;
}

void CollisionController::controlAllCollisions(vector<Player*>& players,
    vector<Enemy*>& enemies, vector<Arrow*>& playersArrows,
    vector<Arrow*>& enemiesArrows, vector<Item*>& items,
    Window* window){
    
    ArrowAndPlayer(enemiesArrows, players, window);
    ArrowAndEnemy(playersArrows, enemies);
    PlayerAndEnemy(players, enemies, window);
    PlayerAndItem(players, items, window);
}

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
    numberOfColumns;
    this->level = level;
    time(&lastShot);
}

bool EnemyShootTimer::isTimeToShot(){
    if (time(NULL) - lastShot > TWO_SHOT_DIFFERENCE){
        return true;
    }
    return false;
}

vector<int> EnemyShootTimer::getSafeColumns(){
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

#endif