#ifndef ROW_H
#define ROW_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "constants.h"
using namespace std;

class Row
{
public:
    obstacle();
    obstacle(bool log, int x, int y, int speed, bool dir, int gap);

    int getSpeed();
    bool getDir();
    int getGap();
    void initRow(int lane);

private:
    bool _log;
    int _x;
    int _y;
    int _speed;
    bool _dir;
    int _gap;
};

#endif // ROW_H
