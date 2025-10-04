#include <cmath>

#include "Renderer.h"

Renderer::Renderer(int windowWidth, int windowHeight, const std::string& title)
    : windowWidth(windowWidth), windowHeight(windowHeight) {
    
    window.create(sf::VideoMode(windowWidth, windowHeight), title);
    window.setFramerateLimit(60);
}

Renderer::~Renderer() {
    if (window.isOpen()) {
        window.close();
    }
}

bool Renderer::isOpen() const {
    return window.isOpen();
}

void Renderer::clear() {
    window.clear(sf::Color(30, 30, 30));  // Dark gray background
}

void Renderer::display() {
    window.display();
}

void Renderer::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        // Handle escape key to close window
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
    }
}

void Renderer::drawMaze(const Maze& maze) {
    sf::RectangleShape cell(sf::Vector2f(maze.getCellSize(), maze.getCellSize()));
    
    for (int y = 0; y < maze.getHeight(); y++) {
        for (int x = 0; x < maze.getWidth(); x++) {
            if (maze.isWall(x, y)) {
                cell.setPosition(x * maze.getCellSize(), y * maze.getCellSize());
                cell.setFillColor(sf::Color(80, 80, 100));  // Blue-gray walls
                cell.setOutlineColor(sf::Color(60, 60, 80));
                cell.setOutlineThickness(-1.0f);
                window.draw(cell);
            }
        }
    }
}

void Renderer::drawRobot(const Robot& robot) {
    // Draw robot as a triangle pointing in the direction of movement
    sf::CircleShape triangle(robot.getRadius(), 3);
    
    // Position the triangle
    triangle.setPosition(robot.getX(), robot.getY());
    triangle.setOrigin(robot.getRadius(), robot.getRadius());
    
    // Rotate to face the correct direction
    // Convert radians to degrees and add 90 to align properly
    triangle.setRotation(robot.getTheta() * 180.0f / (M_PI) + 90.0f);
    
    // Color the robot
    triangle.setFillColor(sf::Color(50, 150, 255));  
    triangle.setOutlineColor(sf::Color(50, 150, 255));  
    triangle.setOutlineThickness(2.0f);
    
    window.draw(triangle);
}