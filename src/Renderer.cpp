#include <cmath>

#include "Renderer.h"

Renderer::Renderer(int windowWidth, int windowHeight, const std::string& title)
    : windowWidth(windowWidth), windowHeight(windowHeight) {
    
    mainWindow.create(sf::VideoMode(windowWidth, windowHeight), title);
    mainWindow.setPosition(sf::Vector2i(50,50));
    mainWindow.setFramerateLimit(60);

    slamWindow.create(sf::VideoMode(windowWidth, windowHeight), "SLAM map - " + title);
    slamWindow.setPosition(sf::Vector2i(windowWidth + 100, 50));
    slamWindow.setFramerateLimit(60);
}

Renderer::~Renderer() {
    if (mainWindow.isOpen()) {
        mainWindow.close();
    }
    if (slamWindow.isOpen()) {
        slamWindow.close();
    }
}

bool Renderer::isOpen() const {
    return mainWindow.isOpen() || slamWindow.isOpen();
}

void Renderer::clear() {
    mainWindow.clear(sf::Color(30, 30, 30));  // Dark gray background
    slamWindow.clear(sf::Color(20, 20, 20));
}

void Renderer::display() {
    mainWindow.display();
    slamWindow.display();
}

void Renderer::handleEvents() {
    sf::Event event;

    // TODO: can we check either?
    while (mainWindow.pollEvent(event) || slamWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mainWindow.close();
            slamWindow.close();
        }
        
        // Handle escape key to close mainWindow
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                mainWindow.close();
                slamWindow.close();
            }
        }
    }
}

void Renderer::activateMainWindow() {
    mainWindow.setActive(true);
}

void Renderer::activateSLAMWindow() {
    slamWindow.setActive(true);
}

void Renderer::drawMaze(const Maze& maze) {
    sf::RectangleShape cell(sf::Vector2f(maze.getCellSize(), maze.getCellSize()));
    
    for (int y = 0; y < maze.getHeight(); y++) {
        for (int x = 0; x < maze.getWidth(); x++) {
            if (maze.isWall(x, y)) {
                cell.setPosition(x * maze.getCellSize(), y * maze.getCellSize());
                cell.setFillColor(sf::Color(80, 80, 100));  // Blue-gray walls
                cell.setOutlineColor(sf::Color(60, 60, 80));
                cell.setOutlineThickness(-1.0f);
                mainWindow.draw(cell);
            }
        }
    }
}

void Renderer::drawRobot(const Robot& robot) {
    // Draw robot as a triangle pointing in the direction of movement
    sf::CircleShape triangle(robot.getRadius(), 3);
    
    // Position the triangle
    triangle.setPosition(robot.getX(), robot.getY());
    triangle.setOrigin(robot.getRadius(), robot.getRadius());
    
    // Rotate to face the correct direction
    // Convert radians to degrees and add 90 to align properly
    triangle.setRotation(robot.getTheta() * 180.0f / (M_PI) + 90.0f);
    
    // Color the robot
    triangle.setFillColor(sf::Color(50, 150, 255));  
    triangle.setOutlineColor(sf::Color(50, 150, 255));  
    triangle.setOutlineThickness(2.0f);
    
    mainWindow.draw(triangle);
}

void Renderer::drawSensorRays(const Robot& robot, const std::vector<RayHit>& hits) {
    for (const auto& hit : hits) {
        if (!hit.hit) continue;

        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(robot.getX(), robot.getY()), sf::Color(255, 255, 0, 30)),
            sf::Vertex(sf::Vector2f(hit.x, hit.y), sf::Color(255, 255, 0, 30))
        };
        mainWindow.draw(line, 2, sf::Lines);

        // Draw hit point
        sf::CircleShape hitPoint(2.0f);
        hitPoint.setPosition(hit.x, hit.y);
        hitPoint.setOrigin(2.0f, 2.0f);
        hitPoint.setFillColor(sf::Color(255, 0, 0, 150));
        mainWindow.draw(hitPoint);
    }
}

void Renderer::drawOccupancyGrid(const OccupancyGrid& grid) {
    sf::RectangleShape bg(sf::Vector2f(grid.getWidth() * grid.getCellSize(), grid.getHeight() * grid.getCellSize()));
    bg.setPosition(grid.getWidth() / 2, grid.getHeight() / 2);
    bg.setFillColor(sf::Color(20, 60, 100));
    slamWindow.draw(bg);

    sf::RectangleShape cell(sf::Vector2f(grid.getCellSize(), grid.getCellSize()));

    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            float prob = grid.getProbability(x, y);
            
            // Threshold for how likely a wall is
            if (std::abs(prob - 0.5f) > 0.1f) {
                cell.setPosition(x * grid.getCellSize(), y * grid.getCellSize());
                int intensity = static_cast<int>(prob * 255);
                cell.setFillColor(sf::Color(intensity, intensity, intensity));

                slamWindow.draw(cell);
            }
        }
    }
}

void Renderer::drawRobotPath(const std::vector<PathPoint>& path) {
    if (path.size() < 2) return;

    for (size_t i = 1; i < path.size(); i++) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(path[i-1].x, path[i-1].y), sf::Color(0, 255,0)),
            sf::Vertex(sf::Vector2f(path[i].x, path[i].y), sf::Color(0,255,0))
        };
        slamWindow.draw(line, 2, sf::Lines);
    }

    if (!path.empty()) {
        sf::CircleShape startPoint(5.0f);
        startPoint.setPosition(path[0].x, path[0].y);
        startPoint.setOrigin(5.0f, 5.0f);
        startPoint.setFillColor(sf::Color(0, 255, 0));
        slamWindow.draw(startPoint);
    }
}

void Renderer::drawRobotOnSLAM(const Robot& robot) {
    sf::CircleShape robotPos(6.0f);
    robotPos.setPosition(robot.getX(), robot.getY());
    robotPos.setOrigin(6.0f, 6.0f);
    robotPos.setFillColor(sf::Color(100, 200, 255));
    slamWindow.draw(robotPos);
}