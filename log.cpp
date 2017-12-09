#include "log.h"

//defining trivial default constructor
Log::Log() = default;

//constructor for customized truck
Log::Log(float posX, int lane){
    //setting Log sizeY to 40 and positionY
    //at increments of 5 to maintain gap between lanes
    log.setFillColor(sf::Color::Yellow);
    log.setPosition(sf::Vector2f(posX, LANE[lane]+5));

    //sets position for resetting Log
    originalPosX = posX;
    originalPosY = LANE[lane]+5;

    setLane(lane);
    //size, speed and direction of vehicle determine by lane
    switch(lane){
        case 1:
            log.setSize(sf::Vector2f(120, 40));
            setSpeed(1.5);
            setDir(-1);
            break;
        case 2:
            log.setSize(sf::Vector2f(100, 40));
            setSpeed(1.0);
            setDir(1);
            break;
        case 3:
            log.setSize(sf::Vector2f(80, 40));
            setSpeed(0.8);
            setDir(-1);
            break;
        case 4:
            log.setSize(sf::Vector2f(100, 40));
            setSpeed(1.5);
            setDir(1);
            break;
        case 5:
            log.setSize(sf::Vector2f(80, 40));
            setSpeed(1.0);
            setDir(-1);
            break;
        default:
            break;
    }
}


//referenced call to main window to draw frog
void Log::Draw(sf::RenderWindow &window) {
    window.draw(log);
}


void Log::Move() {
    log.move(_speed*_dir, 0.0);
    if(getDir()==1){
        if(log.getPosition().x>SCREEN_WIDTH){
            log.setPosition(sf::Vector2f(-log.getSize().x, originalPosY));
        }
    }
    else if(getDir()==-1){
        if((log.getPosition().x+log.getSize().x)<0){
            log.setPosition(sf::Vector2f(SCREEN_WIDTH, originalPosY));
        }
    }
}

//function returning rectangle shape
sf::RectangleShape Log::GetShape() {
    return log;
}
float Log::getSpeed(){
    return _speed;
}
int Log::getDir(){
    return _dir;
}
int Log::getLane(){
    return _lane;
}
void Log::setSpeed(float s){
    _speed=s;
}
void Log::setDir(int d){
    _dir=d;
}
void Log::setLane(int l){
    _lane=l;
}
