#include "Sensor.h"
#include <cmath>

Sensor::Sensor(int numRays, float maxRange, float fov)
    : numRays(numRays), maxRange(maxRange), fov(fov) {
}

std::vector<RayHit> Sensor::scan(const Robot& robot, const Maze& maze) {
    std::vector<RayHit> hits;
    hits.reserve(numRays);

    float startAngle = robot.getTheta() - fov / 2.0f;
    float angleStep = fov / (numRays - 1);

    for (int i = 0; i < numRays; i++){
        float angle = startAngle + i * angleStep;
        RayHit hit = castRay(robot.getX(), robot.getY(), angle, maze);
        hit.angle = angle;
        hits.push_back(hit);
    }

    return hits;
}

RayHit Sensor::castRay(float startX, float startY, float angle, const Maze& maze) {
    RayHit hit;
    hit.hit = false;
    hit.distance = maxRange;

    float dx = std::cos(angle);
    float dy = std::sin(angle);

    float stepSize = 0.5f;
    float distance = 0.0f;

    while (distance < maxRange) {
        distance += stepSize;

        float x = startX + dx * distance;
        float y = startY + dy * distance;

        int gridX = static_cast<int>(x / maze.getCellSize());
        int gridY = static_cast<int>(y / maze.getCellSize());

        if (maze.isWall(gridX, gridY)) {
            hit.hit = true;
            hit.x = x;
            hit.y = y;
            hit.distance = distance;
            return hit;
        }
    }

    hit.x = startX + dx * maxRange;
    hit.y = startY + dy * maxRange;
    hit.distance = maxRange;

    return hit;
}