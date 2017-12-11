#include "game.h"

Game::Game(){
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Frogger v.01");
    window.setFramerateLimit(60);
    srand(time(nullptr));
    initTruck();        //create trucks
    initLog();          //create logs
    initWalls();        //create walls
    initSafe();         //create end safezones
    initSprites();
}

void Game::Draw(){

    window.draw(cuteFrog);
    //currently hardcoded at 15 cars and 15 logs
    for(int i=0; i<15; i++){
        truckV[i].Draw(window);
    }
    for(int i=0; i<15; i++){
        logV[i].Draw(window);
    }
    for(int i=0; i<4; i++){
        window.draw(wallV[i]);
    }
    for(int i=0; i<3; i++){
        window.draw(safezoneV[i]);
    }
    frog.Draw(window);
}

void Game::processEvents(){
    sf::Event event{};
    while(window.pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
                window.close();
                break;

                //key press check
            case sf::Event::KeyPressed:
                frog.Move(event);
                cout<<"frog at lane["<<frog.getLane()<<"]"<<endl;
                break;

            default:
                break;
        }
    }
}

void Game::update(){
    //updates obstacle location and checks collision
    for(int i=0; i<15; i++){
        truckV[i].Move();
    }
    for(int i=0; i<15; i++){
        logV[i].Move();
    }

    checkCollide();
    winCheck(winCounter);
    //debug update
//    if(frog.getAlive()) cout<<"Frog is alive."<<endl;
//    else                cout<<"Frog is dead."<<endl;
}

void Game::render(){
        window.clear();
        Draw();
        window.display();
    if (!frog.getAlive()){
        cout<<"YOU DIED!"<<endl;
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

//function that calls ifCollide based on where the frog is
void Game::checkCollide(){
    //for lane 0
    if(frog.getLane()==0){
        //hits the wall
        for(int i=0; i<4; i++){
            if(ifCollide(wallV[i])){
                frog.setAlive(false);  //squashed frog
            }
        }
        for(int i=0; i<3; i++){
            if(ifCollide(safezoneV[i])){
                safezoneV[i].setFillColor(sf::Color::White);
                frog.setAlive(true);
                frog.Reset();
                winCounter[i] = 1;
                cout<<"winCounter["<<i<<"] = "<<winCounter[i]<<endl
                    <<"total counter: {"<<winCounter[0]<<", "<<winCounter[1]<<", "<<winCounter[2]<<"}"<<endl;
            }
        }
    }
    //for lanes 1 to 5
    else if(frog.getLane()>=1&&frog.getLane()<=5){
        //set a flag for log collision
        bool flag=false;
        for(int i=0; i<15; i++){
            if(ifCollide(logV[i].GetShape())){
                //if colliding, set flag true and update frog pos
                flag=true;
                frog.Move(logV[i].getSpeed(),logV[i].getDir());
            }
        }
        //if no flag has been set, drowned frog
        if(!flag){
            frog.setAlive(false);
        }

        //if the frog is out of bounds, it's dead
        if(frog.GetShape().getPosition().x<0
           &&(frog.GetShape().getPosition().x
             +frog.GetShape().getSize().x)>SCREEN_WIDTH)
            frog.setAlive(false);
    }
    //for lanes 7 to 11
    else if(frog.getLane()>=7&&frog.getLane()<=11){
        for(int i=0; i<15; i++){
            if(ifCollide(truckV[i].GetShape())){
                frog.setAlive(false);   //squashed frog
            }
        }
    }
}

//this is rectangle shape not truck need to fix
void Game::initTruck(){
    int numOfTrucks=0;//not current utilized, maybe pass to Game::Draw()?
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

void Game::initWalls(){
    //we want 4 walls
    for (int i=0; i<4; i++){
        int wallX = 200*i;
        wallV.push_back(sf::RectangleShape(sf::Vector2f(100.0, 50.0)));
        wallV[i].setFillColor(sf::Color::Yellow);
        wallV[i].setPosition(sf::Vector2f(wallX, LANE[0]));
    }
}

void Game::initSafe(){
    //3 safe zones
    for (int i=0; i<3; i++){
        int safeX = ((200*i)+100);
        safezoneV.push_back(sf::RectangleShape(sf::Vector2f(100.0, 50.0)));
        safezoneV[i].setFillColor(sf::Color::Black);
        safezoneV[i].setPosition(sf::Vector2f(safeX, LANE[0]));
    }
}

void Game::run(){
    while(window.isOpen()){
        processEvents();
        update();
        render(); //clear/draw/display
    }
}

void Game::winCheck(int winCounter[]){
    if (winCounter[0] == 1 &&
        winCounter[1] == 1 &&
        winCounter[2] == 1){
        cout<<"WINNER WINNER CHICKEN DINNER!"<<endl;
    }
}

sf::Sprite Game::makeSprite(const string &fileName){
    sf::Texture texture;
    texture.loadFromFile(fileName);

    if (!texture.loadFromFile(fileName)){
        cout << "Load Failed!" << endl;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    return sprite;
}

void Game::initSprites(){
    cuteFrog = makeSprite("assets/cuteFrog.png");

}
