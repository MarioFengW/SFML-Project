#include "SelectionSort.h"
#include <thread>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace sf;

// Function to draw the array on the window
void drawArray(const vector<int> &arr, RenderWindow &window, Text &text, Font &font, int highlight1 = -1, int highlight2 = -1)
{
    window.clear();
    window.draw(text);

    // Calculate bar positioning
    float barWidth = 25.0f;
    float spacing = 28.0f;
    float startX = (window.getSize().x - (arr.size() * spacing)) / 2.0f;
    float baseY = 400.0f;

    // Draw bars
    for (size_t k = 0; k < arr.size(); ++k)
    {
        RectangleShape rectangle(Vector2f(barWidth, arr[k]));
        rectangle.setPosition(startX + k * spacing, baseY - arr[k]);

        if (k == highlight1 || k == highlight2)
        {
            rectangle.setFillColor(Color(173, 216, 230));
        }
        else
        {
            rectangle.setFillColor(Color::White);
        }
        window.draw(rectangle);

        Text numberText(to_string(arr[k]), font, 15);
        numberText.setPosition(startX + k * spacing, baseY - arr[k] - 20);
        window.draw(numberText);
    }
    window.display();
}

// Function to perform selection sort on the array
void SelectionSort(vector<int> &arr, RenderWindow &window, Text &text, bool &sorting, Font &font)
{
    int n = arr.size();
    sorting = true;

    text.setPosition(
        (window.getSize().x - text.getLocalBounds().width) / 2.0f,
        50.0f);

    auto start = chrono::high_resolution_clock::now();
    
    drawArray(arr, window, text, font);
    this_thread::sleep_for(chrono::milliseconds(300));

    // Sorting algorithm
    for (int i = 0; i < n - 1; i++)
    {
        int minVal = i;

        for (int j = i + 1; j < n; j++)
        {
            drawArray(arr, window, text, font, minVal, j);
            this_thread::sleep_for(chrono::milliseconds(300));

            if (arr[j] < arr[minVal])
            {
                minVal = j;
            }
        }

        if (minVal != i)
        {
            swap(arr[i], arr[minVal]);
            drawArray(arr, window, text, font, i, minVal);
            this_thread::sleep_for(chrono::milliseconds(300));
        }
    }

    // Calculate time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    // Draw complexity text at bottom
    ostringstream oss;
    oss << "Time Complexity: O(n^2)\n";
    oss << "Space Complexity: O(1)\n";
    oss << "Execution Time: " << fixed << setprecision(6) << elapsed.count() << " seconds";

    Text complexityText(oss.str(), font, 20);
    complexityText.setPosition(
        (window.getSize().x - complexityText.getLocalBounds().width) / 2.0f,
        450.0f);
    complexityText.setFillColor(Color::White);

    drawArray(arr, window, text, font);
    window.draw(complexityText);
    window.display();

    this_thread::sleep_for(chrono::milliseconds(3000));
    sorting = false;
}