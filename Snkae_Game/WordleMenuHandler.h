#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SoundBufferHandler.h"
using namespace sf;
using namespace std;
class WordleMenuHandler
{
protected:
    RenderWindow& window;
    SoundBufferHandler keyPressSound;
    Font font;
    Texture mainMenuTextures[3];
    Sprite mainMenuSprites[3];
    Texture pauseMenuTextures[3];
    Sprite pauseMenuSprites[3];
    Texture GameOverMenuTextures[2];
    Sprite GameOverMenuSprites[2];
    Texture GameWonMenuTexture[2];
    Sprite GameWonMenuSprite[2];


public:
    WordleMenuHandler(RenderWindow& gameWindow);
    void loadResources();
    int mainMenu();
    int pauseMenu();
    int GameOverMenu(string word);
    int GameWonMenu();
    void showRules();
    int handleMenuLoop();
};

