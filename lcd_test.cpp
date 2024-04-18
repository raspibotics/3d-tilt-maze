 /*  N5110_LCD_Test
*    ===============
*
*    Function:               Basic functionality test of the Nokia N5110 LCD display and N5110.h
*    Circuit Schematic No.:  9     : https://github.com/ELECXJEL2645/Circuit_Schematics
*    Required Libraries:     N5110 : https://github.com/ELECXJEL2645/N5110
*
*    Authored by:            Andrew Knowles
*    Date:                   2021
*    Collaberators:          Dr Craig Evans
*                            Dr Alexander Valavanis
*                            Dr Tim Amsdon
*    Version:                2.0
*    Revision Date:          06/2022 
*    MBED Studio Version:    1.4.1
*    MBED OS Version:        6.14.0
*    Board:	                 NUCLEO L476RG  */

// #define LCD_TEST_ACTIVE
#ifdef LCD_TEST_ACTIVE

#include "mbed.h"
#include "N5110.h"
#include <cstdio>

//Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)  
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);

void contrastTest();
void brightnessTest();
void modeTest();
void printTest();
void powerDown();

char buffer[14] = {0};

const int Fish[4][9]= {
    { 1,0,0,1,1,1,1,1,0, },
    { 1,1,1,1,1,1,1,0,1, },
    { 1,1,1,1,1,1,1,1,1, },
    { 1,0,0,1,1,1,1,1,0, },
};

int main(){
    //lcd.init(LPH7366_6);        //initialise for LPH7366-1 LCD (Options are LPH7366_1 and LPH7366_6)
    lcd.init(LPH7366_1);
    lcd.setContrast(0.55);      //set contrast to 55%
    lcd.setBrightness(0.5);     //set brightness to 50% (utilises the PWM)

    contrastTest();
    brightnessTest();
    modeTest();
    printTest();
    powerDown();

}

void contrastTest(){
    lcd.clear();
    lcd.printString("Begin Contrast", 0, 1);
    lcd.printString("     Test     ", 0, 2);
    lcd.refresh();
    ThisThread::sleep_for(1s);

    float contrast = 0.0;

    while(contrast <= 1.0){
        lcd.clear();
        lcd.setContrast(contrast);
        lcd.printString("Contrast value", 0, 1);
        sprintf(buffer, "     %.2f", contrast);
        lcd.printString(buffer, 0, 2);
        lcd.refresh();

        ThisThread::sleep_for(1s);
        contrast += 0.05;
    }

    contrast = 0.55;
    lcd.setContrast(contrast);

    lcd.clear();
    lcd.printString("Test Complete", 0, 1);
    lcd.refresh();

    ThisThread::sleep_for(1s);
}

void brightnessTest(){
    lcd.clear();
    lcd.printString(" Begin LCD PWM", 0, 1);
    lcd.printString("     Test     ", 0, 2);
    lcd.refresh();
    ThisThread::sleep_for(1s);

    float brightness = 0.0;

    while(brightness <= 1.0){
        lcd.clear();
        lcd.setBrightness(brightness);
        lcd.printString("  PWM value", 0, 1);
        sprintf(buffer, "     %.2f", brightness);
        lcd.printString(buffer, 0, 2);
        lcd.refresh();

        ThisThread::sleep_for(1s);
        brightness += 0.1;
    }

    brightness = 0.5;
    lcd.setBrightness(brightness);

    lcd.clear();
    lcd.printString("Test Complete", 0, 1);
    lcd.refresh();

    ThisThread::sleep_for(1s);
}

void modeTest(){
    lcd.clear();
    lcd.printString("  Begin Mode ", 0, 1);
    lcd.printString("     Test     ", 0, 2);
    lcd.refresh();
    ThisThread::sleep_for(1s);

    int i = 0;

    while(i < 5){
        lcd.inverseMode();
        lcd.refresh();
        ThisThread::sleep_for(1s);

        lcd.normalMode();
        lcd.refresh();
        ThisThread::sleep_for(1s);
        i++;
    }

    lcd.clear();
    lcd.printString("Test Complete", 0, 1);
    lcd.refresh();

    ThisThread::sleep_for(1s);
}

void printTest(){
    lcd.clear();
    lcd.printString("  Begin Print ", 0, 1);
    lcd.printString("     Test     ", 0, 2);
    lcd.refresh();
    ThisThread::sleep_for(1s);

    lcd.clear();

    //lcd.drawCircle(x, y, radius, fill_type)
    lcd.drawCircle(5, 5, 4, FILL_BLACK);            //solid circle
    lcd.drawCircle(17, 5, 4, FILL_TRANSPARENT);     //outlined circle

    //             origin  finish
    //lcd.drawLine(x0, y0, x1, y1, fill_type)
    lcd.drawLine(0, 20, 84, 20, 1);                 //solid line
    lcd.drawLine(0, 25, 84, 25, 2);                 //dotted line

    //lcd.drawRect(x, y, width, height, fill_type)
    lcd.drawRect(0, 30, 84, 4, FILL_BLACK);         //solid black rectangle
    lcd.drawRect(0, 39, 84, 4, FILL_TRANSPARENT);   //outlined rectangle

    //lcd.drawSprite(x, y, rows, columns, int)
    lcd.drawSprite(30, 5, 4, 9, (int*)Fish);        //draws 'fish' sprite

    //lcd.setPixel(x, y, bool state)
    lcd.setPixel(45, 5, 1);                         //turn pixel at co-ordinate (45,5) 'on'

    //lcd.printChar(char, x, y) - refer to printString notes
    lcd.printChar('C', 50, 1);
    lcd.refresh();

    ThisThread::sleep_for(5s);

    lcd.clear();
    lcd.printString("Test Complete", 0, 1);
    lcd.refresh();

    ThisThread::sleep_for(1s);

}

void powerDown(){
    lcd.clear();
    lcd.printString(" LCD Testing", 0, 1);
    lcd.printString("   Complete    ", 0, 2);
    lcd.refresh();
    ThisThread::sleep_for(1s);

    int i = 5;
    while(i > 0){
        lcd.clear();
        lcd.printString("Shutting down", 0, 1);
        sprintf(buffer, "       %d", i);
        lcd.printString(buffer, 0, 2);
        lcd.refresh();
        ThisThread::sleep_for(1s);
        i--;
    }

    lcd.clear();
    lcd.printString("   Goodbye", 0, 1);
    lcd.refresh();
    ThisThread::sleep_for(1s);

    lcd.clear();
    lcd.turnOff();
}

#endif