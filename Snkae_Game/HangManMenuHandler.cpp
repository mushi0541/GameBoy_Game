#include "HangManMenuHandler.h"


HangManMenuHandler::HangManMenuHandler(RenderWindow& gameWindow) : window(gameWindow)
{
    keyPressSound.loadFromFile("../Sound/Key.wav");
    font.loadFromFile("../Font2/arial.ttf");
    loadResources();
}

void HangManMenuHandler:: loadResources()
{
    if (!mainMenuTextures[0].loadFromFile("../HangMan/mainMenu1.jpg") ||
        !mainMenuTextures[1].loadFromFile("../HangMan/mainMenu2.jpg") ||
        !mainMenuTextures[2].loadFromFile("../HangMan/mainMenu3.jpg") ||
        !pauseMenuTextures[0].loadFromFile("../HangMan/Resume.jpg") ||
        !pauseMenuTextures[1].loadFromFile("../HangMan/Exit.jpg") ||
        !GameOverMenuTextures[0].loadFromFile("../HangMan/GameOver1.png") ||
        !GameOverMenuTextures[1].loadFromFile("../HangMan/GameOver2.png") ||
        !GameWonMenuTexture[0].loadFromFile("../HangMan/Win1.jpg") ||
        !GameWonMenuTexture[1].loadFromFile("../HangMan/Win2.jpg"))
    {
		return;
	}

    for (int i = 0; i < 3; i++)
    {
		mainMenuSprites[i].setTexture(mainMenuTextures[i]);
	}

    for (int i = 0; i < 2; i++)
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

int HangManMenuHandler::mainMenu()
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

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                return -1;
            }

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Left)
                {
                    keyPressSound.getSound().play();
                    selectedIndex = (selectedIndex - 1 + 3) % 3;
                    
                }
                else if (event.key.code == Keyboard::Right)
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



int HangManMenuHandler::pauseMenu()
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
                if (event.key.code == Keyboard::Left)
                {
                    keyPressSound.play();
                    selectedIndex = (selectedIndex - 1 + 2) % 2; // Navigate up
                }
                else if (event.key.code == Keyboard::Right)
                {
                    keyPressSound.play();
                    selectedIndex = (selectedIndex -1 + 2) % 2; // Navigate down
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


int HangManMenuHandler::handleMenuLoop()
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

        if (selectedOption == 0 ) 
        {
                isGameOn = true;
        }

        if (isGameOn)
        {
            return selectedOption;
        }

        if (selectedOption == 1)
        {
            // Show rules
            showRules();
            keyPressSound.play();
        }

        // Exit game 
        else if (selectedOption == 2)
        {
            return 2;
        }
    }
}


void HangManMenuHandler::showRules()
{

    Texture rulesTexture;
    if (!rulesTexture.loadFromFile("../HangMan/Rules.jpg"))
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

int HangManMenuHandler::GameOverMenu(string word)
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

        Text result("Original Word Was:", font, 55);
        result.setFillColor(Color::Black);
        result.Bold;
        result.setPosition(120, 820);
        window.draw(result);

        // Convert the word to uppercase
        string wordU = word; // Copy the word
        for (size_t i = 0; i < wordU.length(); ++i) {
            if (wordU[i] >= 'a' && wordU[i] <= 'z') {
                wordU[i] -= 32; // Convert to uppercase (ASCII logic)
            }
        }

        // Display the actual word
        Text result1(wordU, font, 55);
        result1.setFillColor(Color::Red);
        result1.Bold;
        result1.setPosition(600, 820);
        window.draw(result1);

		window.display();
	}

	return -1;
}

int HangManMenuHandler::GameWonMenu()
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
		window.draw(GameWonMenuSprite[selectedIndex]);
		window.display();
	}

	return -1;
}