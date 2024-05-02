#include "ThisThread.h"
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

int main() {

    initialiseEngine(); // Does nothing atm 

    // Initialise the LCD
    screen.init(LPH7366_1);
    screen.setContrast(1);      // Set contrast to 55%
    screen.setBrightness(0);     // Set brightness to 50% (utilises the PWM)
    // Create a camera - TODO fix camera projection, does not take into account camera Z position (Use for perspective projection)
    Camera mainCamera({0,0,10});
    // Create a cube
    Cube test_cube({10,0,10}, 10, 10, 10);
    Cube test_cube2({30,0,10}, 10, 20, 15);
    Cube test_cube3({50,0,10}, 30, 8, 10);

    // Create the player
    Player spaceship({60, 20});
    spaceship.rotatePlayer(95);

    while (true) {
  
        screen.clear();

        spaceship.drawPlayer(screen);

        test_cube.drawCube(mainCamera, screen);

        test_cube2.drawCube(mainCamera, screen);
        // At this scale a sphere is accurately represented by a 2D circle, simplfying collisions with the cube 'cores' 
        Point2D centre = mainCamera.Vector3ToPoint2D(test_cube2.getPosition());
        screen.drawCircle(centre.x, centre.y, 4, FILL_BLACK);

        test_cube3.drawCube(mainCamera, screen);

        screen.refresh();
        test_cube.rotateCube(3, {4,1,3});
        test_cube2.rotateCube(5, {1,0,1});
        test_cube3.rotateCube(7, {5,0,2});
 
        ThisThread::sleep_for(100ms);
    }
}
