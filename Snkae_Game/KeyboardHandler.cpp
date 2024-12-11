#include "KeyboardHandler.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <ctime>

// Constructor to initialize the keyboard and word display
KeyboardHandler::KeyboardHandler(Font& fontRef, const std::string& targetWord, int& livesRef, Text* wordDisplayRef)
    : font(fontRef), word(targetWord), lives(livesRef), wordDisplay(wordDisplayRef) 
{

    // Initialize keys and texts for A-Z keys
    for (int i = 0; i < 26; i++) 
    {
        keys[i].setSize(Vector2f(40, 40));
        keys[i].setFillColor(Color::White);
        keys[i].setOutlineColor(Color::Black);
        keys[i].setOutlineThickness(2);

        if (i < 10) 
        {
            keys[i].setPosition(250 + i * 50, 700); // First row
        }
        else if (i < 19) 
        {
            keys[i].setPosition(270 + (i - 10) * 50, 750); // Second row
        }
        else 
        {
            keys[i].setPosition(320 + (i - 19) * 50, 800); // Third row
        }

        keyLetters[i] = 'A' + i;
        keyTexts[i].setFont(font);
        keyTexts[i].setString(keyLetters[i]);
        keyTexts[i].setCharacterSize(24);
        keyTexts[i].setFillColor(Color::Black);
        keyTexts[i].setPosition(keys[i].getPosition().x + 10, keys[i].getPosition().y + 5);

        isGuessed[i] = false; // Initialize guessed state
    }

    // Initialize word display with underscores
    for (size_t i = 0; i < word.length(); i++) 
    {
        wordDisplay[i].setFont(font);
        wordDisplay[i].setCharacterSize(32);
        wordDisplay[i].setFillColor(Color::Black);
        wordDisplay[i].setString("_");
        wordDisplay[i].setPosition(500 + i * 40, 550); // Positioning based on word length
    }
}

int KeyboardHandler::handleInput(Event& event, int& score,string& currentGuess) 
{
    if (event.type == Event::KeyPressed) 
    {
        if (event.key.code >= Keyboard::A && event.key.code <= Keyboard::Z) 
        {
            char guessedLetter = 'A' + (event.key.code - Keyboard::A);
            int index = event.key.code - Keyboard::A;

            if (!isGuessed[index]) 
            {
                isGuessed[index] = true; // Mark letter as guessed
                bool correct = false;

                // Check for correct guesses and update word display
                for (size_t i = 0; i < word.length(); ++i) 
                {
                    if (toupper(word[i]) == guessedLetter) 
                    {
                        currentGuess[i] = guessedLetter;
                        wordDisplay[i].setString(std::string(1, guessedLetter)); // Reveal letter
                        correct = true;
                        score += 10; // Increment score for correct guess
                    }
                }

                // Change key color based on correct or incorrect guess
                if (correct) 
                {
                    keys[index].setFillColor(Color::Green); // Set key color to green for correct guess
                    return 1; // Return 1 to indicate correct guess
                }
                else 
                {
                    keys[index].setFillColor(Color::Red); // Set key color to red for incorrect guess
                    --lives; // Decrement lives on incorrect guess
                    return -1; // Return -1 to indicate incorrect guess
                }
            }
        }
    }
    if (event.type == Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == Mouse::Left)
        {
			Vector2f mousePos = Vector2f(event.mouseButton.x, event.mouseButton.y);
            for (int i = 0; i < 26; i++)
            {
                if (keys[i].getGlobalBounds().contains(mousePos) && !isGuessed[i])
                {
					isGuessed[i] = true; // Mark letter as guessed
					char guessedLetter = 'A' + i;
					bool correct = false;

					// Check for correct guesses and update word display
                    for (size_t i = 0; i < word.length(); ++i)
                    {
                        if (toupper(word[i]) == guessedLetter)
                        {
                            currentGuess[i] = guessedLetter;
							wordDisplay[i].setString(std::string(1, guessedLetter)); // Reveal letter
							correct = true;
							score += 10; // Increment score for correct guess
						}
					}

					// Change key color based on correct or incorrect guess
                    if (correct)
                    {
						keys[i].setFillColor(Color::Green); // Set key color to green for correct guess
						return 1; // Return 1 to indicate correct guess
					}
                    else
                    {
						keys[i].setFillColor(Color::Red); // Set key color to red for incorrect guess
						--lives; // Decrement lives on incorrect guess
						return -1; // Return -1 to indicate incorrect guess
					}
				}
			}
		}
	}
}


// Draw the keyboard and word display
void KeyboardHandler::draw(RenderWindow& window) 
{
    // Draw each key and its corresponding text
    for (int i = 0; i < 26; i++) 
    {
        window.draw(keys[i]);
        window.draw(keyTexts[i]);
    }

    // Draw word display (revealed letters or underscores)
    for (size_t i = 0; i < word.length(); i++) 
    {
        window.draw(wordDisplay[i]);
    }
}

// Handles mouse hover effect on keys (for visual feedback)
void KeyboardHandler::handleMouseHover(Vector2f mousePos) 
{
    for (int i = 0; i < 26; i++) 
    {
        if (keys[i].getGlobalBounds().contains(mousePos) && !isGuessed[i]) 
        {
            keys[i].setFillColor(Color(200, 200, 200)); // Light gray when hovere
        }
        else if (!isGuessed[i]) 
        {
            keys[i].setFillColor(Color::White); // Reset to default
        }
    }

}

// Reveal one character in the word (Hint system)
void KeyboardHandler::revealHint(int& score,Vector2f mousePos,RectangleShape hintButton, bool& hintUsed)
{
    if (hintButton.getGlobalBounds().contains(mousePos))
    {
        
        if (hintUsed) return; // Only one hint per game

        hintUsed = true;
        char unrevealedLetters[26] = { 0 };
        int unrevealedCount = 0;

        for (size_t i = 0; i < word.length(); i++)
        {
            if (wordDisplay[i].getString() == "_")
            {
                char unrevealedLetter = toupper(word[i]);
                bool alreadyAdded = false;
                for (int j = 0; j < unrevealedCount; ++j)
                {
                    if (unrevealedLetters[j] == unrevealedLetter)
                    {
                        alreadyAdded = true;
                        break;
                    }
                }
                if (!alreadyAdded)
                {
                    unrevealedLetters[unrevealedCount++] = unrevealedLetter;
                }
            }
        }

        if (unrevealedCount > 0)
        {
            // Randomly pick an unrevealed letter and update the word display
            srand(static_cast<unsigned int>(time(0)));
            char randomLetter = unrevealedLetters[rand() % unrevealedCount];
            for (size_t i = 0; i < word.length(); ++i)
            {
                if (toupper(word[i]) == randomLetter)
                {
                    wordDisplay[i].setString(std::string(1, randomLetter)); 
                    score += 5; 
                }
            }
            char hintLetter = toupper(randomLetter);
            
            for (int i = 0; i < 26; ++i)
            {
                if (keyLetters[i] == hintLetter)
                {
					isGuessed[i] = true;
					keys[i].setFillColor(Color::Yellow); 
					break;
				}
			}
        }
    }
  
}


void KeyboardHandler::reset()
{
    for (int i = 0; i < 26; i++)
    {
		isGuessed[i] = false;
		keys[i].setFillColor(Color::White);
	}

    for (size_t i = 0; i < word.length(); i++)
    {
		wordDisplay[i].setString("_");
	}
}