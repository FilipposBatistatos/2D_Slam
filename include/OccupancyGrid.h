#ifndef OCCUPANCY_GRID_H
#define OCCUPANCY_GRID_H

#include <vector>

class OccupancyGrid {
public:
    OccupancyGrid(int width, int height, float cellSize);

    // Update cell probabilistically - log-odds
    void updateCell(int x, int y, float logOddsUpdate);

    float getProbability(int x, int y) const;

    float getLogOdds(int x, int y) const;

    int getWidth() const { return width; }
    int getHeight() const {return height; }
    float getCellSize() const { return cellSize; }

    bool isValid(int x, int y) const;

private:
    int width;
    int height;
    float cellSize;
    std::vector<std::vector<float>> logOdds;

    float probToLogOdds(float prob) const;
    float logOddsToProb(float logOdds) const;

};

#endif