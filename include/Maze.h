#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>

class Maze {
public:
    Maze(int width, int height, float cellSize);
    Maze(const std::string& filename, float cellSize);

    bool isWall(int x, int y) const;

    void setCell(int x, int y, bool isWall);

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    float getCellSize() const { return cellSize; }

    bool checkCollision(float worldX, float worldY, float radius) const;

private:
    int width;
    int height;
    float cellSize;
    std::vector<std::vector<bool>> grid;

    void initialiseMaze();
    bool loadFromFile(const std::string& filename);
};

#endif