#include <iostream>
#include "Maze.h"
#include "Renderer.h"

int main() {
    std::cout << "Starting Maze SLAM Simulator..." << std::endl;
    
    // Configuration
    const float CELL_SIZE = 20.0f;  // Pixels per cell
    
    // Try to load maze from file
    std::string mazeFile = "../maze.txt";
    Maze maze(mazeFile, CELL_SIZE);

    const int WINDOW_WIDTH = maze.getWidth() * CELL_SIZE;
    const int WINDOW_HEIGHT = maze.getHeight() * CELL_SIZE;
    
    // Create renderer
    Renderer renderer(WINDOW_WIDTH, WINDOW_HEIGHT, "2D SLAM");
    
    std::cout << "Maze size: " << maze.getWidth() << "x" << maze.getHeight() << std::endl;
    std::cout << "Window size: " << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << std::endl;
    std::cout << "Press ESC to exit" << std::endl;
    
    // Main game loop
    while (renderer.isOpen()) {
        // Handle events
        renderer.handleEvents();
        
        // Clear window
        renderer.clear();
        
        // Draw maze
        renderer.drawMaze(maze);
        
        // Display
        renderer.display();
    }
    
    std::cout << "Shutting down..." << std::endl;
    return 0;
}