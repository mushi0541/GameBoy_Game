#include "Player.h"
#include <iostream>
#include <fstream>

using namespace std;

Player::Player() : snakeHighScore(0), hangmanHighScore(0), wordleHighScore(0) {}


void Player::loadHighScores() 
{
    string filename = "../PlayerScores/"+ name + ".txt";
    ifstream inFile(filename);

    if (inFile) 
    {
        
        inFile >> snakeHighScore;
        inFile >> hangmanHighScore;
        inFile >> wordleHighScore;
        inFile.close();
        cout << "High scores loaded for " << name << "!" << endl;
    }
    else 
    {
        cout << "No existing high scores found for " << name << ", initializing with default scores." << endl;
        snakeHighScore = 0;
        hangmanHighScore = 0;
        wordleHighScore = 0;

        saveHighScores();
    }
}

// Save the high scores to a file
void Player::saveHighScores() 
{
    string filename = "../PlayerScores/" + name + ".txt";
    ofstream outFile(filename);

    if (outFile) 
    {
        outFile << snakeHighScore << endl;
        outFile << hangmanHighScore << endl;
        outFile << wordleHighScore << endl;
        outFile.close();
        cout << "High scores saved for " << name << "!" << endl;
    }
    else 
    {
        cout << "Failed to save the high scores for " << name << "." << endl;
    }
}

// Update the high score for a specific game
void Player::updateHighScore(int newScore, const string& gameName) 
{
    if (gameName == "Snake") 
    {
        if (newScore > snakeHighScore) 
        {
            snakeHighScore = newScore;
            cout << "New high score for Snake: " << snakeHighScore << endl;
        }
    }
    else if (gameName == "HangMan") 
    {
        if (newScore > hangmanHighScore) 
        {
            hangmanHighScore = newScore;
            cout << "New high score for Hangman: " << hangmanHighScore << endl;
        }
    }
    else if (gameName == "Wordle") 
    {
        if (newScore > wordleHighScore) 
        {
            wordleHighScore = newScore;
            cout << "New high score for Wordle: " << wordleHighScore << endl;
        }
    }

    saveHighScores();
}


void Player::displayHighScores() const 
{
    cout << "High Scores for " << name << ":" << endl;
    cout << "Snake: " << snakeHighScore << endl;
    cout << "Hangman: " << hangmanHighScore << endl;
    cout << "Wordle: " << wordleHighScore << endl;
}
