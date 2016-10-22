/*
* cc2541.cpp
*
* Created: 01/01/2016 22:15:38
*  Author: development
*/
#include <Arduino.h>
#include <Wire.h>
#include "SenShi.h"


#define TCA6416A_ADDRESS 0x20
#define CONF_PORT_0     0b00111000
#define INIT_P0         0b00000111  // ligth of the 3 leds

#define CONF_PORT_1     0b00110101
#define INIT_P1         0b11001010
#define VALUE_GPS_FORCE_ON   0b10001010

// Protocol          PowerOn Default
#define INPUT_PORT_0    0x00 //Read byte          xxxx xxxx (undefined)
#define INPUT_PORT_1    0x01 //Read byte          xxxx xxxx
#define OUTPUT_PORT_0   0x02 //Read/write byte    1111 1111
#define OUTPUT_PORT_1   0x03 //Read/write byte    1111 1111
#define P_INVERT_PORT_0 0x04 //Read/write byte    0000 0000
#define P_INVERT_PORT_1 0x05 //Read/write byte    0000 0000
#define CONFIG_PORT_0   0x06 //Read/write byte    1111 1111
#define CONFIG_PORT_1   0x07 //Read/write byte    1111 1111


#define LED_G_PIN       0x1
#define LED_Y_PIN       0x2
#define LED_R_PIN       0x4
#define BUTTON_1_PIN    0x8
#define BUTTON_2_PIN    0x10
#define BUTTON_3_PIN    0x20
#define NA_1_PIN        0x40
#define NA_1_PIN        0x80

#define SFX_STDBY_STS_PIN   0x1
#define SFX_RESET_PIN       0x2
#define SFX_RADIO_STS_PIN   0x4
#define SFX_WAKEUP_PIN      0x8
#define NFC_FD_PIN         0x10
#define HUT_DRDY_PIN        0x20
#define GPS_FORCE_ON_PIN    0x40
#define GPS_RESET_PIN       0x80

byte SenShi::readRegister(byte _address, byte regToRead)
{
    Wire.beginTransmission(_address);
    Wire.write(regToRead);
    Wire.endTransmission(false); //endTransmission but keep the connection active

    Wire.requestFrom(_address, 1); //Ask for 1 byte, once done, bus is released by default

    while(!Wire.available()) ; //Wait for the data to come back
    return Wire.read(); //Return this one byte
}

// Writes a single byte (dataToWrite) into regToWrite
bool SenShi::writeRegister(byte _address, byte regToWrite, byte dataToWrite)
{
    Wire.beginTransmission(_address);

    if (!Wire.write(regToWrite)) {
        return false;
    }
    if (!Wire.write(dataToWrite)) {
        return false;
    }

    uint8_t errorNo = Wire.endTransmission(); //Stop transmitting
    return (errorNo == 0);
}



SenShi::SenShi(void)
{
    
    
}

void SenShi::begin(void) {
    Wire.begin();
    if (writeRegister( TCA6416A_ADDRESS, CONFIG_PORT_0, CONF_PORT_0)!=false) {
        writeRegister( TCA6416A_ADDRESS, OUTPUT_PORT_0, INIT_P0); // 
    }

    if (writeRegister( TCA6416A_ADDRESS, CONFIG_PORT_1, CONF_PORT_1)!=false){
        writeRegister( TCA6416A_ADDRESS, OUTPUT_PORT_1, INIT_P1); // 
    }
}

uint8_t actualPortValue;
void SenShi::ledRedLight(uint32_t value)   {
    uint8_t actualPortValue;

    actualPortValue = readRegister( TCA6416A_ADDRESS, OUTPUT_PORT_0);
    
    if (value == HIGH) {
        writeRegister( TCA6416A_ADDRESS, OUTPUT_PORT_0, (actualPortValue & (~LED_R_PIN)));
    } else if (value == LOW) {
        writeRegister( TCA6416A_ADDRESS, OUTPUT_PORT_0, (actualPortValue  |(LED_R_PIN)));
    } else {
        writeRegister( TCA6416A_ADDRESS, OUTPUT_PORT_0, (actualPortValue & (~LED_R_PIN)));
    }    
}

void SenShi::ledGreenLight(uint32_t value) {
    uint8_t actualPortValue;

    actualPortValue = readRegister( TCA6416A_ADDRESS, OUTPUT_PORT_0);
    
    if (value == HIGH) {
        writeRegister( TCA6416A_ADDRESS, OUTPUT_PORT_0, (actualPortValue & (~LED_G_PIN)));
        } else if (value == LOW) {
        writeRegister( TCA6416A_ADDRESS, OUTPUT_PORT_0, (actualPortValue  |(LED_G_PIN)));
        } else {
        writeRegister( TCA6416A_ADDRESS, OUTPUT_PORT_0, (actualPortValue & (~LED_G_PIN)));
    }   
}

void SenShi::ledYellowLight(uint32_t value) {
    uint8_t actualPortValue;

    actualPortValue = readRegister( TCA6416A_ADDRESS, OUTPUT_PORT_0);
    
    if (value == HIGH) {
        writeRegister( TCA6416A_ADDRESS, OUTPUT_PORT_0, (actualPortValue & (~LED_Y_PIN)));
        } else if (value == LOW) {
        writeRegister( TCA6416A_ADDRESS, OUTPUT_PORT_0, (actualPortValue  |(LED_Y_PIN)));
        } else {
        writeRegister( TCA6416A_ADDRESS, OUTPUT_PORT_0, (actualPortValue & (~LED_Y_PIN)));
    }   
}

byte SenShi::isButton1Pressed(void) {
    uint8_t actualPortValue;

    actualPortValue = readRegister( TCA6416A_ADDRESS, INPUT_PORT_0);
    
    return !((actualPortValue & BUTTON_1_PIN) == BUTTON_1_PIN);
    
}

byte SenShi::isButton2Pressed(void) {
    uint8_t actualPortValue;

    actualPortValue = readRegister( TCA6416A_ADDRESS, INPUT_PORT_0);
    
    return !((actualPortValue & BUTTON_2_PIN) == BUTTON_2_PIN);
    
}

byte SenShi::isButton3Pressed(void) {
    uint8_t actualPortValue;

    actualPortValue = readRegister( TCA6416A_ADDRESS, INPUT_PORT_0);
    
    return !((actualPortValue & BUTTON_3_PIN) == BUTTON_3_PIN);
    
}
SenShi  senShi;
