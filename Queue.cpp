#include "Queue.h"
#include <iostream>

using namespace sf;

// Constructor for the Queue class
Queue::Queue() : front(nullptr), rear(nullptr) {}

// Destructor for the Queue class
Queue::~Queue()
{
    while (front != nullptr)
    {
        Node *temp = front;
        front = front->next;
        delete temp;
    }
}

// Function to add an element to the queue
void Queue::enqueue(int val)
{
    Node *newNode = new Node(val);
    if (rear == nullptr)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
}

// Function to remove an element from the queue
int Queue::dequeue()
{
    if (isEmpty())
    {
        return -1; 
    }
    int value = front->data;
    Node *temp = front;
    front = front->next;
    if (front == nullptr)
    {
        rear = nullptr;
    }
    delete temp;
    return value;
}

// Function to get the front element of the queue
int Queue::peek() const
{
    if (front == nullptr)
        throw std::runtime_error("Queue is empty");
    return front->data;
}

// Function to check if the queue is empty
bool Queue::isEmpty() const
{
    return front == nullptr;
}

// Function to display the queue in the SFML window
void Queue::display(RenderWindow &window, Font &font) const
{
    Node *temp = front;
    int windowWidth = window.getSize().x;
    int x = windowWidth / 2 - 25; 
    int y = 100;                  
    int spacing = 70;             
    int width = 50;
    int height = 30;

    while (temp != nullptr)
    {
        // Draw the rectangle
        RectangleShape rectangle(Vector2f(width, height));
        rectangle.setPosition(x, y);
        rectangle.setFillColor(Color(173, 216, 230)); 
        rectangle.setOutlineColor(Color::Black);      
        rectangle.setOutlineThickness(2);
        window.draw(rectangle);

        // Draw the data
        Text dataText(std::to_string(temp->data), font, 20);
        dataText.setFillColor(Color::Black); // Black text color
        dataText.setPosition(x + width / 4, y + height / 4);
        window.draw(dataText);

        y += spacing;
        temp = temp->next;
    }

    // Draw the front pointer above the first node
    if (front != nullptr)
    {
        Text frontText("FRONT", font, 20);
        frontText.setFillColor(Color::White);
        frontText.setPosition(x, 50 - spacing / 2);
        window.draw(frontText);

        Vertex frontLine[] = {
            Vertex(Vector2f(x + width / 2, 50 - spacing / 2 + 20), Color::Red),
            Vertex(Vector2f(x + width / 2, 100), Color::Red) 
        };
        window.draw(frontLine, 2, Lines);

        Vertex frontArrowhead[] = {
            Vertex(Vector2f(x + width / 2 - 5, 100 - 5), Color::Red),
            Vertex(Vector2f(x + width / 2, 100), Color::Red),
            Vertex(Vector2f(x + width / 2 + 5, 100 - 5), Color::Red)};
        window.draw(frontArrowhead, 3, Triangles);
    }

    // Draw the rear pointer to the right of the last node
    if (rear != nullptr)
    {
        Text rearText("REAR", font, 20);
        rearText.setFillColor(Color::White);
        rearText.setPosition(x + width + 20, y - spacing);
        window.draw(rearText);

        Vertex rearLine[] = {
            Vertex(Vector2f(x + width, y - spacing + height / 2), Color::Red),     
            Vertex(Vector2f(x + width + 20, y - spacing + height / 2), Color::Red)
        };
        window.draw(rearLine, 2, Lines);

        Vertex rearArrowhead[] = {
            Vertex(Vector2f(x + width + 15, y - spacing + height / 2 - 5), Color::Red),
            Vertex(Vector2f(x + width + 20, y - spacing + height / 2), Color::Red),
            Vertex(Vector2f(x + width + 15, y - spacing + height / 2 + 5), Color::Red)};
        window.draw(rearArrowhead, 3, Triangles);
    }

    // Draw the time and space complexity
    Text complexityText("Time Complexity: O(1)\nSpace Complexity: O(n)", font, 20);
    complexityText.setFillColor(Color::White);
    complexityText.setPosition((windowWidth - complexityText.getLocalBounds().width) / 2, y + 50);
    window.draw(complexityText);
}