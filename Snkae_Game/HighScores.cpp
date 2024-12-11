#include "HighScores.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

HighScores::HighScores()
{
    ifstream highScoresFile("../SnakeHighScores.txt");
    for (int i = 0; i < maxHighScores; ++i)
    {
		highScores[i] = 0;
	}
    
    if (!highScoresFile)
    {
		cout << "Failed to open high scores file!" << endl;
		return;
	}
    for (int i = 0; i < maxHighScores; ++i)
    {
		highScoresFile >> highScores[i];
	}
    highScoresFile.close();
}

void HighScores::saveHighScores()

{
    ofstream highScoresFile("../SnakeHighScores.txt");
    for (int i = 0; i < maxHighScores; ++i)
    {
		highScoresFile << highScores[i] << endl;
	}
    highScoresFile.close();
}

// Updated displayHighScores to use MySprite
void HighScores::displayHighScores(RenderWindow& window, Font& font, Sprite& highScoreSprite)
{

    HighScores();

    const Color backgroundColor(210, 255, 200);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                return;
            }
            if (event.type == Event::Closed)
            {
                exit(0);
            }
        }

        window.clear(backgroundColor);

        // Draw the background sprite
        window.draw(highScoreSprite);
        // Draw the high scores text
        for (int i = 0; i < 10; ++i)
        {
            string scoreTextStr = (i < 9) ? "0" + to_string(i + 1) + ".  " + to_string(highScores[i])
                : to_string(i + 1) + ".  " + to_string(highScores[i]);

            Text scoreText(scoreTextStr, font, 60);
            scoreText.setFillColor(Color::Black);
            scoreText.setPosition(150, 250 + i * 60);  // Adjust the vertical position
            scoreText.setStyle(Text::Bold);
            window.draw(scoreText);
        }

        window.display();
    }
}

void HighScores:: updateHighScores(int newScore)
{
    // Check if the new score qualifies for the high score list
    for (int i = 0; i < maxHighScores; ++i)
    {
        if (newScore > highScores[i])
        {
            // Shift lower scores down
            for (int j = maxHighScores - 1; j > i; --j)
            {
                highScores[j] = highScores[j - 1];
            }
            highScores[i] = newScore;
            break;
        }
    }
}
