#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class WordleKeyboardHandler {
private:
    RectangleShape keys[26]; // Rectangles for A-Z keys
    Text keyTexts[26];       // Text for A-Z keys
    char keyLetters[26];     // Letters corresponding to keys

    RectangleShape enterKey; // Rectangle for Enter key
    Text enterText;          // Text for Enter key

    RectangleShape backspaceKey; // Rectangle for Backspace key
    Text backspaceText;          // Text for Backspace key

    Font& font;                // Reference to font
    const string& word;        // Target word to guess
    int& lives;                // Reference to lives counter
   

public:
    // Constructor
    WordleKeyboardHandler(Font& fontRef, const string& targetWord, int& livesRef);

    // Handles input events (keyboard and mouse)
    bool handleInput(Event& event, string& currentGuess, int& currentRow, string& feedback);

    // Update the color of a key
    void updateKeyColor(char letter, Color color);

    // Draw the keyboard on the window
    void draw(RenderWindow& window);

    // Check the user's guess and return feedback (G, Y, B for Green, Yellow, Gray)
    string checkGuess(const string& guess);

    // Reset the keyboard to initial state
    void reset();
};

#endif // KEYBOARDHANDLER_H