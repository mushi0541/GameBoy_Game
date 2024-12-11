#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "GameConstants.h"
#include "Snake.h"
#include "Food.h"
#include "DifficultyHandler.h"
#include "GameMenuHandler.h"
#include "HighScores.h"
#include "SoundBufferHandler.h"
#include "Game.h"
#include "Player.h"

using namespace sf;
using namespace std;

class SnakeGame : public GameConstants, public Game
{
private:
    RenderWindow& window;
    int regularFoodEaten;
    bool growing, gameOver;
    Texture bonusCountdownTextures[5];
    Sprite bonusCountdownSprites[5];
    Texture backgroundTexture;
    Sprite backgroundSprite;
    Font font;
    SoundBuffer Buffer;
    Sound eatSound, keyPressedSound;
    Clock clock, bonusFoodTimer;
    Snake snake;
    Food food;
    DifficultyHandler difficultyHandler;
    GameMenuHandler gameMenuHandler;
    HighScores highScores;
    SoundBufferHandler soundBufferHandler;
    SoundBufferHandler bgMusic;
    Player &player;

public:
    SnakeGame(RenderWindow& window, Player &player);

    void render() override;
    void initialize();
    void drawScore();
    void infinityCollision();
    void handleInput(Keyboard::Key key);
    void draw();
    int innerLoop();
    void startGame() override;
    void saveGame(const string& filename);
    void loadGame(const string& filename);
};
