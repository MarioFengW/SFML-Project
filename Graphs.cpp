#include "Graphs.h"
#include <algorithm>
#include <iostream>

using namespace std;
using namespace sf;

// Constructor for the Graphs class
Graphs::Graphs(RenderWindow &window, Font &font)
    : window(window), font(font)
{
}

// Function to generate a predefined graph
void Graphs::generatePredefinedGraph()
{
    reset();

    // Insert nodes
    for (int i = 0; i <= 23; ++i)
    {
        nodes.push_back(i);
    }

    // Insert predefined connections
    adjList.resize(nodes.size());
    auto addEdge = [&](int u, int v, int weight)
    {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // Make the graph bidirectional
    };

    // Add edges with weights
    addEdge(0, 1, 47);
    addEdge(0, 23, 14);
    addEdge(1, 2, 288);
    addEdge(1, 10, 49);
    addEdge(2, 3, 45);
    addEdge(3, 4, 48);
    addEdge(3, 11, 129);
    addEdge(4, 5, 53);
    addEdge(4, 12, 133);
    addEdge(5, 6, 47);
    addEdge(5, 19, 172);
    addEdge(6, 7, 50);
    addEdge(7, 8, 41);
    addEdge(8, 9, 47);
    addEdge(8, 14, 106);
    addEdge(9, 15, 120);
    addEdge(9, 16, 267);
    addEdge(10, 2, 145);
    addEdge(10, 11, 51);
    addEdge(11, 12, 47);
    addEdge(12, 20, 39);
    addEdge(13, 7, 103);
    addEdge(13, 14, 46);
    addEdge(14, 15, 46);
    addEdge(15, 9, 120);
    addEdge(15, 16, 46);
    addEdge(16, 21, 99);
    addEdge(17, 13, 52);
    addEdge(17, 18, 53);
    addEdge(18, 6, 161);
    addEdge(18, 19, 47);
    addEdge(19, 5, 172);
    addEdge(19, 20, 57);
    addEdge(20, 23, 87);
    addEdge(22, 17, 36);
    addEdge(22, 21, 12);

    // Define positions of the nodes
    nodePositions = {
        {100, 100},  // Node 0
        {250, 100},  // Node 1
        {400, 100},  // Node 2
        {600, 100},  // Node 3
        {750, 100},  // Node 4
        {900, 100},  // Node 5
        {1050, 100}, // Node 6
        {1200, 100}, // Node 7
        {1350, 100}, // Node 8
        {1500, 100}, // Node 9
        {300, 250},  // Node 10
        {550, 250},  // Node 11
        {700, 250},  // Node 12
        {1050, 250}, // Node 13
        {1200, 250}, // Node 14
        {1350, 250}, // Node 15
        {1500, 250}, // Node 16
        {1050, 350}, // Node 17
        {700, 350},  // Node 18
        {900, 400},  // Node 19
        {550, 400},  // Node 20
        {1500, 450}, // Node 21
        {1050, 450}, // Node 22
        {100, 250}   // Node 23
    };
}

// Function to draw the graph
void Graphs::draw()
{
    View originalView = window.getView();

    View graphView(FloatRect(0, 0, window.getSize().x * 2, window.getSize().y));
    graphView.setViewport(FloatRect(0, 0.2f, 1, 0.6f)); // Adjust the drawing area of the graph
    window.setView(graphView);

    // Draw the connections first
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        for (const auto &edge : adjList[i])
        {
            int neighbor = edge.first;
            int weight = edge.second;

            // Line between nodes
            Vertex line[] = {
                Vertex(nodePositions[i], Color::White),
                Vertex(nodePositions[neighbor], Color::White)};
            window.draw(line, 2, Lines);

            // Draw weight (midpoint with offset)
            if (weight != INF)
            {
                Text weightText;
                weightText.setFont(font);
                weightText.setString(to_string(weight));
                weightText.setCharacterSize(16);
                weightText.setFillColor(Color::Yellow);

                Vector2f midPoint = (nodePositions[i] + nodePositions[neighbor]) / 2.0f;
                midPoint.y -= 10;
                weightText.setPosition(midPoint);
                window.draw(weightText);
            }
        }
    }

    // Draw nodes
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        CircleShape circle(25);
        circle.setFillColor(Color(173, 216, 230));
        circle.setPosition(nodePositions[i] - Vector2f(20, 20));
        window.draw(circle);

        // Node text
        Text nodeText;
        nodeText.setFont(font);
        nodeText.setString(to_string(nodes[i]));
        nodeText.setCharacterSize(22);
        nodeText.setFillColor(Color::Black);
        nodeText.setPosition(nodePositions[i] - Vector2f(10, 10));
        window.draw(nodeText);
    }

    window.setView(originalView);
}

void Graphs::reset()
{
    nodes.clear();
    adjList.clear();
    nodePositions.clear();
}

// Function to perform Dijkstra's algorithm
vector<Nodo> Graphs::dijkstra(int origen)
{
    int n = nodes.size();
    vector<int> distancias(n, INF);
    vector<vector<int>> rutas(n);
    distancias[origen] = 0;
    rutas[origen] = {origen};

    // Priority queue: (accumulated distance, node)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, origen});

    while (!pq.empty())
    {
        int distancia_actual = pq.top().first;
        int nodo_actual = pq.top().second;
        pq.pop();

        if (distancia_actual > distancias[nodo_actual])
            continue;

        // Explore neighbors
        for (const auto &vecino : adjList[nodo_actual])
        {
            int nodo_vecino = vecino.first;
            int peso_arista = vecino.second;

            int nueva_distancia = distancia_actual + peso_arista;

            if (nueva_distancia < distancias[nodo_vecino])
            {
                distancias[nodo_vecino] = nueva_distancia;
                rutas[nodo_vecino] = rutas[nodo_actual];
                rutas[nodo_vecino].push_back(nodo_vecino);
                pq.push({nueva_distancia, nodo_vecino});
            }
        }
    }

    vector<Nodo> resultado;
    for (int i = 0; i < n; ++i)
    {
        if (distancias[i] == INF)
        {
            distancias[i] = -1; // Mark as unreachable
            rutas[i].clear();
        }
        resultado.push_back({i, distancias[i], rutas[i]});
    }
    return resultado;
}

bool Graphs::nodeExists(int node)
{
    return find(nodes.begin(), nodes.end(), node) != nodes.end();
}

// Function to draw the shortest path
void Graphs::drawShortestPath(int startNode, int endNode)
{
    if (!nodeExists(startNode) || !nodeExists(endNode))
    {
        return;
    }

    vector<Nodo> dijkstraResult = dijkstra(startNode);
    vector<int> path = dijkstraResult[endNode].ruta;

    if (path.empty())
    {
        return;
    }

    // Draw the shortest path
    for (size_t i = 0; i < path.size() - 1; ++i)
    {
        int currentNode = path[i];
        int nextNode = path[i + 1];

        // Line between nodes
        Vertex line[] = {
            Vertex(nodePositions[currentNode], Color::Red),
            Vertex(nodePositions[nextNode], Color::Red)};
        window.draw(line, 2, Lines);
    }
}