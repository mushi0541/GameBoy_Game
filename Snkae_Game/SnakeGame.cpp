#include "SnakeGame.h"
#pragma once

SnakeGame::SnakeGame(RenderWindow& window, Player& player)
    :window(window), regularFoodEaten(0), growing(false), gameOver(false),gameMenuHandler(window),player(player)
{

    srand(static_cast<unsigned>(time(0)));
    render();
}

void SnakeGame::render()
{
    bonusCountdownTextures[0].loadFromFile("../Textures/5sec5.png");
    bonusCountdownTextures[1].loadFromFile("../Textures/4sec4.png");
    bonusCountdownTextures[2].loadFromFile("../Textures/3sec3.png");
    bonusCountdownTextures[3].loadFromFile("../Textures/2sec2.png");
    bonusCountdownTextures[4].loadFromFile("../Textures/1sec1.png");

    for (int i = 0; i < 5; i++)
    {
        bonusCountdownSprites[i].setTexture(bonusCountdownTextures[i]);
        bonusCountdownSprites[i].setPosition(780, 0);
    }

    backgroundTexture.loadFromFile("../Textures/newbg.jpeg");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0, 0);

    if (!Buffer.loadFromFile("../Sound/eat.wav")) {
        cout << "Failed to load sound!" << endl;
        exit(-1);
    }
    eatSound.setBuffer(Buffer);
    eatSound.setPitch(2.0f);

    bgMusic.loadFromFile("../Sound/bgMusic2.wav");

    font.loadFromFile("../Font2/font1.otf");
}

void SnakeGame::initialize()
{
    // Initialize game variables
    snake.snake[0][0] = columns / 2;
    snake.snake[0][1] = rows / 2;
    snake.direction[0] = 1;
    snake.direction[1] = 0;
    snake.snakeLength = 2;
    growing = false;
    score = 0;
    regularFoodEaten = 0;
}

// Draw Score
void SnakeGame::drawScore()
{
    Text scoreText(to_string(score), font, 60);
    scoreText.setFillColor(Color::Black);
    scoreText.setOutlineColor(Color::White);
    scoreText.setPosition(70, 60);
    window.draw(scoreText);
}
void SnakeGame::infinityCollision()
{
    if (snake.snake[0][0] < 0) snake.snake[0][0] = columns - 1;
    if (snake.snake[0][0] >= columns) snake.snake[0][0] = 0;
    if (snake.snake[0][1] < 5) snake.snake[0][1] = rows - 1;
    if (snake.snake[0][1] >= rows) snake.snake[0][1] = 5;
}
void SnakeGame::startGame()
{
    render();

    int tempHighScore = 0;
    while (window.isOpen())
    {
        bgMusic.play();
        bgMusic.setLoop(true);
        bgMusic.setVolume(30);
        initialize();
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) window.close();
            if (event.type == Event::KeyPressed) handleInput(event.key.code);
        }

        int gotoGameBoy = gameMenuHandler.handleMenuLoop();
        if (gotoGameBoy == -1 || gotoGameBoy == 3)
        {
            bgMusic.stop();
            break;
        }

        innerLoop();
        if (tempHighScore < score)
        {
			tempHighScore = score;
		}
        draw();
    }
    score = tempHighScore;
}

void SnakeGame::handleInput(Keyboard::Key key)
{
    if (key == Keyboard::Up && snake.direction[1] != 1)
    {
        snake.direction[0] = 0; snake.direction[1] = -1;
    }
    else if (key == Keyboard::Down && snake.direction[1] != -1)
    {
        snake.direction[0] = 0; snake.direction[1] = 1;
    }
    else if (key == Keyboard::Left && snake.direction[0] != 1)
    {
        snake.direction[0] = -1; snake.direction[1] = 0;
    }
    else if (key == Keyboard::Right && snake.direction[0] != -1)
    {
        snake.direction[0] = 1; snake.direction[1] = 0;
    }
}

void SnakeGame::draw()
{
    window.clear();
    // Draw background, snake, food, score, etc.
    window.display();
}

int SnakeGame::innerLoop()
{
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }


            if(event.type == Event::KeyPressed && event.key.code == Keyboard::S)
			{
                string filename = "../SnakeSaves/" + player.name + ".txt";
				saveGame(filename);
			}

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::L)
            {
                string filename = "../SnakeSaves/" + player.name + ".txt";
                loadGame(filename);
                
            }


            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                // Pause the game and freeze the timers

                //Store the current elaspesd time of a bonus food in a variable
                float bonusFoodTime = bonusFoodTimer.getElapsedTime().asSeconds();
                keyPressedSound.play();
                int pauseOption = gameMenuHandler.pauseMenu();

                if (pauseOption == -11)
                {
                    bonusFoodTimer.restart();
                    keyPressedSound.play();
                    continue;
                }
                else if (pauseOption == 0)
                {
                    bonusFoodTimer.restart();
                    keyPressedSound.play();
                    break;
                }
                else if (pauseOption == 1)
                {
                    initialize();
                    break ;

                }
                else if (pauseOption == 2)
                {
                    keyPressedSound.play();
                    initialize();
                    return 1;
                }

            }
        }

        // Input Handling
        bool keyPressed = false;  // Flag to track if a key press is being processed

        if (Keyboard::isKeyPressed(Keyboard::Up) && !keyPressed && !(snake.direction[0] == 0 && snake.direction[1] == 1)) {
            snake.direction[0] = 0;
            snake.direction[1] = -1;
            keyPressed = true;  // Mark key as processed
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down) && !keyPressed && !(snake.direction[0] == 0 && snake.direction[1] == -1)) {
            snake.direction[0] = 0;
            snake.direction[1] = 1;
            keyPressed = true;  // Mark key as processed
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left) && !keyPressed && !(snake.direction[0] == 1 && snake.direction[1] == 0)) {
            snake.direction[0] = -1;
            snake.direction[1] = 0;
            keyPressed = true;  // Mark key as processed
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) && !keyPressed && !(snake.direction[0] == -1 && snake.direction[1] == 0))
        {
            snake.direction[0] = 1;
            snake.direction[1] = 0;
            keyPressed = true;  // Mark key as processed
        }

        // Reset keyPressed flag when no key is pressed
        if (!Keyboard::isKeyPressed(Keyboard::Up) &&
            !Keyboard::isKeyPressed(Keyboard::Down) &&
            !Keyboard::isKeyPressed(Keyboard::Left) &&
            !Keyboard::isKeyPressed(Keyboard::Right)) {
            keyPressed = false;  // Reset when no key is pressed
        }
        if (clock.getElapsedTime().asSeconds() > gameMenuHandler.snakeSpeed)
        {
            clock.restart();

            // Move the snake
            snake.moveSnake();

            // Check boundary collision or self-collision
            if ((snake.snake[0][0] < 0 || snake.snake[0][0] >= columns || snake.snake[0][1] < 5 || snake.snake[0][1] >= rows || snake.selfCollision()) && gameMenuHandler.classicMode)
            {
                cout << "Classic Mode" << endl;
                Text gameOverText("Collision Detected!", font, 50);
                gameOverText.setFillColor(Color::Red);
                gameOverText.setPosition(resolutionX / 4, resolutionY / 3);
                window.draw(gameOverText); // Show Game Over message
                window.display();
                sleep(seconds(2)); // Pause the game for 2 seconds

                Texture Gameover;
                Gameover.loadFromFile("../Textures/gameover.jpg");
                Sprite Gameoversprite;
                Gameoversprite.setTexture(Gameover);
                Gameoversprite.setPosition(0, 0);
                Gameoversprite.setColor(Color::White);
                window.draw(Gameoversprite);

                window.display();
                sleep(seconds(2));
                highScores.updateHighScores(score);
                highScores.saveHighScores();
                //initialize();
                break;
            }
          
            if ((snake.snake[0][0] < 0 || snake.snake[0][0] >= columns || snake.snake[0][1] < 5 || snake.snake[0][1] >= rows) && gameMenuHandler.infiniteMode)
            {
                infinityCollision();
            }

            if (gameMenuHandler.infiniteMode)
            {
                if (snake.selfCollision())
                {
                    
                    Text gameOverText("Collision Detected!", font, 50);
                    gameOverText.setFillColor(Color::Red);
                    gameOverText.setPosition(resolutionX / 4, resolutionY / 3);
                    window.draw(gameOverText); // Show Game Over message
                    window.display();
                    sleep(seconds(2)); // Pause the game for 2 seconds
                    Texture Gameover;
                    Gameover.loadFromFile("../Textures/gameover.jpg");
                    Sprite Gameoversprite;
                    Gameoversprite.setTexture(Gameover);
                    Gameoversprite.setPosition(0, 0);
                    Gameoversprite.setColor(Color::White);
                    window.draw(Gameoversprite);
                    window.display();
                    sleep(seconds(2));
                    highScores.updateHighScores(score);
                    highScores.saveHighScores();
                    //initialize();
                    
                    break;
                }
            }

            // Check food collision
            if (snake.checkCollision(food.food))
            {
                snake.snakeLength++;
                eatSound.play();
                score += 10;
                growing = true;
                food.generateFood(snake.snake, snake.snakeLength);
                regularFoodEaten++;
                cout << "Regular Food Eaten: " << regularFoodEaten << endl;
                // Trigger bonus food after 5 regular foods
                if (regularFoodEaten >= 5 && !food.isBonusFood)
                {
                    food.setBonusFood();
                    food.generateFood(snake.snake, snake.snakeLength);
                    food.isBonusFood = true;
                    bonusFoodTimer.restart();
                    regularFoodEaten = 0; // Reset counter
                }
            }

            if (food.isBonusFood)
            {
                //Show the Timer on Screen for Bonus Food

                if (bonusFoodTimer.getElapsedTime().asSeconds() > 5.0f)
                {
                    food.isBonusFood = false; // Remove bonus food after 5 seconds
                    bonusFoodTimer.restart();
                }
                else if (food.bonusFoodCollision(snake.snake, snake.snakeLength))
                {
                    eatSound.play();
                    score += 100; // Add 100 points for bonus food
                    growing = true;
                    food.isBonusFood = false; // Deactivate bonus food
                }
            }
        }

        // Render
        window.clear();

        window.draw(backgroundSprite);
        
        snake.drawSnake(window);
        food.drawFood(window);
        drawScore();
        if (food.isBonusFood)
        {
            food.drawFood(window);
            int countdown = static_cast<int>(bonusFoodTimer.getElapsedTime().asSeconds());
            if (countdown < 5)
            {
                window.draw(bonusCountdownSprites[countdown]);
            }

        }
        window.display();

    }
    
    highScores.updateHighScores(score);
    highScores.saveHighScores();
    return 0;
}


void SnakeGame::saveGame(const string& filename) 
{
    ofstream outFile(filename);
    if (!outFile.is_open()) 
    {
        cerr << "Failed to open save file!" << endl;
        return;
    }

    // Save score and other variables
    outFile << score << endl;
    outFile << regularFoodEaten << endl;
    outFile << growing << endl;
    outFile << gameOver << endl;

    // Save snake direction and length
    outFile << snake.direction[0] << " " << snake.direction[1] << endl;
    outFile << snake.snakeLength << endl;

    // Save snake body positions
    for (int i = 0; i < snake.snakeLength; ++i) 
    {
        outFile << snake.snake[i][0] << " " << snake.snake[i][1] << endl;
    }

    outFile.close();
    cout << "Game saved successfully!" << endl;
}


void SnakeGame::loadGame(const string& filename) 
{
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Failed to open save file!" << endl;
        return;
    }

    // Load score and other variables
    inFile >> score;
    inFile >> regularFoodEaten;
    inFile >> growing;
    inFile >> gameOver;

    // Load snake direction and length
    inFile >> snake.direction[0] >> snake.direction[1];
    inFile >> snake.snakeLength;

    // Load snake body positions
    for (int i = 0; i < snake.snakeLength; ++i) {
        inFile >> snake.snake[i][0] >> snake.snake[i][1];
    }

    inFile.close();
    cout << "Game loaded successfully!" << endl;
}

