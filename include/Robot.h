#ifndef ROBOT_H
#define ROBOT_H

#include "Maze.h"

class Robot {
public:
    Robot(float x, float y, float theta);
    
    // Movement
    void moveForward(float distance, const Maze& maze);
    void moveBackward(float distance, const Maze& maze);
    void rotateLeft(float angle);
    void rotateRight(float angle);
    
    // Getters for drawing
    float getX() const { return x; }
    float getY() const { return y; }
    float getTheta() const { return theta; }
    float getRadius() const { return radius; }
    
    // Update based on keyboard input
    void update(float deltaTime, const Maze& maze);
    
private:
    float x;        // X position in world coordinates (pixels)
    float y;        // Y position in world coordinates (pixels)
    float theta;    // Orientation in radians 0 is to the right
    float radius;   // Robot interpreted as a circle for simplicity
    
    // Motion parameters
    float speed;           // Linear speed (pixels per second)
    float rotationSpeed;   // Angular speed (radians per second)
};

#endif