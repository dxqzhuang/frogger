#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "constants.h"

class Log
{
public:
    //default constructor
    Log();
    //constructor with argument for position

    Log(float posX, int lane);

    //referenced call to main window to draw log
    void Draw(sf::RenderWindow &window);

    //function that moves the log based on its properties
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
    sf::RectangleShape log;

    //used to reset position of truck when it goes off screen
    float originalPosX;
    float originalPosY;
    float _speed;
    int _dir;
    //odd lanes are left to right, even lanes are right to left
    int _lane;
};


#endif // LOG_H
