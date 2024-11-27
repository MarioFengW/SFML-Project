#include "MazeSolver.h"
#include <random>
#include <algorithm>
#include <queue>
#include <thread>
#include <chrono>

using namespace std;
using namespace sf;

// Constructor for the MazeSolver class
MazeSolver::MazeSolver(int width, int height, int cellSize)
    : width(width), height(height), cellSize(cellSize), start(1, 1), end(width - 2, height - 2)
{
    grid.resize(width, vector<Cell>(height, WALL));
    generateMaze();
    grid[start.x][start.y] = START;
    grid[end.x][end.y] = END;
}

// Function to generate the maze
void MazeSolver::generateMaze()
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            grid[x][y] = WALL;
        }
    }
    generateDFS(start);
    grid[start.x][start.y] = START;
    grid[end.x][end.y] = END;
}

// Function to generate the maze using DFS
void MazeSolver::generateDFS(Position pos)
{
    grid[pos.x][pos.y] = PATH;
    vector<Position> directions = {{0, -2}, {0, 2}, {-2, 0}, {2, 0}};
    shuffle(directions.begin(), directions.end(), mt19937(random_device()()));

    for (const Position &direction : directions)
    {
        int nx = pos.x + direction.x;
        int ny = pos.y + direction.y;

        if (nx > 0 && ny > 0 && nx < width - 1 && ny < height - 1 && grid[nx][ny] == WALL)
        {
            grid[nx][ny] = PATH;
            grid[pos.x + direction.x / 2][pos.y + direction.y / 2] = PATH;
            generateDFS({nx, ny});
        }
    }
}

// Function to solve the maze using BFS
bool MazeSolver::solveBFS(sf::RenderWindow &window)
{
    queue<Position> q;
    q.push(start);
    vector<vector<bool>> visited(width, vector<bool>(height, false));
    visited[start.x][start.y] = true;

    vector<Position> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    while (!q.empty())
    {
        Position current = q.front();
        q.pop();

        if (current.x == end.x && current.y == end.y)
        {
            grid[current.x][current.y] = SOLUTION;
            return true;
        }

        for (const Position &direction : directions)
        {
            int nx = current.x + direction.x;
            int ny = current.y + direction.y;

            if (nx >= 0 && ny >= 0 && nx < width && ny < height && !visited[nx][ny] && (grid[nx][ny] == PATH || grid[nx][ny] == END))
            {
                visited[nx][ny] = true;
                q.push({nx, ny});
                grid[nx][ny] = VISITED;

                // Draw the maze at each step
                window.clear(Color(30, 30, 30));
                draw(window);
                window.display();

                // Add a small delay for the animation
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }
    }

    return false;
}

// Function to draw the maze
void MazeSolver::draw(RenderWindow &window)
{
    float scale = 0.8f;
    float offsetX = (window.getSize().x - width * cellSize * scale) / 2.0f;
    float offsetY = 200.0f;

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            RectangleShape cell(Vector2f(cellSize * scale, cellSize * scale));
            cell.setPosition(offsetX + x * cellSize * scale, offsetY + y * cellSize * scale);

            switch (grid[x][y])
            {
            case WALL:
                cell.setFillColor(Color::Black);
                break;
            case PATH:
                cell.setFillColor(Color::White);
                break;
            case VISITED:
                cell.setFillColor(Color(173, 216, 230));
                break;
            case START:
                cell.setFillColor(Color::Green);
                break;
            case END:
                cell.setFillColor(Color::Red);
                break;
            case SOLUTION:
                cell.setFillColor(Color::Yellow);
                break;
            }

            window.draw(cell);
        }
    }
}