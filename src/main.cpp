#include <iostream>
#include "Maze.h"
#include "Renderer.h"

int main() {
    std::cout << "Starting Maze SLAM Simulator..." << std::endl;
    
    // Configuration
    const int MAZE_WIDTH = 40;   // Grid cells
    const int MAZE_HEIGHT = 30;  // Grid cells
    const float CELL_SIZE = 20.0f;  // Pixels per cell
    
    const int WINDOW_WIDTH = MAZE_WIDTH * CELL_SIZE;
    const int WINDOW_HEIGHT = MAZE_HEIGHT * CELL_SIZE;
    
    // Create maze and renderer
    Maze maze(MAZE_WIDTH, MAZE_HEIGHT, CELL_SIZE);
    Renderer renderer(WINDOW_WIDTH, WINDOW_HEIGHT, "2D SLAM - Phase 1: Maze");
    
    std::cout << "Maze size: " << MAZE_WIDTH << "x" << MAZE_HEIGHT << std::endl;
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