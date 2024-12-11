#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>
#include "WordleMenuHandler.h"
#include "WordleWordManager.h"
#include "SoundBufferHandler.h"
#include "WordleKeyboardHandler.h"	
#include "GridSystem.h"
#include "Game.h"
#include <fstream>
#include "Player.h"
using namespace std;
using namespace sf;

class WordleGame : public Game
{
	RenderWindow& window;
	Font font;
	Texture SetBackGround;
	Sprite BackGround;
	string targetWord;
	int currentRow;
	string currentGuess;
	string feedback;
	int lives;
	bool isGameOver;
	bool isGameWon;
	bool isGamePaused;
	WordleMenuHandler Menu;
	WordleWordManager wordManager;
	GridSystem gridSystem;
	SoundBufferHandler keyPressSound;
	Player &player;
	SoundBufferHandler bgMusic;

public:
	WordleGame(RenderWindow& gameWindow,Player& player);
	void render() override;
	void handleGameLoop();
	void ContinueGame();
	void PlayAgain();
	void startGame() override;
	void saveGame(const string& filename);
	void loadGame(const string& filename);
};

