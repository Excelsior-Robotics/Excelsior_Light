#ifndef Excelsior_Light_h
#define Excelsior_Light_h

#include <Arduino.h>

using namespace std;

//define what color is which number for the switch cases and also what variables are used here
#define OFF          0
#define WHITE        1
#define RED          2
#define GREEN        3
#define BLUE         4
#define CYAN         5
#define MAGENTA      6
#define YELLOW       7

class ELight{
    public:
        ELight(int red, int green, int blue, int signal);
        void changeLightDelay(int delay);
        long readSensor() {readSensor(WHITE,false)};
        long readSensor(int color) {readSensor(color,false)};
        long readSensor(int color, bool percent);
    
    private:        
        int _ports[4];
        int _lightDelay = 1;                                  //not realy neccessary to have a higher number, as even 1 millisecond doesnt reduce the quality of the brightnesvalue
}

#endif