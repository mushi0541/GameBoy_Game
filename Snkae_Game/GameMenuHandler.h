#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "DifficultyHandler.h"
#include "HighScores.h"
#include "SoundBufferHandler.h"
#include "MySprite.h"
#include "GameConstants.h"
using namespace sf;

class GameMenuHandler :public GameConstants, public DifficultyHandler
{
public:

    HighScores highScores;
    RenderWindow& window;
    SoundBufferHandler keyPressSound;
    Font font;
    Texture mainMenuTextures[4];
    Texture startMenuTextures[3];
    Texture startModeTextures[2];
    Texture HighScoresTexture;
    Sprite mainMenuSprites[4];
    Sprite startMenuSprites[3];
    Sprite startModeSprites[2];
    Sprite HighScoresSprite;
    Texture pauseMenuTextures[3];
    Sprite pauseMenuSprites[3];
    

    float snakeSpeed;
    bool classicMode;
    bool infiniteMode;

public:
    GameMenuHandler(RenderWindow& gameWindow);
    void loadResources();
    int mainMenu();
    int startMenu();
    int startModeMenu();
    int pauseMenu();
    void showRules();
    int handleMenuLoop();
};
