#ifndef GRIDSYSTEM_H
#define GRIDSYSTEM_H

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class GridSystem 
{
private:
    RectangleShape grid[6][5];  // 6 rows, 5 columns of boxes
    Text letters[6][5];         // Text inside each box
    Font& font;                 // Reference to the font used

public:
    // Constructor
    GridSystem(Font& fontRef);

    // Update a single box with a letter and color
    void updateBox(int row, int col, char letter, Color color);

    // Reset the grid for a new game
    void reset();

    // Draw the grid on the window
    void getBoxData(int row, int col, char& content, Color& color) const;
    void draw(RenderWindow& window);
};

#endif // GRIDSYSTEM_H
