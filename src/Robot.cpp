#include "Robot.h"
#include <cmath>
#include <SFML/Window/Keyboard.hpp>

Robot::Robot(float x, float y, float theta)
    : x(x), y(y), theta(theta), radius(8.0f), speed(100.0f), rotationSpeed(3.0f) {
}

void Robot::moveForward(float distance, const Maze& maze) {
    float newX = x + distance * std::cos(theta);
    float newY = y + distance * std::sin(theta);
    
    // Check collision before moving
    if (!maze.checkCollision(newX, newY, radius)) {
        x = newX;
        y = newY;
    }
}

void Robot::moveBackward(float distance, const Maze& maze) {
    moveForward(-distance, maze);
}

void Robot::rotateLeft(float angle) {
    theta -= angle;
    
    // Normalize angle
    while (theta < -M_PI) theta += 2 * M_PI;
    while (theta > M_PI) theta -= 2 * M_PI;
}

void Robot::rotateRight(float angle) {
    rotateLeft(-angle);
}

void Robot::update(float deltaTime, const Maze& maze) {
    // Check keyboard input and update robot position
    
    // Forward/Backward movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        moveForward(speed * deltaTime, maze);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        moveBackward(speed * deltaTime, maze);
    }
    
    // Rotation
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        rotateLeft(rotationSpeed * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        rotateRight(rotationSpeed * deltaTime);
    }
}