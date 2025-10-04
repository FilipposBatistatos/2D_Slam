#ifndef SLAM_H
#define SLAM_H

#include <vector>
#include "OccupancyGrid.h"
#include "Sensor.h"
#include "Robot.h"
#include "Maze.h"

struct PathPoint {
    float x;
    float y;
};

class SLAM {
public:
    SLAM(int gridWidth, int gridHeight, float cellSize, int numRays, float maxRange);

    // Update SLAM with new sensor data
    void update(const Robot& robot, const Maze& maze);

    const OccupancyGrid& getMap() const { return map; }
    const std::vector<PathPoint>& getPath() const { return path; }

private:
    OccupancyGrid map;
    Sensor sensor;
    std::vector<PathPoint> path;

    float logOddsOccupied;
    float logOddsFree;

    void updateMap(const Robot& robot, const std::vector<RayHit>& hits);

    std::vector<std::pair<int, int>> getLineCells(int x0, int y0, int x1, int y1);
};

#endif