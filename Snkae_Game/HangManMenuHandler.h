#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SoundBufferHandler.h"
using namespace sf;
using namespace std;
class HangManMenuHandler
{

protected:
    RenderWindow& window;
    SoundBufferHandler keyPressSound;
    Font font;
    Texture mainMenuTextures[3];
    Sprite mainMenuSprites[3];
    Texture pauseMenuTextures[2];
    Sprite pauseMenuSprites[2];
    Texture GameOverMenuTextures[2];
    Sprite GameOverMenuSprites[2];
    Texture GameWonMenuTexture[2];
    Sprite GameWonMenuSprite[2];


public:
    HangManMenuHandler(RenderWindow& gameWindow);
    void loadResources();
    int mainMenu();
    int pauseMenu();
    int GameOverMenu(string word);
    int GameWonMenu();
    void showRules();
    int handleMenuLoop();
};

