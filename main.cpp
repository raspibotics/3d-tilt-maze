#include "EngineUtils.h"
#include "ThisThread.h"
#include "mbed.h"

// Include libraries for LCD
#include "N5110.h"
#include <cstdio>

// Include library for Joystick
#include "Joystick.h"

// Include Game Engine
#include "Engine.h"
#include <vector>


void boundary(int x, int y);

// Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)  
N5110 screen(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);
//                  y     x
Joystick joystick(PC_0, PC_1);  // Attach and create joystick object
DigitalIn fireMissile(PA_8);


int main() {

    initialiseEngine(); // Does nothing atm 

    // Initialise the LCD
    screen.init(LPH7366_1);
    screen.setContrast(1);      // Set contrast to 55%
    screen.setBrightness(0);     // Set brightness to 50% (utilises the PWM)

    // Initialise the Joystick
    joystick.init();
    fireMissile.mode(PullUp);
    
    // Create a camera - TODO fix camera projection, does not take into account camera Z position (Use for perspective projection)
    Camera mainCamera({0,0,10});
    
    // Create cubes
    Cube test_cube({10,0,10}, 10, 10, 10);
    Circle cube_core(Vector3ToPoint2D(test_cube.getPosition()), 2);


    Cube test_cube2({30,0,10}, 10, 20, 15);
    Circle cube2_core(Vector3ToPoint2D(test_cube.getPosition()), 4);

    Cube test_cube3({63,0,10}, 30, 8, 10);
    Circle cube3_core(Vector3ToPoint2D(test_cube.getPosition()), 3);

    // Create the player
    Player spaceship({60, 38});
    //spaceship.rotatePlayer(95);

    int timer = 0; 
    bool fired = false; 
    Point2D missilePos(0,0);

    Circle missile(missilePos, 2);

    while (true) {
        screen.clear();

        screen.printString("Shots:", 0, 1);

        // Draws screen border
        screen.drawRect(0,0,84,48,FILL_TRANSPARENT);   

        Vector2 player_pos = spaceship.getPosition();

        // Continue motion of projectile if fired
        if (fired) {
            missilePos.y-=2;
            if (missilePos.y <= 2){
                fired = false;
            } 
            if (fired){
                missile.centre = missilePos;
                missile.draw(screen);
            }
        }

        // Joystick handling for movement
        if(joystick.get_direction() == E){
            player_pos.x +=3;
            spaceship.setPosition(player_pos);
            printf(" Direction: E\n");

        }else if(joystick.get_direction() == W){
            player_pos.x -=3;
            spaceship.setPosition(player_pos);
            printf(" Direction: W\n");
        }
         if (!fireMissile && !fired) {
            fired = true; 
            missilePos = Vector2ToPoint2D(player_pos);
            missile.centre = missilePos;
            missile.draw(screen);
            printf("Fire missile!\n");
        }

        // Draw player
        spaceship.drawPlayer(screen);

     
        // If cube core has collided with missile, stop rendering cube
        if (fired && cube_core.isCollidingWith(missile)) { test_cube.destroyCube(true); }
        if (!test_cube.isDestroyed()){
            cube_core.centre = Vector3ToPoint2D(test_cube.getPosition());
            cube_core.draw(screen);
            test_cube.drawCube(mainCamera, screen);
        }
        if (fired && cube2_core.isCollidingWith(missile)) { test_cube2.destroyCube(true); }
        if (!test_cube2.isDestroyed()){
            cube2_core.centre = Vector3ToPoint2D(test_cube2.getPosition());
            cube2_core.draw(screen);
            test_cube2.drawCube(mainCamera, screen);
        }
        if (fired && cube3_core.isCollidingWith(missile)) { test_cube3.destroyCube(true); }
        if (!test_cube3.isDestroyed()){
            cube3_core.centre = Vector3ToPoint2D(test_cube3.getPosition());
            cube3_core.draw(screen);
            test_cube3.drawCube(mainCamera, screen);
        }


        screen.refresh();

        // Spin the cubes around a weird axis to make them appear floating
        test_cube.rotateCube(3, {4,1,3});
        test_cube2.rotateCube(5, {1,0,1});
        test_cube3.rotateCube(7, {5,0,2});
 
        ThisThread::sleep_for(100ms);
    }
}
