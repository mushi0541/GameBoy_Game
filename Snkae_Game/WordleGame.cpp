#include "WordleGame.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

using namespace std;
using namespace sf;

WordleGame::WordleGame(RenderWindow& gameWindow,Player& player) : window(gameWindow), Menu(gameWindow), wordManager("../Wordle/Words.txt"), gridSystem(font), player(player)
{
	font.loadFromFile("../Font2/arial.ttf");
    keyPressSound.loadFromFile("../Sound/Key.wav");
    bgMusic.loadFromFile("../Sound/bgMusic4.wav");
    name = "Wordle";
    score = 0;
	render();
}

void WordleGame::render() 
{
	SetBackGround.loadFromFile("../Wordle/bgImg.jpg");
	BackGround.setTexture(SetBackGround);
	targetWord = wordManager.getRandomWord();
	currentRow = 0;
	currentGuess = "";
	feedback = "";
	lives = 6;
	isGameOver = false;
	isGameWon = false;
	isGamePaused = false;
}


void WordleGame::handleGameLoop()
{
    while (window.isOpen())
    {
        cout<<targetWord<<endl;
        bool isContinue = false;
        bool isPauseExit = false;
         
        Event event;

        WordleKeyboardHandler keyboardHandler(font, targetWord, lives);
        while (window.isOpen())
        {
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    window.close();
                }

                if(event.type == Event::KeyPressed && event.key.code == Keyboard::Num1)
				{
                    string filename = "../WordleSaves/" + player.name +".txt";
					saveGame(filename);
				}

                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num2)
                {
                    string filename = "../WordleSaves/" + player.name + ".txt";
                    loadGame(filename);
                }

                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                {
                    keyPressSound.play();
                    int choice = Menu.pauseMenu();
                    keyPressSound.play();
                    if (choice == 0)
                    {
                        //Resume game

                    }
                    else if (choice == 1)
                    {
                        //Restart game
                        PlayAgain();
                        keyboardHandler.reset();
                    }
                    else if (choice == 2)
                    {
                        isPauseExit = true;
                        break;
                    }
                }

                // Handle input through keyboard or mouse
                string feedback = "";
                bool completed = keyboardHandler.handleInput(event, currentGuess, currentRow, feedback);

                // If a guess is completed
                if (completed && !isGameOver)
                {
                    for (int i = 0; i < 5; ++i)
                    {
                        Color boxColor;
                        if (feedback[i] == 'G')
                        {
                            boxColor = Color::Green; // Correct letter, correct position
							score += 10;

                        }
                        else if (feedback[i] == 'Y')
                        {
                            boxColor = Color::Yellow;
                            score += 5;

                        }
                        else boxColor = Color::Red; // Incorrect letter

                        gridSystem.updateBox(currentRow, i, currentGuess[i], boxColor);
                    }



                    currentRow++;
                    currentGuess = "";

                    if (feedback == "GGGGG")
                    {
                        isGameOver = true;
                        isGameWon = true;
                        score += 50;
                        break;
                    }

                    if (currentRow == 6)
                    {

                        isGameOver = true;
                        isGameWon = false;
                        break;
                    }
                }

                if (!completed &&!isGameOver)
                {
                    for (int i = 0; i < 5; i++)
                    {
                        if (i < currentGuess.length())
                        {
                            gridSystem.updateBox(currentRow, i, currentGuess[i], Color(200, 200, 200));
                        }
                        else
                        {
                            gridSystem.updateBox(currentRow, i, ' ', Color::Transparent);
                        }
                    }
                }
            }

            if (isPauseExit)
            {
                isContinue = false;
                break;
            }

           
            window.draw(BackGround);
            gridSystem.draw(window);
            keyboardHandler.draw(window);

            Text ScoreText;
            Font scoreFont;
            scoreFont.loadFromFile("../Font2/Category.ttf");
            ScoreText.setFont(scoreFont);
            ScoreText.setCharacterSize(45);
            ScoreText.setFillColor(Color::Black);
            ScoreText.setPosition(600, 50);
            ScoreText.setString("Score: " + to_string(score));
            window.draw(ScoreText);

            window.display();


            if (isGameOver)
            {
                if (!isGameWon)
                {
                    sleep(seconds(2));
                    int choice = Menu.GameOverMenu(targetWord);
                    if (choice == 0)
                    {
                        PlayAgain();
                        keyboardHandler.reset();
                    }
                    if (choice == 1)
                    {
                        break;
                    }
                }

                if (isGameWon)
                {
                    sleep(seconds(2));
                    int choice = Menu.GameWonMenu();
                    if (choice == 0)
                    {
                        ContinueGame();
                        isContinue = true;
                        keyboardHandler.reset();
                    }
                    if (choice == 1)
                    {
                        break;
                    }
                }
            }

        }

        if (!isContinue)
        {
			break;
		}

    }
}

void WordleGame::startGame()
{
    int tempHighScore = 0;
    while (window.isOpen())
    {
        bgMusic.play();
        bgMusic.setLoop(true);
        bgMusic.setVolume(30);
        render();
        PlayAgain();
        int choice = Menu.handleMenuLoop();

        if (choice == -1 || choice == 2)
        {
            bgMusic.stop();
            break;
        } 

        handleGameLoop();

        if (score > tempHighScore)
        {
			tempHighScore = score;
		}
	}
    score = tempHighScore;
}


void WordleGame::ContinueGame()
{
    isGameOver = false;
    isGameWon = false;
    isGamePaused = false;
    targetWord = wordManager.getRandomWord();
    lives = 6;
    currentGuess = "";
    feedback = "";
    render();
    gridSystem.reset();
}

void WordleGame::PlayAgain()
{
	isGameOver = false;
	isGameWon = false;
	isGamePaused = false;
	targetWord = wordManager.getRandomWord();
	lives = 6;
    score = 0;
	currentGuess = "";
	feedback = "";
	render();
    gridSystem.reset();
}


void WordleGame::saveGame(const string& filename) 
{
    ofstream outFile(filename);
    if (!outFile.is_open()) 
    {
        cerr << "Failed to open save file!" << endl;
        return;
    }

    // Save basic game state
    outFile << targetWord << endl;
    outFile << currentGuess << endl;
    outFile << currentRow << endl;
    outFile << lives << endl;
    outFile << score << endl;
    outFile << isGameOver << endl;
    outFile << isGameWon << endl;
    outFile << isGamePaused << endl;

    // Save grid system data (content and colors)
    for (int row = 0; row < 6; ++row) 
    {
        for (int col = 0; col < 5; ++col) 
        {
            char content;
            Color color;
            gridSystem.getBoxData(row, col, content, color); // Assume `getBoxData` retrieves data from the grid
            outFile << content << " " << color.toInteger() << endl;
        }
    }

    outFile.close();
    cout << "Game saved successfully!" << endl;
}


void WordleGame::loadGame(const string& filename) 
{
    ifstream inFile(filename);
    if (!inFile.is_open()) 
    {
        cerr << "Failed to open save file!" << endl;
        return;
    }

    // Load basic game state
    getline(inFile, targetWord);
    getline(inFile, currentGuess);
    inFile >> currentRow >> lives >> score;
    inFile >> isGameOver >> isGameWon >> isGamePaused;

    // Clear any existing grid system data
    gridSystem.reset();

    // Load grid system data (content and colors)
    for (int row = 0; row < 6; ++row) 
    {
        for (int col = 0; col < 5; ++col) 
        {
            char content;
            unsigned int colorInt;
            inFile >> content >> colorInt;
            Color color(colorInt); 
            gridSystem.updateBox(row, col, content, color);
        }
    }

    inFile.close();
    cout << "Game loaded successfully!" << endl;
}

