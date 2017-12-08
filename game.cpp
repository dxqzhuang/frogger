#include "game.h"
#include <stdlib.h>
#include <time.h>

Game::Game(){
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Frogger v.01");
    window.setFramerateLimit(60);
    srand(time(NULL));
    //create trucks
    initTruck();
    initLog();
}

void Game::Draw(){
    frog.Draw(window);

    for(int i=0; i<15; i++){
        truckV[i].Draw(window);
    }
    for(int i=0; i<15; i++){
        logV[i].Draw(window);
    }
}

void Game::update(){
    for(int i=0; i<15; i++){
        truckV[i].Move();
        if(ifCollide(truckV[i].GetShape())) cout<<"Colliding"<<endl;
    }
    for(int i=0; i<15; i++){
        logV[i].Move();
        if(ifCollide(logV[i].GetShape())) cout<<"Colliding"<<endl;
    }
}

void Game::render(){
    window.clear();
    Draw();
    window.display();
}

void Game::processEvents(){
    sf::Event event;
    while(window.pollEvent(event)){
        switch(event.type){
        case sf::Event::Closed:
            window.close();
            break;

        //key press check
        case sf::Event::KeyPressed:
            frog.Move(event);
            break;

        default:
            break;
        }
    }
}

bool Game::ifCollide(sf::RectangleShape obstacle){
    //collision boundary check from frog to any given obstacle
    bool collide=false;
    if(frog.GetShape().getGlobalBounds().intersects(obstacle.getGlobalBounds())){
        collide=true;
    }
    return collide;
}

//this is rectangle shape not truck need to fix
void Game::initTruck(){
    int numOfTrucks=0;
    //rng for gap distance
    float randHI=200, randLO=100;
    //creates vehicles from lane[7] to lane[11]
    for(int i=7; i<12; i++){
        //3 vehicles per lane for now
        for(int j=0; j<3; j++){
            //float# generation code from stackoverflow
            float r=randHI+static_cast <float>(rand())/(static_cast <float>(RAND_MAX/(randHI-randLO)));
            //creates a new truck in the vector, with position rand for X, lane[i] for Y,
            truckV.push_back(Truck(j*r, i));
            numOfTrucks++;
        }
    }
}

void Game::initLog(){
    int numOfLogs=0;
    //rng for gap distance
    float randHI=200, randLO=100;
    //creates vehicles from lane[1] to lane[6]
    for(int i=1; i<6; i++){
        //3 vehicles per lane for now
        for(int j=0; j<3; j++){
            //float# generation code from stackoverflow
            float r=randHI+static_cast <float>(rand())/(static_cast <float>(RAND_MAX/(randHI-randLO)));
            //creates a new truck in the vector, with position rand for X, lane[i] for Y,
            logV.push_back(Log(j*r, i));
            numOfLogs++;
        }
    }
}

void Game::run(){
    while(window.isOpen()){
        processEvents();
        update();
        render(); //clear/draw/display
    }
}
