#ifndef TRUCK_H
#define TRUCK_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "constants.h"

class Truck
{
public:
    //default constructor
    Truck();
    //constructor with argument for position

    Truck(float posX, int lane);

    //referenced call to main window to draw frog
    void Draw(sf::RenderWindow &window);

    //function moving
    //dir of -1 reverses the direction
    void Move();

    //function returning rectangle shape
    sf::RectangleShape GetShape();

    float getSpeed();
    int getDir();
    int getLane();
    void setSpeed(float s);
    void setDir(int d);
    void setLane(int l);

private:
    //the object that will be returned by GetShape() function
    sf::RectangleShape truck;

    //used to reset position of truck when it goes off screen
    float originalPosX;
    float originalPosY;
    float _speed;
    int _dir;
    //odd lanes are left to right, even lanes are right to left
    int _lane;
};


#endif // TRUCK_H
