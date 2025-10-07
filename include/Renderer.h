#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "Maze.h"
#include "Robot.h"
#include "Sensor.h"
#include "SLAM.h"

class Renderer {
public:
    Renderer(int windowWidth, int windowHeight, const std::string& title);
    ~Renderer();
    
    // Window management
    bool isOpen() const;
    void clear();
    void display();
    void handleEvents();
    
    // Drawing functions - main window
    void drawMaze(const Maze& maze);
    void drawRobot(const Robot& robot);
    void drawSensorRays(const Robot& robot, const std::vector<RayHit>& hits);
    
    // Drawing functions - SLAM window
    void drawOccupancyGrid(const OccupancyGrid& grid);
    void drawRobotPath(const std::vector<PathPoint>& path);
    void drawRobotOnSLAM(const Robot& robot);

    // Window switching
    void activateMainWindow();
    void activateSLAMWindow();

    // Getters
    sf::RenderWindow& getMainWindow() { return mainWindow; }
    sf::RenderWindow& getSlamWindow() { return slamWindow; }
    
private:
    sf::RenderWindow mainWindow;
    sf::RenderWindow slamWindow;
    int windowWidth;
    int windowHeight;
};

#endif