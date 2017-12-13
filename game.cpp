#include "game.h"
#include <iostream>

Game::Game(){
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Frogger v.01");
    window.setFramerateLimit(60);
    srand(time(nullptr));
    initTruck();        //create trucks
    initLog();          //create logs
    initWalls();        //create walls
    initSafe();         //create end safezones
}

void Game::Draw(){
    /* precnd: the vector objects exist and are initialized
     * postcnd: draws the individual objects
    */
    for(int i=0; i<NUM_OF_VEHICLE; i++){
        truckV[i].Draw(window);
    }
    for(int i=0; i<NUM_OF_LOG; i++){
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
    /* precnd:  frog is initialized
     * postcnd: updates the frog based on input
    */

    sf::Event event{};

    while(window.pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
                window.close();
                break;

            //key press check
            case sf::Event::KeyPressed:
            //frog only moveable when alive
                if(frog.getAlive()){
                    if (sf::Keyboard::Key::Left == event.key.code) {
                        frog.moveLeft();
                    }
                    else if (sf::Keyboard::Key::Right == event.key.code) {
                        frog.moveRight();
                    }
                    else if (sf::Keyboard::Key::Up == event.key.code) {
                        frog.moveUp();
                    }
                    else if (sf::Keyboard::Key::Down == event.key.code) {
                        frog.moveDown();
                    }
                    if(DEBUG)   cout<<"Frog at lane["<<frog.getLane()<<"]"<<endl;
                }
                //press R to reset
                if(sf::Keyboard::Key::R==event.key.code){
                    frog.Reset();
                    for(int i=0; i<3; i++){
                        winCounter[i] = 0;
                        safezoneV[i].setFillColor(sf::Color::Black);
                    }
                    cout<<"Game has been reset."<<endl;
                }
                break;

            default:
                break;
        }
    }
    if (!frog.getAlive()){
        cout<<"YOU DIED!"<<endl;
        frog.Reset();
    }
}

void Game::update(){
    /* precnd: none
     * postcnd: updates obstacle location and checks collision
     */
    for(int i=0; i<NUM_OF_VEHICLE; i++){
        truckV[i].Move();
    }
    for(int i=0; i<NUM_OF_LOG; i++){
        logV[i].Move();
    }

    gameProgress();
    winCheck(winCounter);

}

void Game::render(){
    window.clear();     //clear
    Draw();             //draw
    window.display();   //display
}

bool Game::ifCollide(sf::RectangleShape obstacle){
    /* precnd: an obstacle is passed in
     * postcnd: return true if the frog has boundary colliding with obstacle
     */
    bool collide=false;
    if(frog.GetShape().getGlobalBounds().intersects(obstacle.getGlobalBounds())){
        collide=true;
    }
    return collide;
}

void Game::gameProgress(){
    //function that calls ifCollide based on where the frog is
    /* precnd: everything is initialized
     * postcnd: updates frog and game state based on collision and lane location
     */
    int progress=frog.getLane();
    bool flag=false;                                            //set a flag for log collision

    switch(progress){
                                                                    //top lane
    case 0:
        for(int i=0; i<4; i++){                                     //frog hitting wall check
            if(ifCollide(wallV[i])){
                frog.setAlive(false);
            }
        }
        for(int i=0; i<3; i++){                                     //frog entering safe zone check
            if(ifCollide(safezoneV[i])){                            //if safezone already occupied
                if(winCounter[i]==1){                               //then set dead and reset
                    frog.setAlive(false);
                    cout<<"YOU DIED!"<<endl;
                    frog.Reset();
                }
                else{
                    safezoneV[i].setFillColor(sf::Color::White);    //if empty safezone
                    frog.Reset();                                   //reposition frog and update wincounter
                    winCounter[i] = 1;
                    if(DEBUG)
                        cout<<"winCounter["<<i<<"] = "<<winCounter[i]<<endl
                            <<"total counter:  {"<<winCounter[0]<<", "
                            <<winCounter[1]<<", "<<winCounter[2]<<"}"<<endl;
                }
            }
        }
        break;

    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        for(int i=0; i<NUM_OF_LOG; i++){                            //when at lanes 1 to 5
            if(ifCollide(logV[i].GetShape())){                      //check collision with logs
                flag=true;                                          //if colliding, set flag true
                frog.Move(logV[i].getSpeed(),logV[i].getDir());     //and update frog pos
            }
        }
        //if no flag has been set, drowned frog
        if(!flag){                                                  //if !flag
            frog.setAlive(false);                                   //frog has not been on a log
        }
        if(frog.GetShape().getPosition().x<0                        //out of bounds check
           ||(frog.GetShape().getPosition().x                       //when being carried by logs
             +frog.GetShape().getSize().x)>SCREEN_WIDTH)
            frog.setAlive(false);
        break;
    case 6:
        break;
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        for(int i=0; i<NUM_OF_VEHICLE; i++){                        //when between lanes 7 to 11
            if(ifCollide(truckV[i].GetShape())){                    //check vehicle collision
                frog.setAlive(false);
            }
        }
    default:
        break;
    }
}

float Game::getRand(int hi, int lo){
    /* precnd: upper and lower limit are passed in
     * postcnd: returns a random float between hi and lo
     */
    float r=hi+static_cast <float>(rand())/(static_cast <float>(RAND_MAX/(hi-lo)));
    return r;
}

void Game::initTruck(){
    /* precnd: none
     * postcnd: creates a vector of random distanced trucks
     */
    int counter=0;
    for(int lane=7; lane<=11; lane++){                      //creates vehicles from lane[7] to lane[11]
        for(int j=0; j<VEHICLE_PER_LANE[counter]; j++){     //NUM_OF_VEHICLES[j] vehicles per lane
            float r=getRand(200,100);
            truckV.push_back(Truck(j*r, lane));             //creates a new truck in the vector
        }                                                   //with position rand for X, lane[i] for Y
        counter++;
    }
}

void Game::initLog(){
    /* precnd: none
     * postcnd: creates a vector of random distanced logs
     */
    int counter=0;
    for(int lane=1; lane<=5; lane++){                       //creates logs from lane[1] to lane[5]
        for(int j=0; j<LOGS_PER_LANE[counter]; j++){        //NUM_OF_LOGS[counter] logs per lane
            float r=getRand(200,100);
            logV.push_back(Log(j*r, lane));                 //creates a new log in the vector
        }                                                   //with position rand for X, lane[i] for Y
        counter++;
    }
}

void Game::initWalls(){
    /* precnd: none
     * postcnd: creates 4 walls in the top lane
     */
    for (int i=0; i<4; i++){
        int wallX = 200*i;
        wallV.push_back(sf::RectangleShape(sf::Vector2f(100.0, 50.0)));
        wallV[i].setFillColor(sf::Color::Yellow);
        wallV[i].setPosition(sf::Vector2f(wallX, LANE[0]));
    }
}

void Game::initSafe(){
    /* precnd: none
     * postcnd: creates 3 safe zones in the top lane
     */
    for (int i=0; i<3; i++){
        int safeX = ((200*i)+100);
        safezoneV.push_back(sf::RectangleShape(sf::Vector2f(100.0, 50.0)));
        safezoneV[i].setFillColor(sf::Color::Black);
        safezoneV[i].setPosition(sf::Vector2f(safeX, LANE[0]));
    }
}

void Game::run(){
    /* precnd: window is open
     * postcnd: runs the game
     */
    while(window.isOpen()){
        processEvents();
        update();
        render();
    }
}

void Game::winCheck(int winCounter[]){
    /* precnd: winCounter is passed in
     * postcnd: output winning screen if winCounter is filled
     */
    if (winCounter[0] == 1 &&
        winCounter[1] == 1 &&
        winCounter[2] == 1){
        cout<<"WINNER WINNER CHICKEN DINNER!"<<endl;
    }
}
