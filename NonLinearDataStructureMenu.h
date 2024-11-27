#pragma once
#include <SFML/Graphics.hpp>
#include "AVLTree.h"
#include "Graphs.h"
#include "MazeSolver.h"
#include "BFS.h"
#include "DFS.h"

class NonLinearDataStructureMenu
{
private:
    sf::RenderWindow &window; 
    sf::Font &font;       
    sf::Text promptText;     
    sf::Text backText;        
    sf::Text inputText;       
    sf::Text complexityText;  
    std::string inputString;  
    AVLTree avlTree;         
    Graphs graphs;            
    MazeSolver mazeSolver;    

    // Enumerations for submenus
    enum SubMenu
    {
        MAIN_MENU,
        AVL_TREE_MENU,
        GRAPH_MENU,
        MAZE_MENU
    } currentSubMenu; 

    // Enumerations for input modes
    enum InputMode
    {
        NONE,
        INSERT,
        DELETE,
        SOLVE_BFS,
        SOLVE_DFS
    } inputMode; 

    void initializeTexts();       
    void updatePrompt();          
    void updateComplexityText(); 

public:
    NonLinearDataStructureMenu(sf::RenderWindow &window, sf::Font &font);
    void handleEvents(sf::Event &event); 
    void draw(); 
    void reset(); 
};