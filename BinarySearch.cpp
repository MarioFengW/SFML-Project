// BinarySearch.cpp
#include "BinarySearch.h"
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace sf;

// Function to draw the array on the window
void drawArray(const vector<int> &arr, int left, int right, int mid, RenderWindow &window, Font &font)
{
    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;
    float arrayWidth = arr.size() * 50;
    float x = (windowWidth - arrayWidth) / 2;
    float y = (windowHeight - 40) / 2;

    for (size_t i = 0; i < arr.size(); i++)
    {
        RectangleShape rect(Vector2f(40, 40));
        rect.setPosition(x + i * 50, y);

        if (i == mid)
        {
            rect.setFillColor(Color(173, 216, 230)); // Highlight the middle element
        }
        else if (i >= left && i <= right)
        {
            rect.setFillColor(Color(144, 238, 144)); // Highlight the current search range
        }
        else
        {
            rect.setFillColor(Color::White); // Default color for other elements
        }

        rect.setOutlineThickness(2);
        rect.setOutlineColor(Color::White);

        Text text;
        text.setFont(font);
        text.setString(to_string(arr[i]));
        text.setCharacterSize(20);
        text.setFillColor(Color::Black);
        text.setPosition(x + i * 50 + 10, y + 10);

        window.draw(rect);
        window.draw(text);
    }
}

// Function to perform binary search on the array
int BinarySearch(vector<int> &arr, int target,
                 RenderWindow &window, Text &statusText,
                 bool &searching, Font &font)
{
    sort(arr.begin(), arr.end()); // Ensure the array is sorted

    static int left = 0;
    static int right = arr.size() - 1;
    static int mid = left + (right - left) / 2;
    static Clock clock;
    static auto start = chrono::high_resolution_clock::now();

    if (left == 0 && right == arr.size() - 1)
    {
        start = chrono::high_resolution_clock::now(); 
    }

    if (clock.getElapsedTime().asSeconds() >= 0.5f)
    {
        if (left <= right)
        {
            mid = left + (right - left) / 2;

            if (arr[mid] == target)
            {
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> elapsed = end - start;

                // Update the status text with the result
                stringstream ss;
                ss << "Found " << target << " at position " << mid << "\n";
                ss << "Time Complexity: O(log n)\n";
                ss << "Space Complexity: O(1)\n";
                ss << "Execution Time: " << fixed << setprecision(6) << elapsed.count() << " seconds";
                statusText.setString(ss.str());
                searching = false;
                int foundPos = mid;
                left = 0;
                right = arr.size() - 1;
                return foundPos;
            }

            if (arr[mid] < target)
            {
                left = mid + 1; // Search in the right half
            }
            else
            {
                right = mid - 1; // Search in the left half
            }

            clock.restart(); // Restart the clock for the next step
        }
        else
        {
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;

            // Update the status text with the result
            stringstream ss;
            ss << target << " not found in array\n";
            ss << "Time Complexity: O(log n)\n";
            ss << "Space Complexity: O(1)\n";
            ss << "Execution Time: " << fixed << setprecision(6) << elapsed.count() << " seconds";
            statusText.setString(ss.str());
            searching = false;
            left = 0;
            right = arr.size() - 1;
            return -1;
        }
    }

    drawArray(arr, left, right, mid, window, font); 
    window.draw(statusText); 
    return -1;
}