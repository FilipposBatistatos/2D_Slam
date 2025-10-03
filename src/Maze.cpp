#include "Maze.h"
#include <cmath>

Maze::Maze(int width, int height, float cellSize) 
    : width(width), height(height), cellSize(cellSize) {
    
    // Initialize grid with all free space
    grid.resize(height, std::vector<bool>(width, false));
    
    // Create a simple maze
    initialiseMaze();
}

void Maze::initialiseMaze() {
    // Create border walls
    for (int y = 0; y < height; y++) {
        grid[y][0] = true;           // Left wall
        grid[y][width - 1] = true;   // Right wall
    }
    for (int x = 0; x < width; x++) {
        grid[0][x] = true;           // Top wall
        grid[height - 1][x] = true;  // Bottom wall
    }
    
    // Add some internal walls to make it interesting
    // Vertical wall
    for (int y = 5; y < 15; y++) {
        grid[y][10] = true;
    }
    
    // Horizontal wall
    for (int x = 15; x < 25; x++) {
        grid[10][x] = true;
    }
    
    // Create a room
    for (int x = 20; x < 28; x++) {
        grid[5][x] = true;
        grid[15][x] = true;
    }
    for (int y = 5; y < 16; y++) {
        grid[y][20] = true;
        grid[y][28] = true;
    }
    // Add door to room
    grid[10][20] = false;
    
    // Add some scattered obstacles
    for (int y = 18; y < 21; y++) {
        for (int x = 5; x < 8; x++) {
            grid[y][x] = true;
        }
    }
}

bool Maze::isWall(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return true;  // Out of bounds is treated as wall
    }
    return grid[y][x];
}

void Maze::setCell(int x, int y, bool isWall) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        grid[y][x] = isWall;
    }
}

bool Maze::checkCollision(float worldX, float worldY, float radius) const {
    // Convert world coordinates to grid coordinates
    int gridX = static_cast<int>(worldX / cellSize);
    int gridY = static_cast<int>(worldY / cellSize);
    
    // Check the cell and surrounding cells
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int checkX = gridX + dx;
            int checkY = gridY + dy;
            
            if (isWall(checkX, checkY)) {
                // Calculate distance from point to cell center
                float cellCenterX = (checkX + 0.5f) * cellSize;
                float cellCenterY = (checkY + 0.5f) * cellSize;
                
                float distX = worldX - cellCenterX;
                float distY = worldY - cellCenterY;
                
                // Check if circle overlaps with the cell
                float halfCell = cellSize * 0.5f;
                float closestX = cellCenterX + std::max(-halfCell, std::min(halfCell, distX));
                float closestY = cellCenterY + std::max(-halfCell, std::min(halfCell, distY));
                
                float distance = std::sqrt((worldX - closestX) * (worldX - closestX) + 
                                         (worldY - closestY) * (worldY - closestY));
                
                if (distance < radius) {
                    return true;
                }
            }
        }
    }
    
    return false;
}