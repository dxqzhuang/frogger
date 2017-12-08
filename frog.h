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

    //function returning rectangle shape
    sf::RectangleShape GetShape();

    int getLane();
private:
    //the object that will be returned by GetShape() function
    sf::RectangleShape frog;
    int _lane;




//    older design that uses text-based approach
//public:
//    Frog();
//    Frog(float x, float y);
//    int fSizeX();
//    int fSizeY();
//    float fGetX();
//    float fGetY();
//    void fSetX(float x);
//    void fSetY(float y);
//    void fMoveUp();
//    void fMoveDown();
//    void fMoveLeft();
//    void fMoveRight();
//    void initFrog();
//    void renderFrog();
//private:
//    float _x;
//    float _y;
};

#endif // FROG_H
