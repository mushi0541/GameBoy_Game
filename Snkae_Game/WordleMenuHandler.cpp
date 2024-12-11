#include "WordleMenuHandler.h"


WordleMenuHandler::WordleMenuHandler(RenderWindow& gameWindow) : window(gameWindow)
{
    keyPressSound.loadFromFile("../Sound/Key.wav");
    font.loadFromFile("../Font2/arial.ttf");
    loadResources();
}

void WordleMenuHandler::loadResources()
{
    if (!mainMenuTextures[0].loadFromFile("../Wordle/mainMenu1.jpg") ||
        !mainMenuTextures[1].loadFromFile("../Wordle/mainMenu2.jpg") ||
        !mainMenuTextures[2].loadFromFile("../Wordle/mainMenu3.jpg") ||
        !pauseMenuTextures[0].loadFromFile("../Wordle/Resume.jpg") ||
        !pauseMenuTextures[1].loadFromFile("../Wordle/Restart.jpg") ||
        !pauseMenuTextures[2].loadFromFile("../Wordle/Exit.jpg") ||
        !GameOverMenuTextures[0].loadFromFile("../Wordle/GameOver1.jpg") ||
        !GameOverMenuTextures[1].loadFromFile("../Wordle/GameOver2.jpg") ||
        !GameWonMenuTexture[0].loadFromFile("../Wordle/Win1.jpg") ||
        !GameWonMenuTexture[1].loadFromFile("../Wordle/Win2.jpg"))
    {
		//return;
	}

    for (int i = 0; i < 3; i++)
    {
		mainMenuSprites[i].setTexture(mainMenuTextures[i]);
	}

    for (int i = 0; i < 3; i++)
    {
		pauseMenuSprites[i].setTexture(pauseMenuTextures[i]);
	}
    for (int i = 0; i < 2; i++)
    {
		GameOverMenuSprites[i].setTexture(GameOverMenuTextures[i]);
	}
    
    for (int i = 0; i < 2; i++)
    {
		GameWonMenuSprite[i].setTexture(GameWonMenuTexture[i]);
	}
}

int WordleMenuHandler::mainMenu()
{
    int selectedIndex = 0;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed )
            {
                keyPressSound.getSound().play();
                window.close();
                return -1; // Exit game
            }

            if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            {
                return -1;
            }

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Up)
                {
                    keyPressSound.getSound().play();
                    selectedIndex = (selectedIndex - 1 + 3) % 3;
                    
                }
                else if (event.key.code == Keyboard::Down)
                {
                    keyPressSound.getSound().play();
                    selectedIndex = (selectedIndex + 1) % 3;
                }
                else if (event.key.code == Keyboard::Enter)
                {
                    keyPressSound.getSound().play();
                    cout << selectedIndex << endl;
                    return selectedIndex;
                }
            }
        }

        window.clear();
        window.draw(mainMenuSprites[selectedIndex]);
        window.display();
    }

    return -1; 
}



int WordleMenuHandler::pauseMenu()
{
    int selectedIndex = 0;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            {
                return -11; // Exit game
            }

            if (event.type == Event::Closed)
            {
                exit(0); // Exit the game
            }

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Up)
                {
                    keyPressSound.play();
                    selectedIndex = (selectedIndex - 1 + 3) % 3; // Navigate up
                }
                else if (event.key.code == Keyboard::Down)
                {
                    keyPressSound.play();
                    selectedIndex = (selectedIndex + 1 + 3) % 3; // Navigate down
                }
                else if (event.key.code == Keyboard::Enter)
                {
                    keyPressSound.play();
                    return selectedIndex; // Confirm selection
                }
            }
        }

        // Render the pause menu screen
        window.clear();
        pauseMenuSprites[selectedIndex].setColor(Color::White);
        window.draw(pauseMenuSprites[selectedIndex]);
        window.display();
    }
}


int WordleMenuHandler::handleMenuLoop()
{
    while (true)
    {
        bool isGameOn = false;
        
        int selectedOption = mainMenu();
        keyPressSound.play();

        if (selectedOption == -1) 
        {
            return -1;
        }

        //If the user chooses option 0 or 1 (Play Game or Rules)
        if (selectedOption == 0 ) 
        {
                isGameOn = true;
        }

        if (isGameOn)
        {
            return selectedOption;
        }

        // If the user selects 'Exit' from the main menu
        if (selectedOption == 1)
        {
            // Show rules
            showRules();
            keyPressSound.play();
        }

        // Exit game if the user selects option 3
        else if (selectedOption == 2)
        {
            return 2;
        }
    }
}


void WordleMenuHandler::showRules()
{

    Texture rulesTexture;
    if (!rulesTexture.loadFromFile("../Wordle/Rules.jpg"))
    {
        return;
    }
    Sprite rulesSprite(rulesTexture);


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                return;
            }
            if (event.type == Event::Closed)
            {
                exit(0);
            }
        }


        window.clear();
        window.draw(rulesSprite);
        window.display();
    }
}

int WordleMenuHandler::GameOverMenu(string word)
{
	int selectedIndex = 0;

    while (window.isOpen())
    {
		Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            {
				keyPressSound.getSound().play();
				window.close();
				return -1; // Exit game
			}

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Up)
                {
					keyPressSound.getSound().play();
					selectedIndex = (selectedIndex - 1 + 2) % 2;
				}
                else if (event.key.code == Keyboard::Down)
                {
					keyPressSound.getSound().play();
					selectedIndex = (selectedIndex -1 +2) % 2;
				}
                else if (event.key.code == Keyboard::Enter)
                {
					keyPressSound.getSound().play();
					return selectedIndex;
				}
			}
		}

		window.clear();
		window.draw(GameOverMenuSprites[selectedIndex]);

        // Convert the word to uppercase
        string wordU = word; // Copy the word
        for (size_t i = 0; i < wordU.length(); ++i) 
        {
            if (wordU[i] >= 'a' && wordU[i] <= 'z') 
            {
                wordU[i] -= 32; // Convert to uppercase (ASCII logic)
            }
        }

        Font font2;
        font2.loadFromFile("../Font2/Category.ttf");

        Text result1(wordU, font2, 50);
        result1.setFillColor(Color::Black);
        result1.Bold;
        result1.setPosition(590, 890);
        window.draw(result1);
		window.display();
	}

	return -1;
}

int WordleMenuHandler::GameWonMenu()
{
	int selectedIndex = 0;

    while (window.isOpen())
    {
		Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            {
				keyPressSound.getSound().play();
				window.close();
				return -1; // Exit game
			}

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Left)
                {
					keyPressSound.getSound().play();
					selectedIndex = (selectedIndex - 1 + 2) % 2;
				}
                else if (event.key.code == Keyboard::Right)
                {
					keyPressSound.getSound().play();
					selectedIndex = (selectedIndex -1 +2) % 2;
				}
                else if (event.key.code == Keyboard::Enter)
                {
					keyPressSound.getSound().play();
					return selectedIndex;
				}
			}
		}

		window.clear();
		window.draw(GameWonMenuSprite[selectedIndex]);
		window.display();
	}

	return -1;
}