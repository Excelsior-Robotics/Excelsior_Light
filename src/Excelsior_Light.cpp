#include <Arduino.h>
#include <Excelsior_Light.h>

using namespace std;
//------SETUP------------------
ELight::ELight(int red, int green, int blue, int signal){       //ports for the signals
    _ports = {red, green, blue, signal};
}

long ELight::readSensor(int color, bool percent){
    int output[3];
    long values[3];

    for(int i = 0; i < 3; i++){
        bool single = !percent;                           //if percent is fales only a single value will be determined
        switch (color){                                   //determines which ports need to be set high or low to give the correct color and sets the next color in case a percentage value is wanted
            case WHITE:     output = {HIGH, HIGH, HIGH}; single = true;     break;          //For white and off there can't be a percentage determined by different colors, therefore only a single value is needed 
            case RED:       output = {HIGH, LOW , LOW }; color = GREEN;     break;
            case GREEN:     output = {LOW , HIGH, LOW }; color = BLUE;      break;
            case BLUE:      output = {LOW , LOW , HIGH}; color = RED;       break;
            case CYAN:      output = {LOW , HIGH, HIGH}; color = MAGENTA;   break;
            case MAGENTA:   output = {HIGH, LOW , HIGH}; color = YELLOW;    break;
            case YELLOW:    output = {HIGH, HIGH, LOW }; color = CYAN;      break;
            default:        output = {LOW , LOW , LOW }; single = false;    break;
        }

        digitalWrite(_ports[0], output[0]);
        digitalWrite(_ports[1], output[1]);
        digitalWrite(_ports[2], output[2]);
        delay(_lightDelay);                                 //small delay to make sure the colors have changed
        values[i] = 1024 - analogRead(_ports[3]);           //reading the sensor

        if(stop){                                           //there are no procentages for White, since the color wouldn't switch
            if(percent)                                     //in case somebody still wants a value between 0 and 100 instead of 0 and 1024, but the color is WHITE or OFF
                values[0] = 100L * values[0] / 1024;              
            break;
        }
    }
    return percent? (100L * values[0] / (values[0] + values[1] + values[2])) : values[0];  
}

ELight::changeLightDelay(int delay)[
    _lightDelay = delay;
]