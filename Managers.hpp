#ifndef _PLAYER_MANAGER_
#define _PLAYER_MANAGER_

#include <bits/stdc++.h>
#include "Defines.hpp"
#include "BasicStructures.hpp"
#include "Items.hpp"
#include "Arrow.hpp"
#include "Player.hpp"
#include "rsdl.hpp"
#include "Enemies.hpp"

using namespace std;

class PlayerManager{
private:
    std::vector<Player*> players;
    std::vector<Arrow*> arrows;
    Controller getDefaultsControllers(int playerN);
    void moveArrows();
    void drawPlayers(Window* window);
    void drawArrows(Window* window);
    void eraseExitedArrow(int windowWidth,
        int windowHeight);
    void eraseAllPlayers();
    void eraseAllArrows();
    void disableExpiredItems();
    void movePlayers(int windowWidth, int windowHeight);
public:
    void manageKeyPress(char key, Window* window);
    void addPlayer(Point p);
    std::vector<Arrow*>&  getArrows();
    void update(int windowWidth, int windowHeight);
    void draw(Window* window);
    void erase();
    bool allPlayersAreDead();
    vector<Player*>& getPlayers();
    void manageKeyRelease(char released);

};

class EnemyShootTimer{
private:
    time_t lastShot;
    int numberOfColumns;
    DifficultyLevel level;
    std::set<int> chooseColumns(int number);
    std::set<int> chooseColumnsEasy();
    std::set<int> chooseColumnsMedium();
    std::set<int> chooseColumnsHard();

public:
    EnemyShootTimer(int col, DifficultyLevel level);
    bool isTimeToShot();
    std::vector<int> getSafeColumns();
};


class EnemyManager{
private:
    EnemyShootTimer* enemyShootTimer;
    int hostageShipsNumber = 0;
    std::vector<Enemy*> enemies;
    std::vector<Arrow*> arrows;
    void moveArrows();
    void moveEnemies(int windowWidth);
    void drawEnemies(Window* window);
    void drawArrows(Window* window);
    void eraseAllArrows();
    void eraseAllEnemies();
    void eraseExitedArrows(int windowWidth,
        int windowHeight);
    bool isInColumn(Enemy* enemy, int column);
public:
    EnemyManager(int gameColumnsNumber, DifficultyLevel gameLevel);
    std::vector<Arrow*>& getArrows();
    void addMovingEnemy(Point p);
    void addFixedEnemy(Point p);
    void addHostageShip(Point p);
    void erase();
    void draw(Window* window);
    void shoot();
    bool areAllEnemiesDead();
    vector<Enemy*>& getEnemies();
    void update(int windowWidth);
    bool hasAHostageShipDead();
};

class ItemManager{
private:
    std::vector<Item*> items;
    bool isChanceWithMakingItem();
    ItemType whichItemToMake();
public:
    void addGaurdItem(Point position);
    void addSpeedItem(Point position);
    void addItemIfPossible(Point position);
    void addItemIfPossible(vector<Point> positions);
    void deleteExpiredItems();
    void draw(Window* window);
    vector<Item*>& getItems();
    void erase();
};

class CollisionController{
private:

public:
    void ArrowAndPlayer(vector<Arrow*>& arrows,
        vector<Player*>& players, Window* window);
    void ArrowAndEnemy(vector<Arrow*>& arrows,
        vector<Enemy*>& enemies);
    void PlayerAndEnemy(vector<Player*>& players,
        vector<Enemy*>& enemies, Window* window);
    void PlayerAndItem(vector<Player*>& players,
        vector<Item*>& items, Window* window);
    void controlAllCollisions(vector<Player*>& players,
        vector<Enemy*>& enemies, vector<Arrow*>& playersArrows,
        vector<Arrow*>& enemiesArrows, vector<Item*>& items,
        Window* window);
    vector<Point> getAddItemsPosition(const vector<Arrow*>& arrows,
        const vector<Enemy*> enemies);
};

#endif