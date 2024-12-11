#include "Food.h"

Food::Food() :isBonusFood(false)
{
	foodTexture.loadFromFile("../Textures/food.png");
    foodSprite.setTexture(foodTexture);

    bonusFoodTexture.loadFromFile("../Textures/BonusFood.png");
    bonusFoodSprite.setTexture(bonusFoodTexture);

	generateFood(nullptr, 0);
}


bool Food::bonusFoodCollision(const int snake[][2], int snakeLength) 
{
    int snakeHeadX = snake[0][0];
    int snakeHeadY = snake[0][1];

    // Check if snake head intersects bonus food area (100x100)
    if (snakeHeadX >= bonusFood[0] && snakeHeadX <= bonusFood[0] + 3 &&
        snakeHeadY >= bonusFood[1] && snakeHeadY <= bonusFood[1] + 3) 
    {
        return true;
    }
    return false;
}

void Food::drawFood(sf::RenderWindow& window) 
{
    if (isBonusFood) 
    {
        bonusFoodSprite.setPosition(bonusFood[0] * boxSize, bonusFood[1] * boxSize);
        window.draw(bonusFoodSprite);
    }
    
        foodSprite.setPosition(food[0] * boxSize, food[1] * boxSize);
        window.draw(foodSprite);
}

void Food::generateFood(const int snake[][2], int snakeLength)
{
    bool validPosition;
    do {
        validPosition = true;
        food[0] = 1 + rand() % (columns - 1);
        food[1] = 5 + rand() % (rows - 6);

        // Ensure food doesn't spawn on the snake
        for (int i = 0; i < snakeLength; ++i) {
            if (snake[i][0] == food[0] && snake[i][1] == food[1]) {
                validPosition = false;
                break;
            }
        }
    } while (!validPosition);
}

void Food::setBonusFood() 
{
    bonusFood[0] = 1 + rand() % (columns - 4);
    bonusFood[1] = 5 + rand() % (rows - 9);
    isBonusFood = true; 
}