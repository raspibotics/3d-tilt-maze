#include "Vector2.h"
#include "mbed.h"
#include <iostream>

// Include libraries for LCD
#include "N5110.h"
#include <cstdio>
#include <vector>

// Include libraries for Joystick

// Include Game Engine
#include "Engine.h"

// Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)  
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);

// Function definitions
void renderScene(std::vector<Vector2> vertices);

int main() {
    // Initialise the LCD
    lcd.init(LPH7366_1);
    lcd.setContrast(0.55);      // Set contrast to 55%
    lcd.setBrightness(0.5);     // Set brightness to 50% (utilises the PWM)

    // Create a camera
    Camera mainCamera({0,0,10});

    // Define a unit cube in gray code
    std::vector<Vector3> cube = {
        {0,0,0}, {0,0,1}, {0,1,1}, {0,1,0}, 
        {1,1,0}, {1,1,1}, {1,0,1}, {1,0,0}
    };

    // Scale the cube
    for (Vector3 vertex : cube) {
        vertex*=50;
    }

    // TODO Create an interpolation method - SLERP 
    std::vector<Vector2> projected_points = mainCamera.projectObjectToPlane(cube);

    for (auto point : projected_points) {
        std::cout << "point" << "\n";
        point.print();
    }

    renderScene(projected_points);
}

// Draw lines between each of these points 
void renderScene(std::vector<Vector2> vertices) {
    // Iterate through the vertices
    for (size_t i = 0; i < vertices.size() - 1; i++) {
        // Get the current and next vertices
        Vector2 currentVertex = vertices[i];
        Vector2 nextVertex = vertices[i + 1];
        // Draw a line between current and next vertices
        lcd.drawLine(currentVertex.x, currentVertex.y, nextVertex.x, nextVertex.y, 1);
    }
}
