#include "SLAM.h"
#include <cmath>

SLAM::SLAM(int gridWidth, int gridHeight, float cellSize, int numRays, float maxRange)
    : map(gridWidth, gridHeight, cellSize),
    sensor(numRays, maxRange, 2 * M_PI), // 360 view
    logOddsOccupied(0.7f),
    logOddsFree(-0.4f) {

}

void SLAM::update(const Robot& robot, const Maze& maze) {
    std::vector<RayHit> hits = sensor.scan(robot, maze);

    updateMap(robot, hits);

    PathPoint point;
    point.x = robot.getX();
    point.y = robot.getY();

    // Check for duplicates
    if (path.empty() || 
        std::abs(point.x - path.back().x) > 1.0f ||
        std::abs(point.y - path.back().y) > 1.0f) {
        path.push_back(point);
    }
}

void SLAM::updateMap(const Robot& robot, const std::vector<RayHit>& hits) {
    int robotGridX = static_cast<int>(robot.getX() / map.getCellSize());
    int robotGridY = static_cast<int>(robot.getY() / map.getCellSize());

    for (const auto& hit : hits) {
        if (!hit.hit) continue; // Skip over rays that did not hit

        int hitGridX = static_cast<int>(hit.x / map.getCellSize());
        int hitGridY = static_cast<int>(hit.y / map.getCellSize());

        std::vector<std::pair<int, int>> cells = getLineCells(
            robotGridX, robotGridY, hitGridX, hitGridY
        );

        for (size_t i = 0; i < cells.size(); i++) {
            int x = cells[i].first;
            int y = cells[i].second;

            if (i == cells.size() - 1) {
                map.updateCell(x, y, logOddsOccupied);
            } else {
                map.updateCell(x, y, logOddsFree);
            }
        }
    }
}

std::vector<std::pair<int, int>> SLAM::getLineCells(int x0, int y0, int x1, int y1) {
    std::vector<std::pair<int, int>> cells;

    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    int x = x0;
    int y = y0;

    while (true){
        cells.push_back({x, y});

        if (x == x1 && y == y1) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }

    return cells;
}