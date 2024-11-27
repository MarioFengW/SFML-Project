#include "BubbleSort.h"
#include <thread>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace sf;

// Function to visualize and perform Bubble Sort
void BubbleSort(vector<int> &arr, RenderWindow &window, Text &text, bool &sorting, Font &font)
{
    int n = arr.size();
    sorting = true;

    text.setPosition(
        (window.getSize().x - text.getLocalBounds().width) / 2.0f,
        50.0f);

    auto start = chrono::high_resolution_clock::now();

    // Lambda function to draw the array's current state
    auto drawState = [&](int j = -1, int j2 = -1)
    {
        window.clear();
        window.draw(text);

        float barWidth = 25.0f;
        float spacing = 28.0f;
        float startX = (window.getSize().x - (arr.size() * spacing)) / 2.0f;
        float baseY = 400.0f;

        for (size_t k = 0; k < arr.size(); ++k)
        {
            RectangleShape rectangle(Vector2f(barWidth, arr[k]));
            rectangle.setPosition(startX + k * spacing, baseY - arr[k]);

            if (k == j || k == j2)
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
    };

    drawState();
    this_thread::sleep_for(chrono::milliseconds(300));

    // Perform Bubble Sort with visualization
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            drawState(j, j + 1);
            this_thread::sleep_for(chrono::milliseconds(300));

            // Swap elements if they are out of order
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                drawState(j, j + 1);
                this_thread::sleep_for(chrono::milliseconds(300));
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    window.clear();
    window.draw(text);

    // Display the time and space complexity information
    ostringstream oss;
    oss << "Time Complexity: O(n^2)\n";
    oss << "Space Complexity: O(1)\n";
    oss << "Execution Time: " << fixed << setprecision(6) << elapsed.count() << " seconds";

    Text complexityText(oss.str(), font, 20);
    complexityText.setPosition(
        (window.getSize().x - complexityText.getLocalBounds().width) / 2.0f,
        450.0f);
    complexityText.setFillColor(Color::White);

    drawState();
    window.draw(complexityText);
    window.display();

    this_thread::sleep_for(chrono::milliseconds(3000));
    sorting = false;
}
