#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <string>
#include <SFML/Graphics.hpp>
#include "GameConstants.h"
#include "MySprite.h"  // Include the MySprite class
#include <fstream>

class HighScores : public GameConstants
{
public:
    //fstream highScoresFile;     // File stream to read and write high scores

    int highScores[maxHighScores];     // Array to store the high scores
    HighScores();

    // Display high scores using MySprite for better sprite handling
    void displayHighScores(sf::RenderWindow& window, sf::Font& font, Sprite& highScoreSprite);
    void saveHighScores();
    // Update high scores when a new score is achieved
    void updateHighScores(int newScore);
};

#endif // HIGHSCORES_H
