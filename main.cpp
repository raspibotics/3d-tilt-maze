#include "ThisThread.h"
#include "Vector2.h"
#include "Vector3.h"
#include "mbed.h"
#include <stdio.h>

// Include libraries for LCD
#include "N5110.h"
#include <cstdio>
#include <vector>

// Include libraries for Joystick

// Include Game Engine
#include "Engine.h"

// Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)  
N5110 screen(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);

// Function definitions
void drawCube(std::vector<Vector2> cubeBottomFacePoints, std::vector<Vector2> cubeTopFacePoints);

int main() {
    // Initialise the LCD
    screen.init(LPH7366_1);
    screen.setContrast(1);      // Set contrast to 55%
    screen.setBrightness(0);     // Set brightness to 50% (utilises the PWM)
    // Create a camera
    Camera mainCamera({0,0,10});
    // Create a cube
    Cube test_cube({10,0,10}, 10, 10, 10);
    Cube test_cube2({30,0,10}, 10, 20, 15);
    Cube test_cube3({50,0,10}, 30, 8, 10);
    while (true) {
        screen.clear();
        test_cube.drawCube(mainCamera, screen);
        test_cube2.drawCube(mainCamera, screen);
        test_cube3.drawCube(mainCamera, screen);

        screen.refresh();
        test_cube.rotateCube(3, {4,1,3});
        test_cube2.rotateCube(5, {1,0,1});
        test_cube3.rotateCube(7, {5,0,2});
        ThisThread::sleep_for(100ms);
    }
}
