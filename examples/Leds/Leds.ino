/*
SmeIoT Library - ReadSWVersion

The Sketch shows the FwVersion of the Telit SigFox chip

created 27 Nov 2015
by Mik (smkk@axelelettronica.it)

This example is in the public domain
https://github.com/ameltech

Telit le51-868-s more information available here:
http://www.telit.com/products/product-service-selector/product-service-selector/show/product/le51-868-s/
*/

#include <Arduino.h>
#include "SenShi.h"

// the setup function runs once when you press reset or power the board
void setup() {

    SerialUSB.begin(115200);
    senShi.begin();
    
    senShi.ledYellowLight(LOW);
    senShi.ledGreenLight(LOW);
    senShi.ledRedLight(LOW);
    
    while (!SerialUSB) {
        ;
    }
    senShi.ledYellowLight(HIGH);
    senShi.ledGreenLight(HIGH);
    senShi.ledRedLight(HIGH);
}

// the loop function runs over and over again forever
void loop() {
    uint8_t diff;

    do {
        delay(1000);
        senShi.ledYellowLight(LOW);
        delay(1000);
        senShi.ledGreenLight(LOW);
        delay(1000);
        senShi.ledRedLight(LOW);
        
        delay(1000);
        senShi.ledYellowLight(HIGH);
        delay(1000);
        senShi.ledGreenLight(HIGH);
        delay(1000);
        senShi.ledRedLight(HIGH);
        
    } while (1);
    
}

