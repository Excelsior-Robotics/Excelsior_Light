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

class Excelsior_Light{
    public:
        Excelsior_Light() : _ports{0,1,2,3} {};             //should only be used to redefine the sensorInput later on in the program
        Excelsior_Light(int red, int green, int blue, int signal) : _ports{red, green, blue, signal} {};
        Excelsior_Light(Excelsior_Light const&) = default;
        Excelsior_Light& operator=(Excelsior_Light other);

        void changeLightDelay(int delay);
        long read() { return read(WHITE,false); };
        long read(int color) { return read(color,false); };
        long read(int color, bool percent);
    
    private:        
        int _ports[4];
        int _lightDelay = 1;                                  //not realy neccessary to have a higher number, as even 1 millisecond doesnt reduce the quality of the brightnesvalue
};

#endif