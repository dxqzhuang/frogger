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
    void Draw();
    void run();
    void processEvents();
    void update();
    void render();
    bool ifCollide(sf::RectangleShape obstacle);
    void checkCollide();
    void initTruck();
    void initLog();
    void initWalls();
    void initSafe();
    void winCheck(int winCounter[]);

    //    void renderWindow(sf::RenderWindow &window);
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
