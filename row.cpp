#include "row.h"

//Row::obstacle(){
Row::Row(){
    _log=false;
    _x=0;
    _y=0;
    _speed=1;
    _dir=true;
    _gap=100;
    sf::RectangleShape obst;
    obst.setFillColor(sf::Color::Red);
    obst.setSize(sf::Vector2f(75,75));
    obst.setPosition(0,LANE[1]);
}

//Row::obstacle(bool log, int x, int y, int speed, bool dir, int gap){
Row::Row(bool log, int x, int y, int speed, bool dir, int gap){
    _log=log;
    _x=x;
    _y=y;
    _speed=speed;
    _dir=dir;
    _gap=gap;
}

int Row::getSpeed(){
    return _speed;
}

bool Row::getDir(){
    return _dir;
}

int Row::getGap(){
    return _gap;
}

void Row::initRow(int lane){

}

//void Row::initRow(int lane){
//    for(int i=0; i<=4; i++){
//        cout<<"1";
//        sf::RectangleShape newObstacle;
//        cout<<"2";
//        obstacleV.push_back(newObstacle);
//        obstacleV[i].setFillColor(sf::Color::Red);
//        obstacleV[i].setSize(sf::Vector2f(75,75));
//        obstacleV[i].setPosition(i*100,LANE[lane]);
//    }
//}
