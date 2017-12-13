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

    //functions to move frog
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    //function to move frog on logs
    void Move(float logSpeed, int dir);

    //function returning rectangle shape
    sf::RectangleShape GetShape();

    //resets the frog after you get to safezone
    void Reset();

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
