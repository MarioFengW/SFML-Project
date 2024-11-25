#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "SortingMenu.h"
#include "SearchMenu.h"
#include "LinearDataStructureMenu.h"
#include "NonLinearDataStructureMenu.h"
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
    // Initialize window and font
    RenderWindow window(VideoMode(800, 600), "Algorithm Visualizer");
    Font font;
    if (!font.loadFromFile("D:\\Python\\src\\C++Class\\Algoritmos\\SituacionProblema\\SFML-2.6.1\\code\\Tinos-Regular.ttf"))
    {
        return EXIT_FAILURE;
    }

    // Initialize menus
    SortingMenu sortingMenu(window, font);
    SearchMenu searchMenu(window, font);
    LinearDataStructureMenu linearMenu(window, font);
    NonLinearDataStructureMenu nonLinearMenu(window, font);

    // Main menu text setup with better spacing
    Text mainMenuText;
    mainMenuText.setFont(font);
    mainMenuText.setCharacterSize(24); 
    mainMenuText.setString(
        "Algorithm Visualizer\n\n"  
        "Main Menu:\n\n"            
        "1. Sorting Algorithms\n\n" 
        "2. Linear Data Structures\n\n"
        "3. Search Algorithms\n\n"
        "4. Non-Linear Data Structures\n\n"
        "\nPress number to select." 
    );

    // Center the text
    FloatRect textBounds = mainMenuText.getLocalBounds();
    mainMenuText.setPosition(
        (window.getSize().x - textBounds.width) / 2.0f,
        (window.getSize().y - textBounds.height) / 3.0f
    );

    // Menu state tracking
    enum MainState
    {
        MAIN,
        SORTING,
        LINEAR,
        SEARCH,
        NONLINEAR
    };
    MainState currentState = MAIN;

    // Set background color
    Color backgroundColor(30, 30, 30); 

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            // Main menu navigation
            if (currentState == MAIN && event.type == Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case Keyboard::Num1:
                    currentState = SORTING;
                    sortingMenu.reset();
                    break;
                case Keyboard::Num2:
                    currentState = LINEAR;
                    linearMenu.reset();
                    break;
                case Keyboard::Num3:
                    currentState = SEARCH;
                    searchMenu.reset();
                    break;
                case Keyboard::Num4:
                    currentState = NONLINEAR;
                    nonLinearMenu.reset();
                    break;
                }
            }
            else if (event.key.code == Keyboard::B)
            {
                currentState = MAIN;
            }
            else
            {
                switch (currentState)
                {
                case SORTING:
                    sortingMenu.handleEvents(event);
                    break;
                case LINEAR:
                    linearMenu.handleEvents(event);
                    break;
                case SEARCH:
                    searchMenu.handleEvents(event);
                    break;
                case NONLINEAR:
                    nonLinearMenu.handleEvents(event);
                    break;
                }
            }
        }

        // Render current menu
        window.clear(backgroundColor);

        switch (currentState)
        {
        case MAIN:
            window.draw(mainMenuText);
            break;
        case SORTING:
            sortingMenu.draw();
            break;
        case LINEAR:
            linearMenu.draw();
            break;
        case SEARCH:
            searchMenu.draw();
            break;
        case NONLINEAR:
            nonLinearMenu.draw();
            break;
        }

        window.display();
    }

    return EXIT_SUCCESS;
}