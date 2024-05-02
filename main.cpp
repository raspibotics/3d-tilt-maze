#include "ThisThread.h"
#include "mbed.h"

// Include libraries for LCD
#include "N5110.h"

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
    Cube test_cube2({30,0,10}, 10, 20, 15);
    Cube test_cube3({50,0,10}, 30, 8, 10);

    // Create the player
    Player spaceship({60, 38});
    //spaceship.rotatePlayer(95);

    int timer = 0; 
    bool fired = false; 
    Vector2 missilePos;

    while (true) {
        screen.clear();

        // Draws screen border
        screen.drawRect(0,0,84,48,FILL_TRANSPARENT);   

        Vector2 player_pos = spaceship.getPosition();

        // Continue motion of projectile if fired
        if (fired) {
            missilePos.y-=2;
            if (missilePos.y <= 0){
                fired = false;
            } 
            if (fired){
                screen.drawCircle(missilePos.x, missilePos.y, 2, FILL_BLACK);
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
            screen.drawCircle(player_pos.x, player_pos.y, 2, FILL_BLACK);
            fired = true; 
            missilePos = player_pos;
            printf("Fire missile!\n");
        }

        // Draw player
        spaceship.drawPlayer(screen);

       

        test_cube.drawCube(mainCamera, screen);
        Point2D centre = mainCamera.Vector3ToPoint2D(test_cube.getPosition());
        screen.drawCircle(centre.x, centre.y, 2, FILL_BLACK);

        test_cube2.drawCube(mainCamera, screen);
        // At this scale a sphere is accurately represented by a 2D circle, simplfying collisions with the cube 'cores' 
        centre = mainCamera.Vector3ToPoint2D(test_cube2.getPosition());
        screen.drawCircle(centre.x, centre.y, 4, FILL_BLACK);

        test_cube3.drawCube(mainCamera, screen);
        centre = mainCamera.Vector3ToPoint2D(test_cube3.getPosition());
        screen.drawCircle(centre.x, centre.y, 3, FILL_BLACK);

        screen.refresh();
        test_cube.rotateCube(3, {4,1,3});
        test_cube2.rotateCube(5, {1,0,1});
        test_cube3.rotateCube(7, {5,0,2});
 
        ThisThread::sleep_for(100ms);
    }
}
