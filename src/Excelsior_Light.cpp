#include <Arduino.h>
#include <Excelsior_Light.h>

using namespace std;

Excelsior_Light& Excelsior_Light::operator=(Excelsior_Light other){
    for(int i = 0; i < 4; i++)
       _ports[i] = other._ports[i];
    return *this;
}


double Excelsior_Light::read(int color, bool percent, unsigned int lightDelay, unsigned int average){
    switch (color){                                                                     //determines which ports need to be set high or low to give the correct color
        case WHITE:     return readRGB(255, 255, 255, false  , lightDelay, average);    //For white and off there can't be a percentage determined by different outputs
        case RED:       return readRGB(255, 0  , 0  , percent, lightDelay, average);
        case GREEN:     return readRGB(0  , 255, 0  , percent, lightDelay, average);
        case BLUE:      return readRGB(0  , 0  , 255, percent, lightDelay, average);
        case CYAN:      return readRGB(0  , 255, 255, percent, lightDelay, average);
        case MAGENTA:   return readRGB(255, 0  , 255, percent, lightDelay, average);
        case YELLOW:    return readRGB(255, 255, 0  , percent, lightDelay, average);
        default:        return readRGB(0  , 0  , 0  , false  , lightDelay, average);
    }
}

double Excelsior_Light::readHue(int hue, bool percent, unsigned int lightDelay, unsigned int average){
    int rgb[3];
    _hueToRGB(hue,rgb);
    return readRGB(rgb, percent, lightDelay, average);
}

double Excelsior_Light::readRGB(int* rgb, bool percent, unsigned int lightDelay, unsigned int average){
    double values[3];

    for(int i = 0; i < 3; i++){
        rgb[i] %= 256;
    }

    for(int i = 0; i < 3; i++){
        analogWrite(_ports[0], rgb[0]);                     //RED
        analogWrite(_ports[1], rgb[1]);                     //GREEN
        analogWrite(_ports[2], rgb[2]);                     //BLUE

        double sum = 0;
        for(int j = 0; j < average; j++){                   //if smoother values are wanted, avg determines the amount of samples for every sensor call
            delay(lightDelay);                              //small delay to make sure the colors have changed that can be set via the parameter
            sum += 1024 - analogRead(_ports[3]);            //reading the sensor
        }
        values[i] = sum / average;                          //values[i] takes on the average of the sampled values
        if(!percent)                                        //if a percentage value is not wanted, the first value can just be returned
            return values[0];
        if(rgb[0] + rgb[1] + rgb[2] == 0 || rgb[0] + rgb[1] + rgb[2] >= 255 * 3)      //if the color is either black or white there is no need for three repeated scans, but someone might still want a percentage value between 0 and 100
            return 100L * values[0] / 1024;

        _calcNextTriadic(rgb);  	                        //calculates next RGB Value that is located 120° further along the color wheel
    }
    return (100L * values[0] / (values[0] + values[1] + values[2]));
}


void Excelsior_Light::_calcNextTriadic(int* color){   
    for(int i = 0; i < 3; i++){
        color[i] %= 256;                                    //makes sure that the values are between 0 and 255
    } 

    int temp = color[0];
    color[0] = color[1];
    color[1] = color[2];
    color[2] = temp;
}

void Excelsior_Light::_hueToRGB(int hue, int* color){
    int val = float(hue % 60) / 60 * 255;                   //RGB values follow the patten: (255, val, 0) or (255,255-val,0). The order of these three values changes as given by the switch function
    val = hue % 120 >= 60? 255 - val: val;                  //val counts up to 255 and then back down to 0 if the hue goes from 0 to 120

    int num = (hue % 360) / 60;
    switch(num){                                            //determins order of the triple
        case 0: color[0] = 255; color[1] = val; color[2] = 0  ; break;
        case 1: color[0] = val; color[1] = 255; color[2] = 0  ; break;
        case 2: color[0] = 0  ; color[1] = 255; color[2] = val; break;
        case 3: color[0] = 0  ; color[1] = val; color[2] = 255; break;
        case 4: color[0] = val; color[1] = 0  ; color[2] = 255; break;
        case 5: color[0] = 255; color[1] = 0  ; color[2] = val; break;
    }
}