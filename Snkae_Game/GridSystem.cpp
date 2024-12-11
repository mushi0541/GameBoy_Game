#include "GridSystem.h"
#include <iostream>
// Constructor
GridSystem::GridSystem(Font& fontRef) : font(fontRef) 
{
    float startX = 300;
    float startY = 127; 
    float boxSize = 60; 
    float spacing = 10; 

    for (int row = 0; row < 6; ++row)
    {
        for (int col = 0; col < 5; ++col) 
        {
            grid[row][col].setSize(Vector2f(boxSize, boxSize));
            grid[row][col].setFillColor(Color::Transparent);
            grid[row][col].setOutlineColor(Color::Black);
            grid[row][col].setOutlineThickness(2);
            grid[row][col].setPosition(
                startX + col * (boxSize + spacing),
                startY + row * (boxSize + spacing)
            );

            letters[row][col].setFont(font);
            letters[row][col].setCharacterSize(32);
            letters[row][col].setFillColor(Color::Black);
            letters[row][col].setString("");
            letters[row][col].setPosition(
                grid[row][col].getPosition().x + 15, // Center text
                grid[row][col].getPosition().y + 10
            );
        }
    }
}

// Update a single box with a letter and color
void GridSystem::updateBox(int row, int col, char letter, Color color) 
{
    if (row < 0 || row >= 6 || col < 0 || col >= 5)
        return; // Boundary check
    cout << letter << endl;
    grid[row][col].setFillColor(color);
    if(letter == '0')
		letters[row][col].setString(""); // Update displayed letter
	else
    letters[row][col].setString(letter); // Update displayed letter
}

// Reset the grid for a new game
void GridSystem::reset() 
{
    for (int row = 0; row < 6; ++row) 
    {
        for (int col = 0; col < 5; ++col) 
        {
            grid[row][col].setFillColor(Color::Transparent);
            letters[row][col].setString("");
        }
    }
}

// Draw the grid on the window
void GridSystem::draw(RenderWindow& window) 
{
    for (int row = 0; row < 6; ++row) 
    {
        for (int col = 0; col < 5; ++col) 
        {
            window.draw(grid[row][col]);
            window.draw(letters[row][col]);
        }
    }
}

void GridSystem::getBoxData(int row, int col, char& content, Color& color) const
{
    if (row < 0 || row >= 6 || col < 0 || col >= 5)
    {
        content = '0';          
        color = Color::Transparent; 
        return;
    }

   
    if (!letters[row][col].getString().isEmpty())
    {
        content = letters[row][col].getString()[0];
    }
    else
    {
        content = '0'; 
    }
    
    color = grid[row][col].getFillColor();
}
