#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include "MySprite.h"
#include "GameConstants.h"

class Snake : public GameConstants
{
public:
    int snake[maxSnakeLength][2];  // Snake body positions
    int snakeLength;    // Current length of the snake
    int direction[2];   // Direction of movement
    bool growing;       // Flag to check if the snake is growing

    MySprite headUp, headDown, headLeft, headRight;
    MySprite bodyHorizontal, bodyVertical;
    MySprite bodyTL, bodyTR, bodyBL, bodyBR;
    MySprite tailUp, tailDown, tailLeft, tailRight;

public:
    Snake();
    void moveSnake();
    void growSnake();
    virtual void drawSnake(sf::RenderWindow& window);
    bool checkCollision(const int food[2]);
    bool selfCollision();
    int getSnakeLength() const;
    void setDirection(int newDirection[2]);
};

#endif // SNAKE_H
