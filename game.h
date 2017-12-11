#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "constants.h"
#include "frog.h"
#include "truck.h"
#include "log.h"
#include <cstdlib>
#include <ctime>

using namespace std;

class Game{
public:
    Game();
    void Draw();                                        //draws the shapes of objects
    void run();                                         //runs the game
    void processEvents();                               //process input
    void update();                                      //update game based on input
    void render();                                      //refresh and redraw the objects
    bool ifCollide(sf::RectangleShape obstacle);        //geneirc collision algorithm
    void gameProgress();                                //calls ifCollide for appropriate obstacles
    void initTruck();                                   //creates a vector of trucks
    void initLog();                                     //creates a vector of logs
    void initWalls();                                   //creates a vector of walls
    void initSafe();                                    //creates a vector of safe zones
    void winCheck(int winCounter[]);
    float getRand(int hi, int lo);

private:
    sf::RenderWindow window;
    Frog frog;
    vector<Truck> truckV;
    vector<Log> logV;
    vector<sf::RectangleShape> wallV;
    vector<sf::RectangleShape> safezoneV;
    int winCounter[3] = {0,0,0};
};


#endif // GAME_H
