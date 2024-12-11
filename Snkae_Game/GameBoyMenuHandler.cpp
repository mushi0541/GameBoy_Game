#include "GameBoyMenuHandler.h"


GameBoyMenuHandler::GameBoyMenuHandler(RenderWindow& gameWindow) : window(gameWindow)
{
    keyPressSound.loadFromFile("../Sound/Key.wav");
    font.loadFromFile("../Font2/arial.ttf");
    loadResources();
}

void GameBoyMenuHandler::loadResources()
{
    if (!mainMenuTextures[0].loadFromFile("../GameBoy/mainMenu1.jpg") ||
        !mainMenuTextures[1].loadFromFile("../GameBoy/mainMenu2.jpg") ||
        !mainMenuTextures[2].loadFromFile("../GameBoy/mainMenu3.jpg") ||
        !mainMenuTextures[3].loadFromFile("../GameBoy/mainMenu4.jpg") ||
        !mainMenuTextures[4].loadFromFile("../GameBoy/mainMenu5.jpg") ||
        !leaderBoardTextures.loadFromFile("../GameBoy/leaderBoard.jpg"))
    {
       
    }

    for (int i = 0; i < 5; i++)
    {
        mainMenuSprites[i].setTexture(mainMenuTextures[i]);
    }

    leaderBoardSprite.setTexture(leaderBoardTextures);
}

int GameBoyMenuHandler::mainMenu()
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
                    selectedIndex = (selectedIndex - 1 + 5) % 5;

                }
                else if (event.key.code == Keyboard::Down)
                {
                    keyPressSound.getSound().play();
                    selectedIndex = (selectedIndex + 1) % 5;
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





int GameBoyMenuHandler::handleMenuLoop()
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

       
        if (selectedOption >=0 && selectedOption <= 2)
        {
            isGameOn = true;
        }

        if (isGameOn)
        {
            return selectedOption;
        }

        
        if (selectedOption == 3)
        {
            window.clear();
            displayLeaderboard(window, leaderBoardSprite);
            window.display();
            keyPressSound.play();
        }

        else if (selectedOption == 4)
        {
            window.close(); 
            return 0;
        }
    }
}


