#include <IST0010_OLED16x2.h>

IST0010_OLED16x2 oled(/* RS: */ 6, /* Enable: */ 8, /* RW: */ 7 /* , characterset: default EUROPEAN_I, character height: default 8*/);

void setup() {
    oled.init_4bit_6800(/* D4: */ 9, /* D5: */ 10, /* D6: */ 11, /* D7 */ 12);

    oled.print("Joy-IT");
    oled.setCursor(0,1);
    oled.print("OLED Test");
    delay (10000);
    oled.clear();

    oled.firstPosition();
    oled.blinkingCursor();
    delay(5000);
    oled.deactivateCursor();

    oled.shiftDisplay(Direction::RIGHT);
    oled.shiftDisplay(Direction::RIGHT);
    oled.print("shifting");
    delay(5000);

    oled.shiftDisplay(Direction::LEFT);
    oled.shiftDisplay(Direction::LEFT);
    oled.clear();
    oled.firstPosition();
    oled.turnOff();
}

void loop() {
    //nothing
}
