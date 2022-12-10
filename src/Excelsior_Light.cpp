#include <Arduino.h>
#include <Excelsior_Light.h>

using namespace std;

Excelsior_Light& Excelsior_Light::operator=(Excelsior_Light other){
    for(int i = 0; i < 3; i++)
       _ports[i] = other._ports[i];
    return *this;
}


long Excelsior_Light::read(int color, bool percent){
    int output[3];
    long values[3];
    
    bool single = !percent;                           //if percent is fales only a single value will be determined

    for(int i = 0; i < 3; i++){
        switch (color){                                   //determines which ports need to be set high or low to give the correct color and sets the next color in case a percentage value is wanted
            case WHITE:     output[0] = HIGH; output[1] = HIGH; output[2] = HIGH; single = true;     break;          //For white and off there can't be a percentage determined by different outputs, therefore only a single value is needed 
            case RED:       output[0] = HIGH; output[1] = LOW ; output[2] = LOW ; color = GREEN;     break;
            case GREEN:     output[0] = LOW ; output[1] = HIGH; output[2] = LOW ; color = BLUE;      break;
            case BLUE:      output[0] = LOW ; output[1] = LOW ; output[2] = HIGH; color = RED;       break;
            case CYAN:      output[0] = LOW ; output[1] = HIGH; output[2] = HIGH; color = MAGENTA;   break;
            case MAGENTA:   output[0] = HIGH; output[1] = LOW ; output[2] = HIGH; color = YELLOW;    break;
            case YELLOW:    output[0] = HIGH; output[1] = HIGH; output[2] = LOW ; color = CYAN;      break;
            default:        output[0] = LOW ; output[1] = LOW ; output[2] = LOW ; single = false;    break;
        }

        digitalWrite(_ports[0], output[0]);
        digitalWrite(_ports[1], output[1]);
        digitalWrite(_ports[2], output[2]);
        delay(_lightDelay);                                 //small delay to make sure the colors have changed
        values[i] = 1024 - analogRead(_ports[3]);           //reading the sensor

        if(single){                                         //there are no procentages for White, since the color wouldn't switch
            if(percent)                                     //in case somebody still wants a value between 0 and 100 instead of 0 and 1024, but the color is WHITE or OFF
                values[0] = 100L * values[0] / 1024;              
            break;
        }
    }
    return percent? (100L * values[0] / (values[0] + values[1] + values[2])) : values[0];  
}

void Excelsior_Light::changeLightDelay(int delay){
    _lightDelay = delay;
}