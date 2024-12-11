#ifndef FOOD_H
#define FOOD_H

#include "MySprite.h"
#include "GameConstants.h"
#include <SFML/Graphics.hpp>

class Food : public GameConstants
{
public:
    Texture foodTexture; // Texture for regular food
    Texture bonusFoodTexture; // Texture for bonus food
    Sprite foodSprite; // Sprite for regular food
    Sprite bonusFoodSprite; // Sprite for bonus food
    int food[2];   // Position of regular food
    int bonusFood[2]; // Position of bonus food
    bool isBonusFood;

public:
    Food();
    void drawFood(sf::RenderWindow& window);
    bool bonusFoodCollision(const int snake[][2], int snakeLength);
    void generateFood(const int snake[][2], int snakeLength);
    void setBonusFood();
};

#endif

