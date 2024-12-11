#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>
#include "HangManMenuHandler.h"
#include "WordManager.h"
#include "SoundBufferHandler.h"
#include "KeyboardHandler.h"
#include "Game.h"
#include <fstream>
#include "Player.h"

using namespace std;
using namespace sf;

class HangMan : public Game
{
	RenderWindow& window;
	Font font;
	Font font2;
	Texture aliveHeartTexture, deadHeartTexture;
	Sprite heartSprites[6];
	Texture hangmanTextures[6];
	Sprite hangmanSprites[6];
	RectangleShape hintButton;
	Text hintButtonText;
	RectangleShape CategoryBox;
	Text CategoryText;
	string word;
	Text wordDisplay[20];
	string currentGuess;
	string category;
	int lives;
	bool isGameOver;
	bool isGameWon;
	bool isGamePaused;
	bool isHintUsed;
	HangManMenuHandler Menu;
	WordManager wordManager;
	Player &player;
	SoundBufferHandler bgMusic;
public:
	HangMan(RenderWindow& gameWindow, Player &player);
	void render() override;
	void handleGameLoop();
	void ContinueGame();
	void PlayAgain();
	void startGame() override;
	void saveGame(const string& filename);
	void loadGame(const string& filename);
};

