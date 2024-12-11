#include "LeaderBoard.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

const string Leader::leaderboardFile = "../leaderboard.txt";

void Leader::updateLeaderboard(const Player& player)
{
    LeaderboardEntry leaderboard[MAX_ENTRIES];
    int count = 0;

    // Read the existing leaderboard
    readLeaderboard(leaderboard, count);

    bool playerExists = false;
    for (int i = 0; i < count; ++i)
    {
        if (leaderboard[i].name == player.getName())
        {
            playerExists = true;

            // Update scores if the new scores are higher
            leaderboard[i].snakeScore = max(leaderboard[i].snakeScore, player.snakeHighScore);
            leaderboard[i].hangmanScore = max(leaderboard[i].hangmanScore, player.hangmanHighScore);
            leaderboard[i].wordleScore = max(leaderboard[i].wordleScore, player.wordleHighScore);

            // Recalculate total score
            leaderboard[i].totalScore = leaderboard[i].snakeScore +
                leaderboard[i].hangmanScore +
                leaderboard[i].wordleScore;
            break;
        }
    }

    // If the player does not exist, add them to the leaderboard
    if (!playerExists)
    {
        if (count < MAX_ENTRIES)
        {
            leaderboard[count++] = LeaderboardEntry(
                player.getName(),
                player.snakeHighScore,
                player.hangmanHighScore,
                player.wordleHighScore
            );
        }
        else
        {
            // Replace the lowest score if necessary
            int minIndex = 0;
            for (int i = 1; i < count; ++i)
            {
                if (leaderboard[i].totalScore < leaderboard[minIndex].totalScore)
                {
                    minIndex = i;
                }
            }
            int playerTotalScore = player.snakeHighScore + player.hangmanHighScore + player.wordleHighScore;
            if (playerTotalScore > leaderboard[minIndex].totalScore)
            {
                leaderboard[minIndex] = LeaderboardEntry(
                    player.getName(),
                    player.snakeHighScore,
                    player.hangmanHighScore,
                    player.wordleHighScore
                );
            }
        }
    }

  
    sortLeaderboard(leaderboard, count);

    
    writeLeaderboard(leaderboard, count);
    cout << "Leaderboard updated successfully!" << endl;
}


void Leader::readLeaderboard(LeaderboardEntry leaderboard[], int& count)
{
    ifstream inFile(leaderboardFile);
    count = 0;

    if (inFile)
    {
        string line;
        while (getline(inFile, line) && count < MAX_ENTRIES)
        {
            istringstream iss(line);
            string name;
            int snake, hangman, wordle;
            if (iss >> name >> snake >> hangman >> wordle)
            {
                leaderboard[count++] = LeaderboardEntry(name, snake, hangman, wordle);
            }
        }
        inFile.close();
    }
}


void Leader::writeLeaderboard(const LeaderboardEntry leaderboard[], int count)
{
    ofstream outFile(leaderboardFile);
    if (outFile)
    {
        for (int i = 0; i < count; ++i)
        {
            outFile << leaderboard[i].name << " "
                << leaderboard[i].snakeScore << " "
                << leaderboard[i].hangmanScore << " "
                << leaderboard[i].wordleScore << endl;
        }
        outFile.close();
    }
    else
    {
        cerr << "Failed to write to leaderboard file!" << endl;
    }
}


void Leader::sortLeaderboard(LeaderboardEntry leaderboard[], int count)
{
    for (int i = 0; i < count - 1; ++i)
    {
        for (int j = 0; j < count - i - 1; ++j)
        {
            if (leaderboard[j].totalScore < leaderboard[j + 1].totalScore)
            {
                LeaderboardEntry temp = leaderboard[j];
                leaderboard[j] = leaderboard[j + 1];
                leaderboard[j + 1] = temp;
            }
        }
    }
}


void Leader::displayLeaderboard(RenderWindow& window, Sprite& leaderboardSprite)
{
    Font font;
    font.loadFromFile("../Font2/Category.ttf");
    LeaderboardEntry leaderboard[MAX_ENTRIES];
    int count = 0;
    readLeaderboard(leaderboard, count);

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

        
        window.draw(leaderboardSprite);

       
        float startY = 300; 
        for (int i = 0; i < count; ++i)
        {
            float rowY = 0;
            if (i == 0)
            {
                rowY = startY;
			}
            else if(i == 1)
            {
                rowY = startY + 72;
			}
            else if (i == 2)
            {
                rowY = startY + 139;
            }
            else if (i == 3)
            {
                rowY = startY + 204;
            }
            else if (i == 4)
            {
                rowY = startY + 265;
            }
            else if (i == 5)
            {
                rowY = startY + 329;
            }
            else if (i == 6)
            {
                rowY = startY + 393;
            }
            Text nameText(leaderboard[i].name, font, 40);
            nameText.setFillColor(Color::Black);
            nameText.setPosition(180, rowY);
            window.draw(nameText);

            
            Text snakeScoreText(to_string(leaderboard[i].snakeScore), font, 40);
            snakeScoreText.setFillColor(Color::Black);
            snakeScoreText.setPosition(584, rowY); 
            window.draw(snakeScoreText);

            
            Text hangmanScoreText(to_string(leaderboard[i].hangmanScore), font, 40);
            hangmanScoreText.setFillColor(Color::Black);
            hangmanScoreText.setPosition(706, rowY); 
            window.draw(hangmanScoreText);

            
            Text wordleScoreText(to_string(leaderboard[i].wordleScore), font, 40);
            wordleScoreText.setFillColor(Color::Black);
            wordleScoreText.setPosition(827, rowY); 
            window.draw(wordleScoreText);

        }

        window.display();
    }
}


