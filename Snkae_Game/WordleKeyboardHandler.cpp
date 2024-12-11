#include "WordleKeyboardHandler.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <ctime>
#include <iostream>

using namespace std;


WordleKeyboardHandler::WordleKeyboardHandler(Font& fontRef, const string& targetWord, int& livesRef)
    : font(fontRef), word(targetWord), lives(livesRef)
{
    for (int i = 0; i < 26; i++)
    {
        keys[i].setSize(Vector2f(40, 40));
        keys[i].setFillColor(Color::Transparent);
        keys[i].setOutlineColor(Color::Black);
        keys[i].setOutlineThickness(3);

        if (i < 10)
        {
            keys[i].setPosition(230 + i * 50, 610); // First row
        }
        else if (i < 19)
        {
            keys[i].setPosition(250 + (i - 10) * 50, 660); // Second row
        }
        else
        {
            keys[i].setPosition(300 + (i - 19) * 50, 710); // Third row
        }

        keyLetters[i] = 'A' + i;
        keyTexts[i].setFont(font);
        keyTexts[i].setString(keyLetters[i]);
        keyTexts[i].setCharacterSize(24);
        keyTexts[i].setFillColor(Color::Black);
        keyTexts[i].setPosition(keys[i].getPosition().x + 10, keys[i].getPosition().y + 5);
    }

    // Initialize Enter key
    enterKey.setSize(Vector2f(80, 40));
    enterKey.setFillColor(Color::Transparent);
    enterKey.setOutlineColor(Color::Black);
    enterKey.setOutlineThickness(3);
    enterKey.setPosition(210, 710);
    enterText.setFont(font);
    enterText.setString("Enter");
    enterText.setCharacterSize(18);
    enterText.setFillColor(Color::Black);
    enterText.setPosition(enterKey.getPosition().x + 10, enterKey.getPosition().y + 5);

    // Initialize Backspace key
    backspaceKey.setSize(Vector2f(80, 40));
    backspaceKey.setFillColor(Color::Transparent);
    backspaceKey.setOutlineColor(Color::Black);
    backspaceKey.setOutlineThickness(3);
    backspaceKey.setPosition(650, 710);
    backspaceText.setFont(font);
    backspaceText.setString("Back");
    backspaceText.setCharacterSize(18);
    backspaceText.setFillColor(Color::Black);
    backspaceText.setPosition(backspaceKey.getPosition().x + 10, backspaceKey.getPosition().y + 5);
}

// Handles keyboard and mouse input
bool WordleKeyboardHandler::handleInput(Event& event, string& currentGuess, int& currentRow, string& feedback)
{
    if (event.type == Event::KeyPressed)
    {
        if (event.key.code >= Keyboard::A && event.key.code <= Keyboard::Z)
        {
            if (currentGuess.length() < 5)
            {
                char guessedLetter = 'A' + (event.key.code - Keyboard::A);
                currentGuess += guessedLetter;
                return false;
            }
        }
        // Handle Enter key (submission)
        else if (event.key.code == Keyboard::Enter)
        {
            if (currentGuess.length() < 5)
            {
                feedback = "Not enough letters!";
                cout << feedback << endl; 
                return false; // Prevent submission
            }
            else if (currentGuess.length() == 5)
            {
                feedback = checkGuess(currentGuess);
                //currentRow++;
                return true; // Word submitted
            }
        }
        // Handle Backspace key
        else if (event.key.code == Keyboard::Backspace)
        {
            if (!currentGuess.empty())
            {
                char removedLetter = currentGuess.back();
                currentGuess.pop_back();
                return false; // Letter removed
            }
        }
    }

    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
    {
        Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        for (int i = 0; i < 26; i++)
        {
            if (keys[i].getGlobalBounds().contains(mousePos) && currentGuess.length() < 5)
            {
                char guessedLetter = keyLetters[i];
               
                    currentGuess += guessedLetter;
                    return false;
            }
        }

        if (enterKey.getGlobalBounds().contains(mousePos))
        {
            if (currentGuess.length() < 5)
            {
                feedback = "Not enough letters!";
                cout << feedback << endl;
                return false; // Prevent submission
            }
            else if (currentGuess.length() == 5)
            {
                feedback = checkGuess(currentGuess);
                return true; // Word submitted
            }
        }

        if (backspaceKey.getGlobalBounds().contains(mousePos) && !currentGuess.empty())
        {
            char removedLetter = currentGuess.back();
            currentGuess.pop_back();
            return false;
        }
    }

    return false; 
}


// Update key color based on user interaction
void WordleKeyboardHandler::updateKeyColor(char letter, Color color)
{
    int index = letter - 'A';
    if (index >= 0 && index < 26)
    {
        keys[index].setFillColor(color);
    }
}

// Draw the keyboard
void WordleKeyboardHandler::draw(RenderWindow& window)
{
    // Draw each key and its corresponding text
    for (int i = 0; i < 26; i++)
    {
        window.draw(keys[i]);
        window.draw(keyTexts[i]);
    }

    // Draw Enter and Backspace keys
    window.draw(enterKey);
    window.draw(enterText);
    window.draw(backspaceKey);
    window.draw(backspaceText);
}

// Handles feedback for the guess
string WordleKeyboardHandler::checkGuess(const string& guess)
{
    string result = "";

    for (int i = 0; i < 5; ++i)
    {
        if (tolower(guess[i]) == word[i])
        {
            cout<<guess[i]<<endl;
            result += "G"; // Green
            updateKeyColor(guess[i], Color::Green);
        }
        else if (count(word.begin(), word.end(),tolower( guess[i])))
        {
            result += "Y"; // Yellow
            updateKeyColor(guess[i], Color::Yellow);
        }
        else
        {
            cout<<guess[i]<<endl;
            result += "B"; // Gray
            updateKeyColor(guess[i], Color::Red);
        }
    }
    return result;
}

// Reset the keyboard state
void WordleKeyboardHandler::reset()
{
    for (int i = 0; i < 26; i++)
    {
        keys[i].setFillColor(Color::Transparent);
    }
}
