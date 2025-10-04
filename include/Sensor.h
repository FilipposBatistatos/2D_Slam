#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include "Maze.h"
#include "Robot.h"

struct RayHit {
    float x;        
    float y;
    float distance; // Distance from robot 
    float angle;    // Angle relative to robot
    bool hit;       // Whether the ray hit
};

class Sensor {
public:
    Sensor(int numRays, float maxRange, float fov);

    std::vector<RayHit> scan(const Robot& robot, const Maze& maze);

    int getNumRays() const { return numRays; }
    float getMaxRange() const { return maxRange; }

private:
    int numRays;
    float maxRange;
    float fov;

    RayHit castRay(float startX, float startY, float angle, const Maze& maze);
};

#endif