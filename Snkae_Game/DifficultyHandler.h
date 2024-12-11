#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "MySprite.h"
#include "SoundBufferHandler.h"

using namespace sf;
using namespace std;

class DifficultyHandler
{
public:
    DifficultyHandler();

    void EasyMode(float& snakeSpeed);
    void MediumMode(float& snakeSpeed);
    void HardMode(float& snakeSpeed);
    int modeMenu(RenderWindow& window);
    void setDifficulty(RenderWindow& window, float& snakeSpeed);
protected:
    Texture imgT[3];
    Sprite img[3];
    SoundBufferHandler keyPressed;
    int selectedIndex;
};
