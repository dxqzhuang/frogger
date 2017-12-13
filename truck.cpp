#include "truck.h"

Truck::Truck() = default;

//constructor for customized truck
Truck::Truck(float posX, int lane){
    //setting truck sizeY to 40 and positionY
    //at increments of 5 to maintain gap between lanes
    truck.setFillColor(sf::Color::Red);
    truck.setPosition(sf::Vector2f(posX, LANE[lane]+5));

    //sets position for resetting truck
    originalPosX = posX;
    originalPosY = LANE[lane]+5;

    setLane(lane);
    //size, speed and direction of vehicle determine by lane
    switch(lane){
        case 7:
            truck.setSize(sf::Vector2f(80, 40));
            setSpeed(1.2);
            setDir(-1);
            break;
        case 8:
            truck.setSize(sf::Vector2f(40, 40));
            setSpeed(1.0);
            setDir(1);
            break;
        case 9:
            truck.setSize(sf::Vector2f(60, 40));
            setSpeed(0.8);
            setDir(-1);
            break;
        case 10:
            truck.setSize(sf::Vector2f(40, 40));
            setSpeed(1.5);
            setDir(1);
            break;
        case 11:
            truck.setSize(sf::Vector2f(40, 40));
            setSpeed(1.2);
            setDir(-1);
            break;
        default:
            break;
    }
}


//referenced call to main window to draw frog
void Truck::Draw(sf::RenderWindow &window) {
    window.draw(truck);
}


void Truck::Move(){
    //moving the car based on its speed and direction
    //wrapping when applicable
    truck.move(_speed*_dir, 0.0);
    if(getDir()==1){
        if(truck.getPosition().x>SCREEN_WIDTH){
            truck.setPosition(sf::Vector2f(-truck.getSize().x, originalPosY));
        }
    }
    else if(getDir()==-1){
        if((truck.getPosition().x+truck.getSize().x)<0){
            truck.setPosition(sf::Vector2f(SCREEN_WIDTH, originalPosY));
        }
    }
}

//function returning rectangle shape
sf::RectangleShape Truck::GetShape() {
    return truck;
}
float Truck::getSpeed(){
    return _speed;
}
int Truck::getDir(){
    return _dir;
}
int Truck::getLane(){
    return _lane;
}
void Truck::setSpeed(float s){
    _speed=s;
}
void Truck::setDir(int d){
    _dir=d;
}
void Truck::setLane(int l){
    _lane=l;
}
