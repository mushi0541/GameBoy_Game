#include "GameMenuHandler.h"
#include <iostream>

using namespace std;
using namespace sf;

GameMenuHandler::GameMenuHandler(RenderWindow& gameWindow) :window(gameWindow)
{
    highScores = HighScores();
	keyPressSound.loadFromFile("../Sound/Key.wav");
    font.loadFromFile("../Font2/font1.otf");
    loadResources();
}

void GameMenuHandler::loadResources()
{
    mainMenuTextures[0].loadFromFile("../Textures/menu1.jpeg");
    mainMenuTextures[1].loadFromFile("../Textures/menu2.jpeg");
    mainMenuTextures[2].loadFromFile("../Textures/menu3.jpeg");
    mainMenuTextures[3].loadFromFile("../Textures/menu4.jpeg");

    startMenuTextures[0].loadFromFile("../Textures/start_menu1.jpeg");
    startMenuTextures[1].loadFromFile("../Textures/start_menu2.jpeg");
    startMenuTextures[2].loadFromFile("../Textures/start_menu3.jpeg");

    startModeTextures[0].loadFromFile("../Textures/Classic.jpeg");
    startModeTextures[1].loadFromFile("../Textures/Infinite.jpeg");
    
    HighScoresTexture.loadFromFile("../Textures/HighScores.jpeg");

    pauseMenuTextures[0].loadFromFile("../Textures/Resume.jpeg");
    pauseMenuTextures[1].loadFromFile("../Textures/Restart.jpeg");
    pauseMenuTextures[2].loadFromFile("../Textures/Exit.jpeg");

    pauseMenuSprites[0].setTexture(pauseMenuTextures[0]);
    pauseMenuSprites[1].setTexture(pauseMenuTextures[1]);
    pauseMenuSprites[2].setTexture(pauseMenuTextures[2]);

    pauseMenuSprites[0].setPosition(0, 0);
    pauseMenuSprites[1].setPosition(0, 0);
    pauseMenuSprites[2].setPosition(0, 0);

    mainMenuSprites[0].setTexture(mainMenuTextures[0]);
    mainMenuSprites[1].setTexture(mainMenuTextures[1]);
    mainMenuSprites[2].setTexture(mainMenuTextures[2]);
    mainMenuSprites[3].setTexture(mainMenuTextures[3]);

    startMenuSprites[0].setTexture(startMenuTextures[0]);
    startMenuSprites[1].setTexture(startMenuTextures[1]);
    startMenuSprites[2].setTexture(startMenuTextures[2]);

    startModeSprites[0].setTexture(startModeTextures[0]);
    startModeSprites[1].setTexture(startModeTextures[1]);

    HighScoresSprite.setTexture(HighScoresTexture);

    mainMenuSprites[0].setPosition(0, 0);
    mainMenuSprites[1].setPosition(0, 0);
    mainMenuSprites[2].setPosition(0, 0);
    mainMenuSprites[3].setPosition(0, 0);

    for (int i = 0; i < 4; i++)
    {
        mainMenuSprites[i].setScale(
            static_cast<float>(resolutionX) / mainMenuTextures[i].getSize().x,
            static_cast<float>(resolutionY) / mainMenuTextures[i].getSize().y
        );
	}

    startMenuSprites[0].setPosition(0, 0);
    startMenuSprites[1].setPosition(0, 0);
    startMenuSprites[2].setPosition(0, 0);

    startModeSprites[0].setPosition(0, 0);
    startModeSprites[1].setPosition(0, 0);

    HighScoresSprite.setPosition(0, 0);
  

    snakeSpeed = 0.1f;
    classicMode = false;
    infiniteMode = true;
}

int GameMenuHandler::mainMenu() 
{
    int selectedIndex = 0;

    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed ) 
            {
                keyPressSound.getSound().play();
                window.close();
                return -1; // Exit game
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                keyPressSound.getSound().play();
				return -1; 
            }

            if (event.type == Event::KeyPressed) 
            {
                if (event.key.code == Keyboard::Up) 
                {
                    keyPressSound.getSound().play();
                    selectedIndex = (selectedIndex - 1 + 4) % 4;
                    if (selectedIndex == 0) 
                    {
                        selectedIndex = 3;
                    }
                }
                else if (event.key.code == Keyboard::Down) 
                {
                    keyPressSound.getSound().play();
                    selectedIndex = (selectedIndex + 1) % 4;
                    if (selectedIndex == 0) 
                    {
                        selectedIndex = 1;
                    }
                }
                else if (event.key.code == Keyboard::Enter) 
                {
                    keyPressSound.getSound().play();
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

int GameMenuHandler::pauseMenu()
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
                    selectedIndex = (selectedIndex - 1 + 3) % 3; // up
                }
                else if (event.key.code == Keyboard::Right)
                {
                    keyPressSound.play();
                    selectedIndex = (selectedIndex + 1) % 3; // down
                }
                else if (event.key.code == Keyboard::Enter)
                {
                    keyPressSound.play();
                    return selectedIndex; 
                }
            }
        }

        
        window.clear();
        pauseMenuSprites[selectedIndex].setColor(Color::White);
        window.draw(pauseMenuSprites[selectedIndex]);
        window.display();
    }

}

int GameMenuHandler::startMenu() 
{
    cout << "Start Menu" << endl;
    int selectedIndex = 0;

    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) 
            {
                return -1; // Return to the main menu
            }

            if (event.type == Event::Closed) 
            {
                exit(0); // Exit the game
            }

            if (event.type == Event::KeyPressed) 
            {
                if (event.key.code == Keyboard::Up) 
                {
                    keyPressSound.getSound().play();
                    selectedIndex = (selectedIndex - 1 + 3) % 3; // up
                }
                else if (event.key.code == Keyboard::Down) 
                {
                    keyPressSound.getSound().play();
                    selectedIndex = (selectedIndex + 1) % 3; // down
                }
                else if (event.key.code == Keyboard::Enter) 
                {
                    keyPressSound.getSound().play();
                    return selectedIndex; 
                }
            }
        }

        window.clear();
        window.draw(startMenuSprites[selectedIndex]);
        window.display();
    }

}


int GameMenuHandler::startModeMenu() 
{
    int selectedIndex = 0;
   
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) 
        {
            if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) 
            {
                keyPressSound.getSound().play();
                return -1; // Exit game
            }

            if (event.type == Event::Closed) {
                exit(0);
            }

            if (event.type == Event::KeyPressed) 
            {
                if (event.key.code == Keyboard::Left) 
                {
                    keyPressSound.getSound().play();
                    selectedIndex = (selectedIndex - 1 + 2) % 2; // left
                }
                else if (event.key.code == Keyboard::Right) 
                {
                    keyPressSound.getSound().play();
                    selectedIndex = (selectedIndex + 1) % 2; // right
                }
                else if (event.key.code == Keyboard::Enter) 
                {
                    keyPressSound.getSound().play();
                    return selectedIndex; 
                }
            }
        }

        window.clear();
        window.draw(startModeSprites[selectedIndex]);
        window.display();
    }

    return -1; 
}


void GameMenuHandler::showRules()
{
    
    MySprite rulesSprite("../Textures/Rules.jpeg");

    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) 
            {
                return; // Exit the rules screen and return to the main menu
            }
            if (event.type == Event::Closed) 
            {
                exit(0); // Exit the game
            }
        }

        
        window.clear();
        rulesSprite.Draw(window); 
        window.display();
    }
}


int GameMenuHandler::handleMenuLoop() 
{
    while (true) 
    {
        bool isGameOn = false;
        // Main menu loop
        int selectedOption = mainMenu();
        keyPressSound.play();
        if (selectedOption == -1) 
        {
            return selectedOption; // Exit game
        }

        
        if (selectedOption == 0 || selectedOption == 1) {
            while (true) {
                // Start menu loop
                int startOption = startMenu();
                keyPressSound.play();

                if (startOption == -1) 
                {
                    break; // Exit start menu
                }
                // Start game
                else if (startOption == 0) 
                {
                    // Mode selection: Easy, Medium, Hard
                    int modeOption = modeMenu(window);
                    keyPressSound.play();

                    if (modeOption == -1) 
                    {
                        continue; // If ESC is pressed, stay in the mode menu
                    }
                    else if (modeOption == 0) 
                    {
                        EasyMode(snakeSpeed);
                        isGameOn = true;
                        break; // Exit mode menu to start game
                    }
                    else if (modeOption == 1) 
                    {
                        isGameOn = true;
                        MediumMode(snakeSpeed);
                        break; // Exit mode menu to start game
                    }
                    else if (modeOption == 2) 
                    {
                        isGameOn = true;
                        HardMode(snakeSpeed);
                        break; // Exit mode menu to start game
                    }
                }
                else if (startOption == 1) 
                {
                    // Handle the classic/infinite mode menu
                    int modeOption = startModeMenu();
                    keyPressSound.play();

                    if (modeOption == -1) 
                    {
                        continue; // If ESC is pressed, stay in the mode menu
                    }
                    else if (modeOption == 0) 
                    {
                        classicMode = true;
                        infiniteMode = false;
                    }
                    else if (modeOption == 1) 
                    {
                        classicMode = false;
                        infiniteMode = true;
                    }
                }
                else if (startOption == 2) 
                {
                    // Show High Scores
                    window.clear();
                    highScores.displayHighScores(window, font, HighScoresSprite);
                    window.display();
                    keyPressSound.play();
                }
            }
        }

        if (isGameOn)
        {
			break;
		}

        
        if (selectedOption == 2) 
        {
            // Show rules
            showRules();
            keyPressSound.play();
        }

        // Exit game 
        else if (selectedOption == 3) 
        {
            return selectedOption;
        }
    }
}
