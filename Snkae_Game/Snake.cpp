#include "Snake.h"

Snake::Snake()
    : snakeLength(2), growing(false),
    headUp("../Textures/head_up.png"), headDown("../Textures/head_down.png"),
    headLeft("../Textures/head_left.png"), headRight("../Textures/head_right.png"),
    bodyHorizontal("../Textures/body_horizontal.png"), bodyVertical("../Textures/body_vertical.png"),
    bodyTL("../Textures/body_tl.png"), bodyTR("../Textures/body_tr.png"),
    bodyBL("../Textures/body_bl.png"), bodyBR("../Textures/body_br.png"),
    tailUp("../Textures/tail_up.png"), tailDown("../Textures/tail_down.png"),
    tailLeft("../Textures/tail_left.png"), tailRight("../Textures/tail_right.png")
{
    headUp.setCoordinates(0, 0);
    headDown.setCoordinates(0, 0);
    headLeft.setCoordinates(0, 0);
    headRight.setCoordinates(0, 0);
    bodyHorizontal.setCoordinates(0, 0);
    bodyVertical.setCoordinates(0, 0);
    bodyTL.setCoordinates(0, 0);
    bodyTR.setCoordinates(0, 0);
    bodyBL.setCoordinates(0, 0);
    bodyBR.setCoordinates(0, 0);
    tailUp.setCoordinates(0, 0);
    tailDown.setCoordinates(0, 0);
    tailLeft.setCoordinates(0, 0);
    tailRight.setCoordinates(0, 0);

    // Initialize snake in the center
    snake[0][0] = columns / 2;
    snake[0][1] = rows / 2;
    direction[0] = 1; // Right
    direction[1] = 0; // No vertical movement
}

void Snake::drawSnake(sf::RenderWindow& window)
{
    // Draw the head
    if (snakeLength > 1) {
        int dx = snake[1][0] - snake[0][0];
        int dy = snake[1][1] - snake[0][1];

        if (dx == 1) {
            headLeft.setCoordinates(snake[0][0] * boxSize, snake[0][1] * boxSize);
            headLeft.Draw(window);
        }
        else if (dx == -1) {
            headRight.setCoordinates(snake[0][0] * boxSize, snake[0][1] * boxSize);
            headRight.Draw(window);
        }
        else if (dy == 1) {
            headUp.setCoordinates(snake[0][0] * boxSize, snake[0][1] * boxSize);
            headUp.Draw(window);
        }
        else if (dy == -1) {
            headDown.setCoordinates(snake[0][0] * boxSize, snake[0][1] * boxSize);
            headDown.Draw(window);
        }
    }

    // Draw the body
    for (int i = 1; i < snakeLength - 1; ++i) {
        int prevX = snake[i - 1][0], prevY = snake[i - 1][1];
        int currX = snake[i][0], currY = snake[i][1];
        int nextX = snake[i + 1][0], nextY = snake[i + 1][1];

        if (prevX == currX && nextX == currX) { // Vertical
            bodyVertical.setCoordinates(currX * boxSize, currY * boxSize);
            bodyVertical.Draw(window);
        }
        else if (prevY == currY && nextY == currY) { // Horizontal
            bodyHorizontal.setCoordinates(currX * boxSize, currY * boxSize);
            bodyHorizontal.Draw(window);
        }
        else if ((prevX < currX && nextY < currY) || (nextX < currX && prevY < currY)) { // Top-left corner
            bodyTL.setCoordinates(currX * boxSize, currY * boxSize);
            bodyTL.Draw(window);
        }
        else if ((prevX > currX && nextY < currY) || (nextX > currX && prevY < currY)) { // Top-right corner
            bodyTR.setCoordinates(currX * boxSize, currY * boxSize);
            bodyTR.Draw(window);
        }
        else if ((prevX < currX && nextY > currY) || (nextX < currX && prevY > currY)) { // Bottom-left corner
            bodyBL.setCoordinates(currX * boxSize, currY * boxSize);
            bodyBL.Draw(window);
        }
        else if ((prevX > currX && nextY > currY) || (nextX > currX && prevY > currY)) { // Bottom-right corner
            bodyBR.setCoordinates(currX * boxSize, currY * boxSize);
            bodyBR.Draw(window);
        }
    }

    // Draw the tail
    if (snakeLength > 1) {
        int dx = snake[snakeLength - 2][0] - snake[snakeLength - 1][0];
        int dy = snake[snakeLength - 2][1] - snake[snakeLength - 1][1];

        if (dx == 1) {
            tailLeft.setCoordinates(snake[snakeLength - 1][0] * boxSize, snake[snakeLength - 1][1] * boxSize);
            tailLeft.Draw(window);
        }
        else if (dx == -1) {
            tailRight.setCoordinates(snake[snakeLength - 1][0] * boxSize, snake[snakeLength - 1][1] * boxSize);
            tailRight.Draw(window);
        }
        else if (dy == 1) {
            tailUp.setCoordinates(snake[snakeLength - 1][0] * boxSize, snake[snakeLength - 1][1] * boxSize);
            tailUp.Draw(window);
        }
        else if (dy == -1) {
            tailDown.setCoordinates(snake[snakeLength - 1][0] * boxSize, snake[snakeLength - 1][1] * boxSize);
            tailDown.Draw(window);
        }
    }
}

void Snake::moveSnake()
{
    // Shift all segments to follow the head
    for (int i = snakeLength - 1; i > 0; --i)
    {
        snake[i][0] = snake[i - 1][0];
        snake[i][1] = snake[i - 1][1];
    }

    // Update the head position based on direction
    snake[0][0] += direction[0];
    snake[0][1] += direction[1];

    // Update the head sprite's position according to the new position
    if (direction[0] == 1) {
        headRight.setCoordinates(snake[0][0] * boxSize, snake[0][1] * boxSize);
    }
    else if (direction[0] == -1) {
        headLeft.setCoordinates(snake[0][0] * boxSize, snake[0][1] * boxSize);
    }
    else if (direction[1] == 1) {
        headDown.setCoordinates(snake[0][0] * boxSize, snake[0][1] * boxSize);
    }
    else if (direction[1] == -1) {
        headUp.setCoordinates(snake[0][0] * boxSize, snake[0][1] * boxSize);
    }

    // Increase length if growing
    if (growing && snakeLength < maxSnakeLength)
    {
        ++snakeLength;
        growing = false;
    }
}

bool Snake::checkCollision(const int food[2])
{
    // Get the position of the snake's head and food's coordinates
    int snakeHeadX = snake[0][0];
    int snakeHeadY = snake[0][1];

    // Check if snake head intersects the food area (1x1)
    return snakeHeadX == food[0] && snakeHeadY == food[1];
}

bool Snake::selfCollision()
{
    for (int i = 1; i < snakeLength; ++i) {
        if (snake[0][0] == snake[i][0] && snake[0][1] == snake[i][1]) {
            return true;
        }
    }
    return false;
}




int Snake::getSnakeLength() const
{
	return snakeLength;
}

void Snake::setDirection(int newDirection[2])
{
	// Ensure the snake can't reverse direction
    if (direction[0] == -newDirection[0] || direction[1] == -newDirection[1]) 
    {
		return;
	}

	direction[0] = newDirection[0];
	direction[1] = newDirection[1];
}

void Snake::growSnake()
{
	growing = true;
}