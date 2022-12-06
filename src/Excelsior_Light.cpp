#include <Arduino.h>
#include <Excelsior_Light.h>

using namespace std;
//------SETUP------------------
ELight::ELight(int red, int green, int blue, int signal){       //ports for the signals
    _ports = {red, green, blue, signal};
}

ELight::readSensor(int color, bool percent){
    int output[3];
    int values[3];

    for(int i = 0; i < 3; i++){
        switch (color){                                   //determines which ports need to be set high or low to give the correct color
            case WHITE:     output = {HIGH, HIGH, HIGH}; break;
            case RED:       output = {HIGH, LOW , LOW }; break;
            case GREEN:     output = {LOW , HIGH, LOW }; break;
            case BLUE:      output = {LOW , LOW , HIGH}; break;
            case CYAN:      output = {LOW , HIGH, HIGH}; break;
            case MAGENTA:   output = {HIGH, LOW , HIGH}; break;
            case YELLOW:    output = {HIGH, HIGH, LOW }; break;
            default:        output = {LOW , LOW , LOW };
        }

        digitalWrite(_ports[0], output[0]);
        digitalWrite(_ports[1], output[1]);
        digitalWrite(_ports[2], output[2]);
        delay(_lightDelay);                               //small delay to make sure the colors have changed
        value[i] = 1024 - analogRead(_ports[3]);

        switch (color){                                   //goes to the next color of the group of three for the next loop
            case RED:       color = GREEN; break;
            case GREEN:     color = BLUE; break;
            case BLUE:      color = RED; break;
            case CYAN:      color = MAGENTA; break;
            case MAGENTA:   color = YELLOW; break;
            case YELLOW:    color = CYAN; break;
            default:        percent = false;              //to break out of the loop
        }

        if(!percent)                                      //there are no procentages for White, since the color wouldn't switch
            break;
    }
    return percent? value[0] / (value[0] + value[1] + value[2]) : value[0];  
}

ELight::changeLightDelay(int delay)[
    _lightDelay = delay;
]