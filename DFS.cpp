#include "DFS.h"
#include "MazeSolver.h"
#include <thread>
#include <chrono>

using namespace std;
using namespace sf;

// Function to solve the maze using Depth-First Search (DFS)
bool DFS::solve(MazeSolver &maze, RenderWindow &window)
{
    return solveDFS(maze, maze.getStart(), window);
}

// Recursive function to perform DFS
bool DFS::solveDFS(MazeSolver &maze, Position pos, RenderWindow &window)
{
    // Check if we have reached the end position
    if (pos.x == maze.getEnd().x && pos.y == maze.getEnd().y)
    {
        maze.getGrid()[pos.x][pos.y] = SOLUTION;
        return true;
    }

    // Mark the current position as visited
    maze.getGrid()[pos.x][pos.y] = VISITED;

    // Possible movement directions
    vector<Position> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    for (const Position &dir : directions)
    {
        Position newPos(pos.x + dir.x, pos.y + dir.y);
        // Check if the new position is within bounds and is a path or the end
        if (newPos.x >= 0 && newPos.y >= 0 && newPos.x < maze.getGrid().size() && newPos.y < maze.getGrid()[0].size() && (maze.getGrid()[newPos.x][newPos.y] == PATH || maze.getGrid()[newPos.x][newPos.y] == END))
        {
            // Draw the maze at each step
            window.clear(Color(30, 30, 30));
            maze.draw(window);
            window.display();

            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            // Recursively solve the maze from the new position
            if (solveDFS(maze, newPos, window))
            {
                maze.getGrid()[newPos.x][newPos.y] = SOLUTION;
                return true;
            }
        }
    }

    // Mark the current position as a path (backtrack)
    maze.getGrid()[pos.x][pos.y] = PATH;

    // Draw the maze at each step
    window.clear(Color(30, 30, 30));
    maze.draw(window);
    window.display();

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    return false;
}