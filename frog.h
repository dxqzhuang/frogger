#ifndef FROG_H
#define FROG_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "constants.h"


class Frog
{
public:
    //constructor with argument for position
    Frog();

    //referenced call to main window to draw frog
    void Draw(sf::RenderWindow &window);

    //function to move frog taking keyboard events as args
    void Move(sf::Event event);

    //function to move frog on logs
    void Move(float logSpeed, int dir);

    //function returning rectangle shape
    sf::RectangleShape GetShape();

    int getLane();
    bool getAlive();
    void setAlive(bool alive);
private:
    //the object that will be returned by GetShape() function
    sf::RectangleShape frog;
    int _lane;
    bool _alive;
};

#endif // FROG_H
