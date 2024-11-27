#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum Cell
{
    WALL,
    PATH,
    VISITED,
    START,
    END,
    SOLUTION
};

struct Position
{
    int x, y;
    Position(int x, int y) : x(x), y(y) {}
};

class MazeSolver
{
private:
    int width, height, cellSize;
    Position start, end;
    std::vector<std::vector<Cell>> grid;

    void generateDFS(Position pos);

public:
    MazeSolver(int width, int height, int cellSize);
    void generateMaze();
    void draw(sf::RenderWindow &window);
    bool solveBFS(sf::RenderWindow &window); // Añadido para BFS

    // Métodos públicos para acceder a start, end y grid
    Position getStart() const { return start; }
    Position getEnd() const { return end; }
    std::vector<std::vector<Cell>>& getGrid() { return grid; }
};