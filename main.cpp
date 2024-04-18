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
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);

// Function definitions
void drawCube(std::vector<Vector2> cubeBottomFacePoints, std::vector<Vector2> cubeTopFacePoints);

int main() {
    // Initialise the LCD
    lcd.init(LPH7366_1);
    lcd.setContrast(0.55);      // Set contrast to 55%
    lcd.setBrightness(0.0);     // Set brightness to 50% (utilises the PWM)

    // Create a camera
    Camera mainCamera({0,0,10});

/*
    std::vector<Vector3> cubeBottomFace = {
        {0,0,0}, {0,0,1}, {1,0,1}, {1,0,0} // Bottom face
    };
    std::vector<Vector3> cubeTopFace = {
        {0,1,0}, {0,1,1}, {1,1,1}, {1,1,0} // Top face
    };
*/

    std::vector<Vector3> cubeBottomFace = {
        {20,0,20}, {20,0,40}, {40,0,40}, {40,0,20} // Bottom face
    };
    std::vector<Vector3> cubeTopFace = {
        {20,20,20}, {20,20,40}, {40,20,40}, {40,20,20} // Top face
    };

    auto cubeBottomFacePoints = mainCamera.projectObjectToPlane(cubeBottomFace);
    auto cubeTopFacePoints = mainCamera.projectObjectToPlane(cubeTopFace);

    auto rotatedBottomFace = mainCamera.rotateGameObject(cubeBottomFace, {1,0,1}, 5);
    auto rotatedTopFace = mainCamera.rotateGameObject(cubeTopFace, {1,0,1}, 5);

    while (true) {
        // TODO Create an interpolation method - SLERP 
        drawCube(cubeBottomFacePoints, cubeTopFacePoints);
        ThisThread::sleep_for(100ms);
        cubeBottomFacePoints.clear();
        cubeTopFacePoints.clear();
        cubeBottomFacePoints = mainCamera.projectObjectToPlane(rotatedBottomFace);
        cubeTopFacePoints = mainCamera.projectObjectToPlane(rotatedTopFace);
        rotatedBottomFace = mainCamera.rotateGameObject(rotatedBottomFace, {1,0,1}, 5);
        rotatedTopFace = mainCamera.rotateGameObject(rotatedTopFace, {1,0,1}, 5);
    }
    
}
// Draw lines between each of these points 
void drawCube(std::vector<Vector2> cubeBottomFacePoints, std::vector<Vector2> cubeTopFacePoints) {
    lcd.clear();
    // Draw the bottom face
     for (size_t i = 0; i < cubeBottomFacePoints.size(); ++i) {
        Vector2 currentVertex = cubeBottomFacePoints[i];
        Vector2 nextVertex = cubeBottomFacePoints[(i + 1) % cubeBottomFacePoints.size()]; // Next vertex (wrap around for last vertex)
        lcd.drawLine(currentVertex.x, currentVertex.y, nextVertex.x, nextVertex.y, 1);

    }
    // Draw the edges
     for (size_t i = 0; i < cubeBottomFacePoints.size(); ++i) {
        Vector2 currentVertex = cubeBottomFacePoints[i];
        Vector2 nextVertex = cubeTopFacePoints[i]; 
        lcd.drawLine(currentVertex.x, currentVertex.y, nextVertex.x, nextVertex.y, 1); 
     }
     // Draw the top face
     for (size_t i = 0; i < cubeTopFacePoints.size(); ++i) {
        Vector2 currentVertex = cubeTopFacePoints[i];
        Vector2 nextVertex = cubeTopFacePoints[(i + 1) % cubeTopFacePoints.size()]; // Next vertex (wrap around for last vertex)
        lcd.drawLine(currentVertex.x, currentVertex.y, nextVertex.x, nextVertex.y, 1);
    }
    // Update the LCD
    lcd.refresh(); 
}
