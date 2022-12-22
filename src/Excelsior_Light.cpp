#include <Arduino.h>
#include <Excelsior_Light.h>

using namespace std;

Excelsior_Light& Excelsior_Light::operator=(Excelsior_Light other){
    for(int i = 0; i < 3; i++)
       _ports[i] = other._ports[i];
    return *this;
}


long Excelsior_Light::read(int color, bool percent, unsigned int lightDelay){
    long values[3];
    
    for(int i = 0; i < 3; i++){
        switch (color){                                   //determines which ports need to be set high or low to give the correct color and sets the next color in case a percentage value is wanted (percentage values are calculated in this function not avoid the use of the _calcNextTriad function)
            case WHITE:     values[i] = readRGB(255, 255, 255, false, lightDelay);                    break;          //For white and off there can't be a percentage determined by different outputs, therefore only a single value is needed 
            case RED:       values[i] = readRGB(255, 0  , 0  , false, lightDelay); color = GREEN;     break;
            case GREEN:     values[i] = readRGB(0  , 255, 0  , false, lightDelay); color = BLUE;      break;
            case BLUE:      values[i] = readRGB(0  , 0  , 255, false, lightDelay); color = RED;       break;
            case CYAN:      values[i] = readRGB(0  , 255, 255, false, lightDelay); color = MAGENTA;   break;
            case MAGENTA:   values[i] = readRGB(255, 0  , 255, false, lightDelay); color = YELLOW;    break;
            case YELLOW:    values[i] = readRGB(255, 255, 0  , false, lightDelay); color = CYAN;      break;
            default:        values[i] = readRGB(0  , 0  , 0  , false, lightDelay); color = OFF;       break;
        }

        if(!percent)                                     
            return values[0];              
        if(color == WHITE || color == OFF){                 //in case somebody still wants a value between 0 and 100 instead of 0 and 1024, but the color is WHITE or OFF
            return values[0] = 100L * values[0] / 1024;
        }
    }
    return 100L * values[0] / (values[0] + values[1] + values[2]);  
}

long Excelsior_Light::readHSV(int* hsv, bool percent, unsigned int lightDelay){
    hsv[0] %= 360;
    hsv[1] %= 100;
    hsv[2] %= 100;

    _HSVtoRGB(hsv);                               //hsv will now be rgb values
    return readRGB(hsv, percent, lightDelay);
}

long Excelsior_Light::readRGB(int* rgb, bool percent, unsigned int lightDelay){
    long values[3];

    for(int i = 0; i < 3; i++){
        rgb[i] %= 256;
    }

    for(int i = 0; i < 3; i++){
        analogWrite(_ports[0], rgb[0]);                     //RED
        analogWrite(_ports[1], rgb[1]);                     //GREEN
        analogWrite(_ports[2], rgb[2]);                     //BLUE
        delay(lightDelay);                                  //small delay to make sure the colors have changed that can be set via the parameter
        values[i] = 1024 - analogRead(_ports[3]);           //reading the sensor
    
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
        color[i] %= 256;                          //makes sure that the values are between 0 and 255
    } 

    _RGBtoHSV(color);
    color[0] = (color[0] + 120) % 360;            //next Triad is located 120° along the color wheel
    _HSVtoRGB(color);
}

void Excelsior_Light::_RGBtoHSV(int* color){
    float r = (float) color[0] / 255;
    float g = (float) color[1] / 255;
    float b = (float) color[2] / 255;

    float Cmax = max(r, max(g, b));
    float Cmin = min(r, min(g, b));
    float diff = Cmax - Cmin;
    int hue = 0;
    if (Cmax == r) {
        hue = (int)(60 * (g - b) / diff + 360) % 360;
    } else if (Cmax == g) {
        hue = (int)(60 * (b - r) / diff + 120) % 360;
    } else if (Cmax == b) {
        hue = (int)(60 * (r - g) / diff + 240) % 360;
    }
    int sat = (int) (diff / Cmax * 100);
    if (Cmax == 0) {
        sat = 0;
    }
    int val = (int) (Cmax * 100);

    color[0] = hue;
    color[1] = sat;
    color[2] = val;
}

void Excelsior_Light::_HSVtoRGB(int* color){
    float c = (float)color[2] / 100 * (float)color[1] / 100;
    float h = (float)color[0] / 60;
    float x = (float) (c * (1 - abs(fmodf(h,2) -1)));               //fmodf is a function that acts like a modulo operation,but for floats
    float m = (float)color[0] / 100 - c;

    float temp[3];
    if (h >= 0 && h < 1) {
        temp[0] = c;
        temp[1] = x;
        temp[2] = 0;
    } else if (h >= 1 && h < 2) {
        temp[0] = x;
        temp[1] = c;
        temp[2] = 0;
    } else if (h >= 2 && h < 3) {
        temp[0] = 0;
        temp[1] = c;
        temp[2] = x;
    } else if (h >= 3 && h < 4) {
        temp[0] = 0;
        temp[1] = x;
        temp[2] = c;
    } else if (h >= 4 && h < 5) {
        temp[0] = x;
        temp[1] = 0;
        temp[2] = c;
    } else if (h >= 5 && h <= 6) {
        temp[0] = c;
        temp[1] = 0;
        temp[2] = x;
    } else {
        temp[0] = 0;
        temp[1] = 0;
        temp[2] = 0;
    }

    for (int i = 0; i < 3; i++) {
        temp[i] += m;
        temp[i] *= 255;
        color[i] = (int) temp[i];
    }
}
