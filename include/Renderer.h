#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "Maze.h"

class Renderer {
public:
    Renderer(int windowWidth, int windowHeight, const std::string& title);
    ~Renderer();
    
    // Window management
    bool isOpen() const;
    void clear();
    void display();
    void handleEvents();
    
    // Drawing functions
    void drawMaze(const Maze& maze);
    
    // Getters
    sf::RenderWindow& getWindow() { return window; }
    
private:
    sf::RenderWindow window;
    int windowWidth;
    int windowHeight;
};

#endif