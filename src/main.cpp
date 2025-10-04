#include <iostream>
#include "Maze.h"
#include "Robot.h"
#include "Renderer.h"

int main() {
    std::cout << "Starting Maze SLAM Simulator..." << std::endl;
    
    const float CELL_SIZE = 20.0f;  
    
    // Try to load maze from file
    std::string mazeFile = "../maze.txt";
    Maze maze(mazeFile, CELL_SIZE);
    
    const int WINDOW_WIDTH = maze.getWidth() * CELL_SIZE;
    const int WINDOW_HEIGHT = maze.getHeight() * CELL_SIZE;
    
    // Create renderer
    Renderer renderer(WINDOW_WIDTH, WINDOW_HEIGHT, "2D SLAM");
    
    // Place agent
    float startX = 100.0f;  
    float startY = 100.0f; 
    float startTheta = 0.0f;  // 0 is towards the right
    Robot robot(startX, startY, startTheta);
    
    // Clock for smooth movement
    sf::Clock clock;
    
    std::cout << "Maze size: " << maze.getWidth() << "x" << maze.getHeight() << std::endl;
    std::cout << "Window size: " << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  Arrow Keys - Move robot" << std::endl;
    std::cout << "  ESC - Exit" << std::endl;
    
    // Main game loop
    while (renderer.isOpen()) {
        // Calculate delta time
        float deltaTime = clock.restart().asSeconds();
        
        // Handle events - kill window
        renderer.handleEvents();
        
        // Keyboard input
        // Also takes maze to check for collisions
        robot.update(deltaTime, maze);
        
        // Draw loop
        renderer.clear();
        renderer.drawMaze(maze);
        renderer.drawRobot(robot);
        renderer.display();
    }
    
    std::cout << "Shutting down..." << std::endl;
    return 0;
}