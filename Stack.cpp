#include "Stack.h"
#include <iostream>

using namespace std;
using namespace sf;

Stack::Stack() : top(nullptr) {}

Stack::~Stack()
{
    while (top != nullptr)
    {
        Node *temp = top;
        top = top->next;
        delete temp;
    }
}

void Stack::push(int val)
{
    Node *newNode = new Node(val);
    newNode->next = top;
    top = newNode;
}

int Stack::pop()
{
    if (isEmpty())
    {
        return -1; 
    }
    int value = top->data;
    Node *temp = top;
    top = top->next;
    delete temp;
    return value;
}

int Stack::peek() const
{
    if (top == nullptr)
        throw runtime_error("Stack is empty");
    return top->data;
}

bool Stack::isEmpty() const
{
    return top == nullptr;
}

void Stack::display(RenderWindow &window, Font &font) const
{
    Node *temp = top;
    int windowWidth = window.getSize().x;
    int x = windowWidth / 2 - 25; 
    int y = 100;                 
    int spacing = 50;
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
        Text dataText(to_string(temp->data), font, 20);
        dataText.setFillColor(Color::Black); 
        dataText.setPosition(x + width / 4, y + height / 4);
        window.draw(dataText);

        y += spacing;
        temp = temp->next;
    }

    // Draw the top pointer above the first node
    if (top != nullptr)
    {
        Text topText("TOP", font, 20);
        topText.setFillColor(Color::White);
        topText.setPosition(x, 50 - spacing / 2);
        window.draw(topText);

        Vertex topLine[] = {
            Vertex(Vector2f(x + width / 2, 50 - spacing / 2 + 20), Color::Red),
            Vertex(Vector2f(x + width / 2, 100), Color::Red) 
        };
        window.draw(topLine, 2, Lines);

        Vertex topArrowhead[] = {
            Vertex(Vector2f(x + width / 2 - 5, 100 - 5), Color::Red),
            Vertex(Vector2f(x + width / 2, 100), Color::Red),
            Vertex(Vector2f(x + width / 2 + 5, 100 - 5), Color::Red)};
        window.draw(topArrowhead, 3, Triangles);
    }

    // Draw the time and space complexity
    Text complexityText("Time Complexity: O(1)\nSpace Complexity: O(n)", font, 20);
    complexityText.setFillColor(Color::White);
    complexityText.setPosition((windowWidth - complexityText.getLocalBounds().width) / 2, y + 50);
    window.draw(complexityText);
}