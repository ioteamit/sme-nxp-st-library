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
    
    while (!SerialUSB) {
        ;
    }
}

// the loop function runs over and over again forever
void loop() {
    uint8_t diff;

    do {
        delay(1000);
        
        SerialUSB.print("Button 1 Status = ");
        SerialUSB.println(senShi.isButton1Pressed(), HEX);

        SerialUSB.print("Button 2 Status = ");
        SerialUSB.println(senShi.isButton2Pressed(), HEX);

        SerialUSB.print("Button 3 Status = ");
        SerialUSB.println(senShi.isButton3Pressed(), HEX);
        
    } while (1);
    
}
