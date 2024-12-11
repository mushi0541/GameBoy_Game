#ifndef LEADER_H
#define LEADER_H

#include <string>
#include <fstream>
#include "Player.h"
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

class Leader 
{
public:
    void updateLeaderboard(const Player& player);
    void displayLeaderboard(RenderWindow& window, Sprite& leaderboardSprite);
private:
    struct LeaderboardEntry 
    {
        string name;
        int snakeScore;
        int hangmanScore;
        int wordleScore;
        int totalScore;

        LeaderboardEntry() : name(""), snakeScore(0), hangmanScore(0), wordleScore(0), totalScore(0) {}
        LeaderboardEntry(const string& playerName, int snake, int hangman, int wordle)
            : name(playerName), snakeScore(snake), hangmanScore(hangman), wordleScore(wordle) {
            totalScore = snake + hangman + wordle;
        }
    };

    static const int MAX_ENTRIES = 7; // Maximum number of leaderboard entries
    static const string leaderboardFile;

    void readLeaderboard(LeaderboardEntry leaderboard[], int& count);
    void writeLeaderboard(const LeaderboardEntry leaderboard[], int count);
    void sortLeaderboard(LeaderboardEntry leaderboard[], int count);
};

#endif // LEADER_H
