#ifndef ALTREAD_HPP
#define ALTREAD_HPP

#include <Adafruit_BMP280.h>


Adafruit_BMP280 bmp;

Adafruit_Sensor *bmp_temp;
Adafruit_Sensor *bmp_pressure;

float zero = 0;

float oldVal = 0;
float newVal;
//(bmp.readAltitude(1013.25) * 3.28 - zero);

float altRaw(){
    float raw = (bmp.readAltitude(1013.25) * 3.28);
    return raw;
}

float altZero(){
    zero = altRaw();
    return zero;
}

float altRead(float zero) {
    float alt = 0;
    float mult = .25;
    newVal = (bmp.readAltitude(1013.25) * 3.28 - zero);
    alt = (newVal * mult) + (oldVal * (1 - mult));
    
    oldVal = alt;

    return alt;
}


#endif