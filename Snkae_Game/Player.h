#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Player 
{
public:
    string name;
    int snakeHighScore;
    int hangmanHighScore;
    int wordleHighScore;

    Player();

    void setName(const string& playerName) { name = playerName; }
    string getName() const { return name; }
    void loadHighScores();
    void saveHighScores();
    void updateHighScore(int newScore, const string& gameName);
    void displayHighScores() const;
};

#endif
