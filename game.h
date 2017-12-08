#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "constants.h"
#include "frog.h"
#include "truck.h"
#include "log.h"

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
    void initTruck();
    void initLog();
    void renderWindow(sf::RenderWindow &window);

private:
    sf::RenderWindow window;
    Frog frog;
    vector<Truck> truckV;
    vector<Log> logV;
};


#endif // GAME_H
