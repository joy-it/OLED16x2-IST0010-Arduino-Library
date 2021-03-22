/*
    IST0010_OLED16x2.cpp - Library for OLED16x2 with IST0010_OLED16x2
    Created by Joy-IT , 10. March 2021
    Released under the MIT License
*/

#include "IST0010_OLED16x2.h"
#include "Arduino.h"

IST0010_OLED16x2::IST0010_OLED16x2(uint8_t rs, uint8_t enable, uint8_t rw,
    uint8_t characterset = EUROPEAN_I, uint8_t character_height = 8){
        // Setting some pins
        (*this).enable = enable;
        (*this).rs = rs;
        (*this).rw = rw;
        (*this).characterset = characterset;
        if (character_height == 8) (*this).character_height = 0x00;
        if (character_height == 10) (*this).character_height = 0x04;
    }

void IST0010_OLED16x2::init_4bit_6800(uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7){
    // initialisation of 4bit 6800 parallel
    bits = 4;
    mode = 6800;
    data[0] = d4;
    data[1] = d5;
    data[2] = d6;
    data[3] = busy_flag = d7;   //setting data pins

    pinMode(rs, OUTPUT);
    pinMode(rw, OUTPUT);
    pinMode(enable, OUTPUT);

    digitalWrite(rs, LOW);
    digitalWrite(rw, LOW);
    digitalWrite(enable, LOW);
    delayMicroseconds(5000);

    for (int i = 0; i < 4; i++) {
        pinMode(data[i], OUTPUT);
        digitalWrite(data[i], LOW);
    }

    // setup routine
    writePins(0x03);
    delayMicroseconds(5000);
    writing(0x08);
    delayMicroseconds(5000);
    writePins(BIT_4_MODE);
    delayMicroseconds(5000);
    writePins(BIT_4_MODE);
    delayMicroseconds(5000);
    writePins(0x08 | characterset | character_height);
    delayMicroseconds(5000);
    writing(DISPLAYOFF);
    delayMicroseconds(5000);
    writing(CLEARDISPLAY);
    delayMicroseconds(5000);
    writing(ENTRYMODE);
    delayMicroseconds(5000);
    writing(RETURNHOME);
    delayMicroseconds(5000);
    writing(DISPLAYON);
    delayMicroseconds(5000);
}

void IST0010_OLED16x2::init_8bit_6800(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4,
    uint8_t d5, uint8_t d6, uint8_t d7){

    // initialisation of 8bit 6800 parallel
    bits = 8;
    mode = 6800;
    data[0] = d0;
    data[1] = d1;
    data[2] = d2;
    data[3] = d3;
    data[4] = d4;
    data[5] = d5;
    data[6] = d6;
    data[7] = busy_flag = d7;   //setting data pins

    pinMode(rs, OUTPUT);
    pinMode(rw, OUTPUT);
    pinMode(enable, OUTPUT);

    digitalWrite(rs, LOW);
    digitalWrite(rw, LOW);
    digitalWrite(enable, LOW);
    delayMicroseconds(5000);

    for (int i = 0; i < 8; i++) {
        pinMode(data[i], OUTPUT);
        digitalWrite(data[i], LOW);
    }

    // setup routine
    writePins(0X08);
    writePins(BIT_8_MODE | characterset | character_height);
    delayMicroseconds(5000);
    writing(DISPLAYOFF);
    writing(CLEARDISPLAY);
    writing(ENTRYMODE);
    writing(RETURNHOME);
    writing(DISPLAYON);
}

void IST0010_OLED16x2::init_4bit_8080(uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7){

    // initialisation of 4 bit 8080 parallel
    bits = 4;
    mode = 8080;
    data[0] = d4;
    data[1] = d5;
    data[2] = d6;
    data[3] = busy_flag = d7;   //setting data pins

    pinMode(rs, OUTPUT);
    pinMode(enable, OUTPUT);
    pinMode(rw, OUTPUT);

    digitalWrite(rs, LOW);
    digitalWrite(enable, HIGH);
    digitalWrite(rw, HIGH);
    delayMicroseconds(5000);

    for (int i = 0; i < 4; i++) {
        pinMode(data[i], OUTPUT);
        digitalWrite(data[i], LOW);
    }

    // setup routine
    writePins(0x03);
    delayMicroseconds(5000);
    writing(0x08);
    delayMicroseconds(5000);
    writePins(BIT_4_MODE);
    delayMicroseconds(5000);
    writePins(BIT_4_MODE);
    delayMicroseconds(5000);
    writePins(0x08 | characterset | character_height);
    delayMicroseconds(5000);
    writing(DISPLAYOFF);
    delayMicroseconds(5000);
    writing(CLEARDISPLAY);
    delayMicroseconds(5000);
    writing(ENTRYMODE);
    delayMicroseconds(5000);
    writing(RETURNHOME);
    delayMicroseconds(5000);
    writing(DISPLAYON);
    delayMicroseconds(5000);
}

void IST0010_OLED16x2::init_8bit_8080(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4,
    uint8_t d5, uint8_t d6, uint8_t d7){

    // initialisation of 8 bit 8080 parallel
    bits = 8;
    mode = 8080;
    data[0] = d0;
    data[1] = d1;
    data[2] = d2;
    data[3] = d3;
    data[4] = d4;
    data[5] = d5;
    data[6] = d6;
    data[7] = busy_flag = d7;   //setting data pins

    pinMode(rs, OUTPUT);
    pinMode(enable, OUTPUT);
    pinMode(rw, OUTPUT);

    digitalWrite(rs, LOW);
    digitalWrite(enable, HIGH);
    digitalWrite(rw, HIGH);
    delayMicroseconds(5000);

    for (int i = 0; i < 8; i++) {
        pinMode(data[i], OUTPUT);
        digitalWrite(data[i], LOW);
    }

    //setup routine
    writePins(0X08);
    writePins(BIT_8_MODE | characterset | character_height);
    delayMicroseconds(5000);
    writing(DISPLAYOFF);
    writing(CLEARDISPLAY);
    writing(ENTRYMODE);
    writing(RETURNHOME);
    writing(DISPLAYON);

}

// writing sequence, set RegisterSelect and RW on the correct value
void IST0010_OLED16x2::writing(uint8_t value, uint8_t level = LOW){
    digitalWrite(rs, level);
    if(mode == 6800) digitalWrite(rw, LOW);

    if(bits == 4) writePins(value >> bits); // only by 4 bit communication
    writePins(value);
    checkBusyFlag();    //checking if chip is busy
}

// will be called up with print method, is for writing on the display
inline size_t IST0010_OLED16x2::write(uint8_t value){
    writing(value, HIGH);
}

// will send bits to data lines
void IST0010_OLED16x2::writePins(uint8_t value){

    for (int i = 0; i < bits; i++){
        digitalWrite(data[i], (value >> i) & 0x01);
    }
    delayMicroseconds(50);
    if(mode == 8080) clockingWrite(50);
    if(mode == 6800) clocking(50);
}

// this method is for 6800 parallel
// enables chip for communication
void IST0010_OLED16x2::clocking(int time){
    digitalWrite(enable, HIGH);
    delayMicroseconds(time);
    digitalWrite(enable, LOW);
}

// this method is for 8080 parallel
// enables chip for writing
void IST0010_OLED16x2::clockingWrite(int time){
    digitalWrite(rw, LOW);
    delayMicroseconds(time);
    digitalWrite(rw, HIGH);
}

// this method is for 8080 parallel
// enables chip for reading
void IST0010_OLED16x2::clockingRead(int time){
    digitalWrite(enable, LOW);
    delayMicroseconds(time);
    digitalWrite(enable, HIGH);
}

// checking if chip is busy
void IST0010_OLED16x2::checkBusyFlag(){
    pinMode(busy_flag, INPUT);  // setting data pin 7 as busy flag
    digitalWrite(rs, LOW);
    if(mode == 6800) digitalWrite(rw, HIGH);
    unsigned char flag = 1;

    do{
        if(mode == 6800) digitalWrite(enable, HIGH);
        if(mode == 8080) digitalWrite(enable, LOW);

      	delayMicroseconds(10);
      	flag = digitalRead(busy_flag);

        if(mode == 6800) digitalWrite(enable, LOW);
        if(mode == 8080) digitalWrite(enable, HIGH);
        // 4bit communication calls up impulse two times

        if(bits == 4 && mode == 6800) clocking(50);
        if(bits == 4 && mode == 8080) clockingRead(50);
    } while (flag); // as long as the chip is busy no signal will be sent

    pinMode(busy_flag, OUTPUT); // setting busy flag back as a data pin
    if(mode == 6800) digitalWrite(rw, LOW);
}

// clears display
void IST0010_OLED16x2::clear(){
    writing(CLEARDISPLAY);
}

// setting cursor to the first position
void IST0010_OLED16x2::firstPosition(){
    writing(RETURNHOME);
}

// turns off the display
void IST0010_OLED16x2::turnOff(){
    writing(DISPLAYOFF);
}

// turns on the display
void IST0010_OLED16x2::turnOn(){
    writing(DISPLAYON);
}

// makes cursor visible
void IST0010_OLED16x2::activateCursor(){
    writing(DISPLAYCURSOR);
}

// the cursor blinks
void IST0010_OLED16x2::blinkingCursor(){
    writing(DISPLAYBLINKING);
}

// makes the cursor invisible again
void IST0010_OLED16x2::deactivateCursor(){
    writing(DISPLAYON);
}

// shifts display one position into a direction
void IST0010_OLED16x2::shiftDisplay(Direction direction){
    if(direction == Direction::LEFT) writing(SHIFTDISPLAY_LEFT);
    if(direction == Direction::RIGHT) writing(SHIFTDISPLAY_RIGHT);
}

// set cursor to an explicit position
void IST0010_OLED16x2::setCursor(uint8_t column, uint8_t row){
    if (row >= 2) row = 0;
    writing(DDRAMADDR | (column + row_values[row]));
}
