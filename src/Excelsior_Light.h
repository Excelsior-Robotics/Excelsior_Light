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

        double read()                                                                           { return read(WHITE, false, 1, 1); };                            
        double read(int color)                                                                  { return read(color, false, 1, 1); };
        double read(int color, bool percent)                                                    { return read(color, percent, 1, 1); };
        double read(int color, bool percent, unsigned int lightDelay)                           { return read(color, percent, lightDelay, 1); };    
        double read(int color, bool percent, unsigned int lightDelay, unsigned int average);     

        double readHue(int hue)                                                                 { return readHue(hue, false, 1, 1); };          
        double readHue(int hue, bool percent)                                                   { return readHue(hue, percent, 1, 1); };
        double readHue(int hue, bool percent, unsigned int lightDelay)                          { return readHue(hue, percent, lightDelay, 1); };
        double readHue(int hue, bool percent, unsigned int lightDelay, unsigned int average);

        double readRGB(int red, int blue, int green)                                            { return readRGB(red, green, blue, false, 1, 1); };          
        double readRGB(int red, int blue, int green, bool percent)                              { return readRGB(red, green, blue, percent, 1, 1); };
        double readRGB(int red, int blue, int green, bool percent, unsigned int lightDelay)     { return readRGB(red, green, blue, percent, lightDelay, 1); };
        double readRGB(int red, int blue, int green, bool percent, unsigned int lightDelay, unsigned int average)     { int rgb[] = {red, green, blue}; return readRGB(rgb, percent, lightDelay, average);};
        double readRGB(int* rgb, bool percent, unsigned int lightDelay, unsigned int average);

    private: 
        void _calcNextTriadic(int* color);
        void _hueToRGB(int hue, int* color);


        int _ports[4];
};

#endif