#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
using namespace sf;
using namespace std;


class KeyboardHandler 
{
private:
    RectangleShape keys[26];     // Visual representation of keyboard keys
    Text keyTexts[26];          // Letters displayed on keys
    char keyLetters[26];        // Letters A-Z
    bool isGuessed[26];         // Track guessed letters
    Font& font;                 // Reference to the font
    const std::string& word;    // Reference to the target word
    Text* wordDisplay;          // Word display Text array
    int& lives;                 // Reference to lives

public:
    // Constructor to initialize the keyboard and word display
    KeyboardHandler(Font& fontRef, const std::string& targetWord, int& livesRef, Text* wordDisplayRef);

    // Handles the input (keyboard or mouse) for guessing letters and updating word
    int handleInput(Event& event, int& score, string& currentGuess);

    // Draw the keyboard and word display
    void draw(RenderWindow& window);

    // Handles mouse hover effect on keys (for visual feedback)
    void handleMouseHover(Vector2f mousePos);

    // Reveal one character in the word (Hint system)
    void revealHint(int& score,Vector2f mousePos,RectangleShape hintButton, bool& hintUsed);

    void reset();
};

#endif
