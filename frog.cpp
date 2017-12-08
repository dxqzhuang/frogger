#include "frog.h"

//default constructor
Frog::Frog() {
    frog.setSize(sf::Vector2f(40.0, 40.0));
    frog.setPosition(sf::Vector2f(SCREEN_WIDTH/2+5,LANE[12]+5));
    _lane=12;
}

//referenced call to main window to draw frog
void Frog::Draw(sf::RenderWindow &window) {
    window.draw(frog);
}

//function to move frog taking keyboard events as args
void Frog::Move(sf::Event event) {
    if (sf::Keyboard::Key::Left == event.key.code) {
        if(frog.getPosition().x-5>0)
            frog.move(-50, 0);
    }
    else if (sf::Keyboard::Key::Right == event.key.code) {
        if(frog.getPosition().x+frog.getSize().x+5<SCREEN_WIDTH)
            frog.move(50, 0);
    }
    else if (sf::Keyboard::Key::Up == event.key.code) {
        if((frog.getPosition().y-5>0))
            frog.move(0, -50);
            _lane++;
    }
    else if (sf::Keyboard::Key::Down == event.key.code) {
        if((frog.getPosition().y+frog.getSize().y+5<SCREEN_HEIGHT))
            frog.move(0, 50);
            _lane--;
    }
}

//function returning rectangle shape
sf::RectangleShape Frog::GetShape() {
    return frog;
}

int Frog::getLane(){
    return _lane;
}
