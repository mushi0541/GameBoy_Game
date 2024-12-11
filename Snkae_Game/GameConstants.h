#ifndef GAMECONSTANTS_H
#define GAMECONSTANTS_H

class GameConstants {
public:
    // Resolution of the game window
    static const int resolutionX = 960;
    static const int resolutionY = 960;

    // Grid size and max snake length
    static const int boxSize = 32;
    static const int rows = resolutionX / boxSize;
    static const int columns = resolutionY / boxSize;
    static const int maxSnakeLength = rows * columns;

    // Maximum number of high scores to store
    static const int maxHighScores = 100;
};

#endif 