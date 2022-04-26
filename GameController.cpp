#ifndef _G_
#define _G_

#include <bits/stdc++.h>
#include "StarWars.hpp"

using namespace std;

Controller PlayerManger::getDefaultsControllers(int playerN){
    switch (playerN)
    {
    case 1:
        return Controller ('w', 's', 'a', 'd', ' ');
        break;
    case 2:
        return Controller ('i', 'k', 'j', 'l', 'o');
    }
}
void PlayerManger::addPlayer(Point p){
    Controller control = getDefaultsControllers(players.size()+1);
    Player *player = new Player(control, p);
    players.push_back(player);
}

void PlayerManger::PlayerManger::eraseExitedArrows(int windowWidth, int windowHeight){
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->earseExitedArrow(windowWidth,
            windowHeight);
    }
}
void PlayerManger::erase(){
    for (int i = 0; i < players.siz(); i++)
    {
        players[i]->earseAllArrows();
    }
    delete[] players;
}

void PlayerManger::doCommand(char key){
    for (int i = 0; i < players.size(); i++)
    {
            if (players[i]->hasKey(key)){
                players[i]->doCommand(key);
                break;
            }  
    }
}
void PlayerManger::movePlayerElements(){
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->moveArrows();

    }   
}
void PlayerManger::draw(Window* window){
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->draw(window);
    }
}

class Game{
private:
    Window* window;
    // EnemyManager* enemyManager = new EnemyManager();
    PlayerManger* playerManager = new PlayerManger();
    bool gameIsRunning = true;
public:
    Game(int windowWidth, int windowHeight){
        window = new Window(windowWidth,
         windowHeight, GAME_TITLE);
    }
    
    void closeGame(){
        // enemyManager->earase();
        playerManager->earase();
        delete window;
        exit(0);
    }
    
    void doEvent(Event event){
        switch(event.get_type()){
            case Event::QUIT:
                closeGame();
                break;
            case Event::KEY_PRESS:
                playerManager->doCommand(event.get_pressed_key());
                break;
        }
    }

    void getInput(){
        if (window->has_pending_event()){
            Event event = window->poll_for_event();
            doEvent(event);
        }
    }

    void moveElements(){
        playerManager->movePlayerElements();
        enemyManager->moveEnemiesElements(window);
    }
    void update(){
        getInput();
        moveElements();
    }
    void draw(){
        enemyManager->draw(window);
        playerManager->draw(window);
    }
    void run(){
        while(gameIsRunning){
            update();
            draw();
            delay(15);
        }
        closeGame();
    }
    std::vector<std::string> readFile(string address){
        std::ifstream file (address);
        vector<string> readed;
        string buf;
        while(getline(cin, buf)){
            readed.push_back();
        }
        return readed;
    }

    Point getElementPosition(int i, int j){
        return Point(i*STANDARD_BLOCK_WIDTH+   
            (i+1)*STANDARD_SEPRATOR_WIDTH,
            i*STANDARD_BLOCK_HEIGHT + 
            (i+1)*STANDARD_SEPRATOR_HEIGHT);
    }

    void addMapElement(char input, Point position){
        switch (input)
        {
        case 'E':
            
            break;
        case 'M':

            break;
        case 'S':

            break;
        case 'P':
            playerManager->addPlayer(position);
            break;
        default:
            break;
        }
    }

    void readMap(std::string address){
        vector<string> gameMap = readFile(address);
        for (int i = 0; i < gameMap.size(); i++)
        {
            for (int j = 0; j < gameMap[i].size(); j++)
            {
                Point position = getElementPosition(i, j)
                addMapElement(gameMap[i][j], position);
            }
        }
    }
};
#endif