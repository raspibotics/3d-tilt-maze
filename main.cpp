#include "EngineUtils.h"
#include "ThisThread.h"
#include "Thread.h"
#include "mbed.h"

// Include libraries for LCD
#include "N5110.h"
#include <cstdio>

// Include library for Joystick
#include "Joystick.h"

// Include Game Engine
#include "Engine.h"
#include <cstdlib>
#include <vector>

void GameOver();
void PlayLevel();
void level2();
void level3();
void Win();

void startMenu();

 const int SPRITE[23][56]= {
	{ 0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0 },
	{ 0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0 },
	{ 0,0,0,0,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0 },
	{ 0,0,0,0,0,1,0,0,1,1,0,0,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0 },
	{ 0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,0,1,0,1,1,1,1,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,1,1,1,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,1,1,1,0,1,0,1,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,1,0,0,1,1,0,1,1,0,1,0,0,0,1,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,1,0,0,1,1,1,0,1,0,1,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,1,1,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,1,1,0,1,0,1,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,1,1,0,0,0,0,1,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0 },
	{ 1,1,0,0,0,1,0,0,0,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,0,0,1,1,0,1,1,1,0,0,1,1,0,0,1,0,0,0,0,0,0 },
	{ 0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,1,0,0,1,0,0,0,1,1,1,0,1,0,0,1,1,0,0,1,1,0,0,0,0,0 },
	{ 0,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1 },
	{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};

// Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)  
N5110 screen(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);
//                  y     x
Joystick joystick(PC_0, PC_1);  // Attach and create joystick object
DigitalIn fireMissile(PA_8);

/* ---------------------
GAME OBJECTS FOR LEVELS
------------------------ */
Camera mainCamera({0,0,10});
char buffer[14] = {0};
// Create cubes
Cube test_cube({10,0,10}, 10, 10, 10);
Circle cube_core(Vector3ToPoint2D(test_cube.getPosition()), 2);
int test_cube_speed = 3;
Vector3 axis_1 = {4,1,3};

Cube test_cube2({30,0,10}, 10, 20, 15);
Circle cube2_core(Vector3ToPoint2D(test_cube.getPosition()), 4);
int test_cube2_speed = 5;
Vector3 axis_2 = {1,0,1};

Cube test_cube3({63,15,20}, 25, 8, 10);
Circle cube3_core(Vector3ToPoint2D(test_cube.getPosition()), 3);
int test_cube3_speed = 3;
Vector3 axis_3 = {5,0,2};

// Create the player
Player spaceship({60, 38});

int shots_left = 2; 

Circle missile({0,0}, 2);

int current_level = 1; 

// Initialise everything in int main()
int main() {

    initialiseEngine(); // Does nothing atm 

    // Initialise the LCD
    screen.init(LPH7366_1);
    screen.setContrast(1);      // Set contrast to 55%
    screen.setBrightness(0);     // Set brightness to 50% (utilises the PWM)

    // Initialise the Joystick
    joystick.init();
    fireMissile.mode(PullUp);
    

    startMenu();
    
}

void startMenu() {
    // Create a main menu here for the game
   
    screen.clear();
    screen.drawSprite(10, 0, 23, 56, (int *)SPRITE);
    screen.printString("Press to Play!", 0, 4);
    screen.refresh();
    ThisThread::sleep_for(1000ms);
    while (fireMissile) {}
    PlayLevel();

}
void PlayLevel() {
    // Create a camera - TODO fix camera projection, does not take into account camera Z position (Use for perspective projection)
    //spaceship.rotatePlayer(95);
    ThisThread::sleep_for(500ms);
    bool fired = false; 
    Point2D missilePos(0,0);

    while (true) {
        screen.clear();
        sprintf(buffer, "Shots:%i", shots_left);
        screen.printString(buffer, 40, 0);

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
            shots_left-=1;
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

        // End Game if there are no shots left and all junk has not been destroyed
        if(shots_left <=0 && !fired && (!test_cube.isDestroyed() || !test_cube2.isDestroyed() || !test_cube3.isDestroyed())){
            GameOver();
        }
        if (test_cube.isDestroyed() && test_cube2.isDestroyed() && test_cube3.isDestroyed()) {
            switch (current_level) {
                case 1:
                    level2();
                case 2:
                    level3();
                case 3:
                    Win();
            }
           
        }

        screen.refresh();

        // Spin the cubes around a weird axis to make them appear floating
        test_cube.rotateCube(test_cube_speed, axis_1);
        test_cube2.rotateCube(test_cube2_speed, axis_2);
        test_cube3.rotateCube(test_cube3_speed, axis_3);
 
        ThisThread::sleep_for(100ms);
    }
}



void level2(){
    current_level = 2; 
    screen.clear();
    // Draws screen border
    screen.drawRect(0,0,84,48,FILL_TRANSPARENT); 
    screen.printString("LEVEL 2", 20, 3);
    screen.refresh();
    shots_left = 1; 

    // CONFIGURE CUBE 1
    test_cube.destroyCube(false); // reset cube
    int test_cube_speed = 10; // faster movement
    Vector3 axis_1 = {10,5,6};
    test_cube.setPosition({30, 10, 20});
    test_cube.setWidthDepthHeight(20, 15, 12);
    cube_core.centre = Vector3ToPoint2D(test_cube.getPosition());
    cube_core.radius = 1; // smaller target
    missile.radius = 1; // smaller projectile

    ThisThread::sleep_for(3000ms);

    PlayLevel();

}

void level3() {
    current_level = 3; 
    screen.clear();
    // Draws screen border
    screen.drawRect(0,0,84,48,FILL_TRANSPARENT); 
    screen.printString("LEVEL 3", 20, 3);
    screen.refresh();
    shots_left = 3; 

    // CONFIGURE CUBE 1
    test_cube.destroyCube(false); 
    int test_cube_speed = 15; 
    Vector3 axis_1 = {1,5,6};
    test_cube.setPosition({40, 5, 10});
    test_cube.setWidthDepthHeight(10, 15, 12);
    cube_core.centre = Vector3ToPoint2D(test_cube.getPosition());
    cube_core.radius = 3; 
    missile.radius = 1; 

     // CONFIGURE CUBE 2
    test_cube2.destroyCube(false); // reset cube
    int test_cube2_speed = 10; 
    Vector3 axis_2 = {2,3,1};
    test_cube.setPosition({5, 30, 20});
    test_cube.setWidthDepthHeight(15, 5, 25);
    cube_core.centre = Vector3ToPoint2D(test_cube.getPosition());
    cube_core.radius = 2; // smaller target

    test_cube3.destroyCube(false); // reset cube
    int test_cube3_speed = 10; 
    Vector3 axis_3 = {1,3,4};
    test_cube.setPosition({15, 10, 20});
    test_cube.setWidthDepthHeight(20, 5, 15);
    cube_core.centre = Vector3ToPoint2D(test_cube.getPosition());
    cube_core.radius = 1; // smaller target


    ThisThread::sleep_for(3000ms);

    PlayLevel();
}

void GameOver() { 
    screen.clear();
    // Draws screen border
    screen.drawRect(0,0,84,48,FILL_TRANSPARENT); 
    screen.printString("GAME OVER", 15, 3);
    screen.refresh();
    ThisThread::sleep_for(2000ms);
    exit(0);
}

void Win() { 
    screen.clear();
    // Draws screen border
    screen.drawRect(0,0,84,48,FILL_TRANSPARENT); 
    screen.printString("YOU WIN!!", 15, 3);
    screen.refresh();
    ThisThread::sleep_for(2000ms);
    exit(0);
}