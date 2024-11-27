#include "SearchMenu.h"

using namespace std;
using namespace sf;

SearchMenu::SearchMenu(RenderWindow &window, Font &font)
    : window(window), font(font),
      currentState(MAIN_MENU),
      numberOfElements(0), searchTarget(0),
      searching(false), searchComplete(false),
      selectedAlgorithm(0),
      searchResult(-1)
{
    initializeTexts();
}

// Function to initialize text elements
void SearchMenu::initializeTexts()
{
    menuText.setFont(font);
    menuText.setCharacterSize(24);
    menuText.setString("Search Algorithms:\n1. Linear Search\n2. Binary Search\nPress number to select, or 'B' to go back.");
    menuText.setPosition(
        (window.getSize().x - menuText.getLocalBounds().width) / 2.0f,
        50.0f);

    promptText.setFont(font);
    promptText.setCharacterSize(24);
    promptText.setPosition(
        (window.getSize().x - promptText.getLocalBounds().width) / 2.0f,
        100.0f);

    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setPosition(
        (window.getSize().x - inputText.getLocalBounds().width) / 2.0f,
        250.0f);

    statusText.setFont(font);
    statusText.setCharacterSize(24);
    statusText.setFillColor(Color::White);
    statusText.setPosition(
        (window.getSize().x - statusText.getLocalBounds().width) / 2.0f,
        350.0f);

    backText.setFont(font);
    backText.setCharacterSize(24);
    backText.setString("Press B to go back");
    FloatRect backBounds = backText.getLocalBounds();
    backText.setPosition(
        (window.getSize().x - backBounds.width) / 2.0f,
        window.getSize().y - 50.0f);

    updatePrompt();
}

// Function to update the prompt text based on the current state
void SearchMenu::updatePrompt()
{
    if (currentState != MAIN_MENU)
    {
        menuText.setString(""); 
    }

    switch (currentState)
    {
    case MAIN_MENU:
        promptText.setString("");
        break;
    case WAITING_FOR_COUNT:
        promptText.setString("Enter the number of elements:\nPress 'B' to go back");
        break;
    case WAITING_FOR_ELEMENTS:
        promptText.setString("Enter the elements separated by spaces:\nPress 'B' to go back");
        break;
    case WAITING_FOR_TARGET:
        promptText.setString("Enter target number to search:\nPress 'B' to go back");
        break;
    default:
        break;
    }
    FloatRect promptBounds = promptText.getLocalBounds();
    promptText.setPosition(
        (window.getSize().x - promptBounds.width) / 2.0f,
        100.0f);
}

// Function to parse input string into a vector of integers
vector<int> SearchMenu::parseInput(const string &input)
{
    vector<int> result;
    stringstream ss(input);
    int number;
    while (ss >> number)
    {
        result.push_back(number);
    }
    return result;
}

// Function to handle events
void SearchMenu::handleEvents(Event &event)
{
    if (event.type == Event::KeyPressed)
    {
        if (event.key.code == Keyboard::B)
        {
            if (currentState != MAIN_MENU)
            {
                reset();
                return;
            }
        }

        if (currentState == MAIN_MENU)
        {
            if (event.key.code == Keyboard::Num1)
            {
                selectedAlgorithm = 1;
                currentState = WAITING_FOR_COUNT;
                inputBuffer.clear();
                updatePrompt();
            }
            else if (event.key.code == Keyboard::Num2)
            {
                selectedAlgorithm = 2;
                currentState = WAITING_FOR_COUNT;
                inputBuffer.clear();
                updatePrompt();
            }
        }
        else if (event.key.code == Keyboard::Enter)
        {
            processInput();
        }
    }

    if (event.type == Event::TextEntered && !searching)
    {
        if (isdigit(event.text.unicode) || event.text.unicode == ' ')
        {
            inputBuffer += static_cast<char>(event.text.unicode);
            inputText.setString(inputBuffer);
        }
        else if (event.text.unicode == '\b' && !inputBuffer.empty())
        {
            inputBuffer.pop_back();
            inputText.setString(inputBuffer);
        }
    }
}

// Function to process input based on the current state
void SearchMenu::processInput()
{
    switch (currentState)
    {
    case MAIN_MENU:
        break;
    case WAITING_FOR_COUNT:
        numberOfElements = stoi(inputBuffer);
        currentState = WAITING_FOR_ELEMENTS;
        inputBuffer.clear();
        break;
    case WAITING_FOR_ELEMENTS:
        arr = parseInput(inputBuffer);
        if (arr.size() == numberOfElements)
        {
            currentState = WAITING_FOR_TARGET;
            inputBuffer.clear();
        }
        break;
    case WAITING_FOR_TARGET:
        searchTarget = stoi(inputBuffer);
        searching = true;
        currentState = SEARCHING;
        inputBuffer.clear();
        break;
    default:
        break;
    }
    inputText.setString(inputBuffer);
    updatePrompt();
}

// Function to draw the current menu and search results
void SearchMenu::draw()
{
    window.clear(Color(30, 30, 30));

    window.draw(menuText);
    window.draw(promptText);
    window.draw(inputText);
    window.draw(statusText);

    if (searching && currentState == SEARCHING)
    {
        if (selectedAlgorithm == 1)
        {
            searchResult = LinearSearch(arr, searchTarget, window, statusText, searching, font);
        }
        else if (selectedAlgorithm == 2)
        {
            searchResult = BinarySearch(arr, searchTarget, window, statusText, searching, font);
        }
    }

    if (!searching && currentState == SEARCHING)
    {
        currentState = SEARCH_COMPLETE;

        FloatRect statusBounds = statusText.getLocalBounds();
        statusText.setPosition(
            (window.getSize().x - statusBounds.width) / 2.0f,
            350.0f);
    }
}

// Function to reset the menu state
void SearchMenu::reset()
{
    currentState = MAIN_MENU;
    searching = false;
    searchComplete = false;
    numberOfElements = 0;
    searchTarget = 0;
    searchResult = -1;
    selectedAlgorithm = 0;
    inputBuffer.clear();
    arr.clear();
    inputText.setString("");
    statusText.setString("");
    menuText.setString("Search Algorithms:\n\n1. Linear Search\n2. Binary Search\n\nPress number to select, or 'B' to go back.");
    updatePrompt();
}