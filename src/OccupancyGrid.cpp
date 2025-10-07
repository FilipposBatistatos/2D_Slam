#include "OccupancyGrid.h"
#include <cmath>
#include <algorithm>

OccupancyGrid::OccupancyGrid(int width, int height, float cellSize)
    : width(width), height(height), cellSize(cellSize){
        // Initialise grid with log odds
        logOdds.resize(height, std::vector<float>(width, 0.0f));
}

void OccupancyGrid::updateCell(int x, int y, float logOddsUpdate) {
    if (!isValid(x, y)) return;

    logOdds[y][x] += logOddsUpdate;

    logOdds[y][x] = std::max(-10.0f, std::min(10.0f, logOdds[y][x]));
}

float OccupancyGrid::getProbability(int x, int y) const {
    if (!isValid(x, y)) return 0.5f;

    return logOddsToProb(logOdds[y][x]);
}

float OccupancyGrid::getLogOdds(int x, int y) const {
    if (!isValid(x ,y)) return 0.0f;

    return logOdds[y][x];
}

bool OccupancyGrid::isValid(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

float OccupancyGrid::probToLogOdds(float prob) const {
    // Avoid division by zero
    prob = std::max(0.001f, std::min(0.999f, prob));
    return std::log(prob / (1.0f - prob));
}

float OccupancyGrid::logOddsToProb(float logOdds) const {
    return 1.0f / (1.0f + std::exp(-logOdds));
}