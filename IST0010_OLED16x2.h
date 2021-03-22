/*
    IST0010_OLED16x2.h- Library for OLED16x2 with IST0010_OLED16x2
    Created by Joy-IT , 10. March 2021
    Released under the MIT License
*/


#ifndef IST0010_OLED16x2_H
#define IST0010_OLES16x2_H

#include "Print.h"
#include "Arduino.h"

#define CLEARDISPLAY 0x01
#define RETURNHOME 0x02
#define ENTRYMODE 0x06

#define DISPLAYOFF 0x08
#define DISPLAYON 0x0C
#define DISPLAYCURSOR 0x0E
#define DISPLAYBLINKING 0x0F
#define SHIFTDISPLAY_LEFT 0x18
#define SHIFTDISPLAY_RIGHT 0x1C

#define CGRAMADDR 0x40
#define DDRAMADDR 0x80

#define BIT_4_MODE 0x02
#define BIT_8_MODE 0x38

#define JAPANESE 0x00
#define EUROPEAN_I 0x01
#define RUSSIAN 0x02
#define EUROPEAN_II 0x03

enum class Direction {LEFT, RIGHT};

class IST0010_OLED16x2 : public Print{

public:
    IST0010_OLED16x2(uint8_t rs, uint8_t enable, uint8_t rw,
        uint8_t characterset = EUROPEAN_I, uint8_t character_height = 8);

    void init_4bit_6800(uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
    void init_8bit_6800(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4,
        uint8_t d5, uint8_t d6, uint8_t d7);
    void init_4bit_8080(uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
    void init_8bit_8080(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4,
        uint8_t d5, uint8_t d6, uint8_t d7);

    void clear();
    void firstPosition();
    void turnOff();
    void turnOn();
    void activateCursor();
    void blinkingCursor();
    void deactivateCursor();
    void shiftDisplay(Direction);
    void setCursor(uint8_t, uint8_t);

private:
    void writePins(uint8_t);
    void writing(uint8_t, uint8_t mode = LOW);
    virtual size_t write(uint8_t);
    void checkBusyFlag();
    void clocking(int);
    void clockingRead(int);
    void clockingWrite(int);

    uint8_t rs;
    uint8_t characterset;
    uint8_t character_height;
    uint8_t rw;
    uint8_t enable;
    uint8_t data[8];
    uint8_t busy_flag;
    int bits;
    int mode;
    uint8_t row_values[2] = {0x00, 0x40};
};


#endif
