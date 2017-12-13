#ifndef CONSTANTS_H
#define CONSTANTS_H

const int DEBUG = false;

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 650;
const float LANE[13]={0,50,100,150,200,250,300,350,400,450,500,550,600};

//changeable obstacle count -- the array sum need to match up with the int
const int NUM_OF_VEHICLE=12;
const int VEHICLE_PER_LANE[5]={2,3,2,3,2};
const int NUM_OF_LOG=13;
const int LOGS_PER_LANE[5]={2,3,3,3,2};

#endif // CONSTANTS_H
