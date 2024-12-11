#include "HangMan.h"

HangMan::HangMan(RenderWindow& gameWindow,Player& player) : window(gameWindow), Menu(gameWindow), wordManager("../HangMan/Words.txt"),player(player)
{
	font.loadFromFile("../Font2/arial.ttf");
    font2.loadFromFile("../Font2/Category.ttf");
    bgMusic.loadFromFile("../Sound/bgMusic3.wav");
	lives = 6;
	score = 0;
	isGameOver = false;
	isGameWon = false;
	isGamePaused = false;
	isHintUsed = false;
	word = wordManager.getRandomWord();
    category = wordManager.category;
	render();
}

void HangMan::render()
{
	if (!aliveHeartTexture.loadFromFile("../HangMan/Heart.png") || !deadHeartTexture.loadFromFile("../HangMan/Dead.png"))
	{
		return;
	}

	for (int i = 0; i < 6; i++)
	{
		heartSprites[i].setTexture(aliveHeartTexture);
		heartSprites[i].setPosition(50 + i * 90, 20);
	}

	for (int i = 0; i < 6; i++)
	{
		if (!hangmanTextures[i].loadFromFile("../HangMan/Stage" + to_string(i) + ".png"))
		{
			return;
		}
	}

	for (int i = 0; i < 6; i++)
	{
		hangmanSprites[i].setTexture(hangmanTextures[i]);
		hangmanSprites[i].setPosition(50, 200);
	}

	for (int i = 0; i < word.length(); i++)
	{
		wordDisplay[i].setFont(font);
		wordDisplay[i].setCharacterSize(32);
		wordDisplay[i].setFillColor(sf::Color::Black);
		wordDisplay[i].setString(currentGuess[i]);
		wordDisplay[i].setPosition(500 + i * 40, 550);
	}

	hintButton.setSize(sf::Vector2f(100, 40));
	hintButton.setPosition(850, 150);
	hintButton.setFillColor(sf::Color::Yellow);
	hintButton.setOutlineThickness(0); // No border initially
	hintButton.setOutlineColor(sf::Color::Black); // Border color

	hintButtonText.setFont(font);
	hintButtonText.setCharacterSize(30);
	hintButtonText.setString("Hint");
	hintButtonText.setPosition(875, 151);
	hintButtonText.setFillColor(Color::Black);

    //Size of Box should be according to the category
    float width = category.length() * 20;
    CategoryBox.setSize(sf::Vector2f(width, 40));
    //Position of Box should be according to the category
    float x = 890 - width/1.65;
    CategoryBox.setPosition(x, 200);
    CategoryBox.setFillColor(sf::Color::Green);
    CategoryBox.setOutlineThickness(0); // No border initially
    CategoryBox.setOutlineColor(sf::Color::Black); // Border color
    CategoryText.setFont(font2);
    CategoryText.setCharacterSize(30);
    CategoryText.setString(category);
    CategoryText.setPosition(x+10, 202);
    CategoryText.setFillColor(Color::Black);
    
    for (int i = 0; i < word.length(); i++)
        currentGuess += '_';
}

void HangMan::handleGameLoop()
{
    while (window.isOpen())
    {
        bool isContinue = false;
        bool isPauseExit = false;
        
        KeyboardHandler keyboardHandler(font, word,lives,wordDisplay);

        sf::Event event;

        while (window.isOpen())
        {
            // Poll events
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                //saving game
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num1)
                {
                    string filename = "../HangManSaves/" + player.name + ".txt";
                    saveGame(filename);
                }
                //loading game 
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num2)
				{
                    string filename = "../HangManSaves/" + player.name + ".txt";
					loadGame(filename);
                    keyboardHandler.reset();
				}

                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                {
                    int result = Menu.pauseMenu();
                    if (result == 0) // Resume game
                    {

                    }
                    else if (result == 1) // Exit game
                    {
                        isPauseExit = true;
                        break;
                    }
                }


                if (!isGameOver)
                {
                    Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    // Handle mouse hover effect on keyboard
                    if (event.type == Event::MouseMoved)
                    {
                        keyboardHandler.handleMouseHover(Vector2f(event.mouseMove.x, event.mouseMove.y));
                    }

                    if (hintButton.getGlobalBounds().contains(mousePos))
                    {
                        hintButton.setOutlineThickness(5); // Highlight the border
                        hintButton.setOutlineColor(sf::Color::Red); // Change the border color
                    }
                    else
                    {
                        hintButton.setOutlineThickness(0); // Remove the border when the mouse moves away
                    }

                    // Handle hint button click or key press
                    if (event.type == Event::MouseButtonPressed)
                    {
                        keyboardHandler.revealHint(score, mousePos, hintButton, isHintUsed);
                        hintButton.setFillColor(sf::Color::Red);
                    }

                    // Handle keyboard input via KeyboardHandler
                    int a = keyboardHandler.handleInput(event, score, currentGuess);
                    if (a == -1)
                        heartSprites[lives].setTexture(deadHeartTexture);
                    // Check if all letters in the word have been revealed (win condition)
                    bool allRevealed = true;
                    for (int i = 0; i < word.length(); ++i)
                    {
                        if (wordDisplay[i].getString() == "_")
                        {
                            allRevealed = false;
                            break;
                        }
                    }

                    if (allRevealed)
                    {
                        isGameOver = true;
                        isGameWon = true;
                    }
                }
            }

            // If the game is not over, handle input and update the game state

            if (isPauseExit)
            {
				isContinue = false;
				break;
			}
            window.clear(sf::Color::White);

            // Draw hearts (remaining lives)
            for (int i = 0; i < 6; ++i) {
                window.draw(heartSprites[i]);
            }

            // Draw the hangman state if the player has lost lives
            if (lives < 6) {
                window.draw(hangmanSprites[6 - lives - 1]);
            }

            for (int i = 5; i > lives; i--)
            {
                heartSprites[i].setTexture(deadHeartTexture);
            }

            // Draw the word display (revealed letters or underscores)
            for (int i = 0; i < word.length(); ++i) {
                window.draw(wordDisplay[i]);
            }

            // Draw the keyboard
            keyboardHandler.draw(window);

            // Draw hint button and text
            window.draw(hintButton);
            window.draw(hintButtonText);

            // Draw category box and text
            window.draw(CategoryBox);
            window.draw(CategoryText);

            // Draw the score
            sf::Text scoreText("Score: " + to_string(score), font, 35);
            scoreText.setFillColor(sf::Color::Black);
            scoreText.setPosition(730, 37); 
            window.draw(scoreText);

            if (lives == 0)
            {
                isGameOver = true;
                isGameWon = false;
            }
            window.display();


            if (isGameOver)
            {
                if (!isGameWon)
                {
                    sleep(seconds(2));
                    int choice = Menu.GameOverMenu(word);
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

void HangMan::ContinueGame()
{
	isGameOver = false;
	isGameWon = false;
	isGamePaused = false;
	isHintUsed = false;
	word = wordManager.getRandomWord();
    category = wordManager.category;
    currentGuess = "";
    for(int i=0;i<word.length();i++)
		currentGuess+= '_';
	lives = 6;
    render();
}


void HangMan::PlayAgain()
{
   
	isGameOver = false;
	isGameWon = false;
	isGamePaused = false;
	isHintUsed = false;
	word = wordManager.getRandomWord();
    category = wordManager.category;
    currentGuess = "";
    for (int i = 0; i < word.length(); i++)
        currentGuess += '_';
	lives = 6;
	score = 0;
    render();
}


void HangMan::startGame()
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


// Save the game state to a file
void HangMan::saveGame(const string& filename)
{
    ofstream outFile(filename);
    if (!outFile)
    {
        cerr << "Failed to open file for saving!" << endl;
        return;
    }

    outFile << word << endl;

    outFile << wordManager.category << endl; 

    outFile << score << endl;

    outFile << lives << endl;

    outFile << (isGameOver ? 1 : 0) << endl;

    outFile << (isGameWon ? 1 : 0) << endl;

    outFile << (isHintUsed ? 1 : 0) << endl;

    for (int i = 0; i < word.length(); ++i)
    {
        outFile << currentGuess[i];  
    }
    outFile << endl;  

    
    outFile.close();
    cout << "Game saved successfully!" << endl;
}

//load the saved game
void HangMan::loadGame(const string& filename)
{
    ifstream inFile(filename);
    if (!inFile)
    {
        cerr << "Failed to open file for loading!" << endl;
        return;
    }

    getline(inFile, word);

    getline(inFile, category);  

    inFile >> score;
    inFile.ignore();  // To skip the newline after reading the score

    inFile >> lives;
    inFile.ignore();  

    int gameOverStatus;
    inFile >> gameOverStatus;
    isGameOver = (gameOverStatus == 1);
    inFile.ignore();  

    int gameWonStatus;
    inFile >> gameWonStatus;
    isGameWon = (gameWonStatus == 1);
    inFile.ignore(); 

    int hintUsedStatus;
    inFile >> hintUsedStatus;
    isHintUsed = (hintUsedStatus == 1);
    inFile.ignore();  

    currentGuess.clear();
    for (int i = 0; i < word.length(); ++i)
    {
        char ch;
        inFile >> ch;
        currentGuess += ch;  
    }
    inFile.ignore(); 


    inFile.close();
    cout << "Game loaded successfully!" << endl;

    render();
}
