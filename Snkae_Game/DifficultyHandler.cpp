#include "DifficultyHandler.h"
//for snake
DifficultyHandler::DifficultyHandler() : selectedIndex(0) 
{
    keyPressed.loadFromFile("../Sound/Key.wav");
    imgT[0].loadFromFile("../Textures/Easy.jpeg");
    imgT[1].loadFromFile("../Textures/Medium.jpeg");
    imgT[2].loadFromFile("../Textures/Hard.jpeg");
    img[0].setTexture(imgT[0]);
    img[1].setTexture(imgT[1]);
    img[2].setTexture(imgT[2]);
    img[0].setPosition(0, 0);
    img[1].setPosition(0, 0);
    img[2].setPosition(0, 0);
}

void DifficultyHandler::EasyMode(float& snakeSpeed) 
{
    snakeSpeed = 0.1f;
}

void DifficultyHandler::MediumMode(float& snakeSpeed) 
{
    snakeSpeed = 0.06f;
}

void DifficultyHandler::HardMode(float& snakeSpeed) 
{
    snakeSpeed = 0.035f;
}

int DifficultyHandler::modeMenu(RenderWindow& window) 
{
    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) 
            {
                return -1;
            }
            if (event.type == Event::Closed) 
            {
                exit(0);
            }
            if (event.type == Event::KeyPressed) 
            {
                if (event.key.code == Keyboard::Left) 
                {
                    keyPressed.play();
                    selectedIndex = (selectedIndex - 1 + 3) % 3;
                }
                else if (event.key.code == Keyboard::Right) 
                {
                    keyPressed.play();
                    selectedIndex = (selectedIndex + 1) % 3;
                }
                else if (event.key.code == Keyboard::Enter) 
                {
                    keyPressed.play();
                    return selectedIndex;
                }
            }
        }

        window.clear();
        window.draw(img[selectedIndex]);
        window.display();
    }
    return -1;
}

void DifficultyHandler::setDifficulty(RenderWindow& window, float& snakeSpeed) 
{
    int modeOption = modeMenu(window);
    if (modeOption == 0)
    {
        EasyMode(snakeSpeed);
        return;
    }
    else if (modeOption == 1)
    {
        MediumMode(snakeSpeed);
        return;
    }
    else if (modeOption == 2)
    {
        HardMode(snakeSpeed);
        return;
    }
    else
        return;
}
