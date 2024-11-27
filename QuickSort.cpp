#include "QuickSort.h"
#include <thread>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace sf;

void QuickSort(vector<int> &array, int left, int right, RenderWindow &window, Text &text, bool &sorting, Font &font)
{
    static auto start = chrono::high_resolution_clock::now();

    // Configure title
    text.setPosition(
        (window.getSize().x - text.getLocalBounds().width) / 2.0f,
        50.0f);

    int i = left;
    int j = right;
    int pivot = array[(left + right) / 2];

    // Helper function to draw current state
    auto drawState = [&]()
    {
        window.clear();
        window.draw(text);

        // Calculate bar positioning
        float barWidth = 25.0f;
        float spacing = 28.0f;
        float startX = (window.getSize().x - (array.size() * spacing)) / 2.0f;
        float baseY = 400.0f;

        // Draw bars
        for (size_t k = 0; k < array.size(); ++k)
        {
            RectangleShape rectangle(Vector2f(barWidth, array[k]));
            rectangle.setPosition(startX + k * spacing, baseY - array[k]);

            if (k == i || k == j)
            {
                rectangle.setFillColor(Color(173, 216, 230)); 
            }
            else if (k == (left + right) / 2)
            {
                rectangle.setFillColor(Color(144, 238, 144));
            }
            else
            {
                rectangle.setFillColor(Color::White);
            }
            window.draw(rectangle);

            Text numberText(to_string(array[k]), font, 15);
            numberText.setPosition(startX + k * spacing, baseY - array[k] - 20);
            window.draw(numberText);
        }

        window.display();
    };

    drawState();
    this_thread::sleep_for(chrono::milliseconds(500));

    // Sorting algorithm
    while (i <= j)
    {
        while (i <= right && array[i] < pivot)
        {
            i++;
            drawState();
        }
        while (j >= left && array[j] > pivot)
        {
            j--;
            drawState();
        }
        if (i <= j)
        {
            swap(array[i], array[j]);
            i++;
            j--;
            drawState();
        }
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    // Recursive calls
    if (left < j)
    {
        QuickSort(array, left, j, window, text, sorting, font);
    }
    if (i < right)
    {
        QuickSort(array, i, right, window, text, sorting, font);
    }

    // Final state for complete sort
    if (left == 0 && right == array.size() - 1)
    {
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;

        // Draw complexity text at bottom
        ostringstream oss;
        oss << "Time Complexity: O(n log n)\n";
        oss << "Space Complexity: O(log n)\n";
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
}