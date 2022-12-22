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

        long read()                                                                                 { return read(WHITE,false,1); };                            
        long read(int color)                                                                        { return read(color,false,1); };
        long read(int color, bool percent)                                                          { return read(WHITE,percent,1); };
        long read(int color, bool percent, unsigned int lightDelay);     

        long readHSV(int hue, int saturation, int value)                                            { return readHSV(hue, saturation, value, false, 1);};          
        long readHSV(int hue, int saturation, int value, bool percent)                              { return readHSV(hue, saturation, value, percent, 1);};
        long readHSV(int hue, int saturation, int value, bool percent, unsigned int lightDelay)     { int hsv[] = {hue, saturation, value}; return readHSV(hsv, percent, lightDelay);};
        long readHSV(int* hsv, bool percent, unsigned int lightDelay);                              

        long readRGB(int red, int blue, int green)                                                  { return readRGB(red, green, blue, false, 1);};          
        long readRGB(int red, int blue, int green, bool percent)                                    { return readRGB(red, green, blue, percent, 1);};
        long readRGB(int red, int blue, int green, bool percent, unsigned int lightDelay)           { int rgb[] = {red, green, blue}; return readRGB(rgb, percent, lightDelay);};
        long readRGB(int* rgb, bool percent, unsigned int lightDelay);

    private: 
        void _calcNextTriadic(int* color);
        void _RGBtoHSV(int* color);
        void _HSVtoRGB(int* color);

        int _ports[4];
};

#endif