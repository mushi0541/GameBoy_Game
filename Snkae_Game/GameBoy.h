#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "GameBoyMenuHandler.h"
#include "SoundBufferHandler.h"
#include "Game.h"
#include "HangMan.h"
#include "SnakeGame.h"
#include "WordleGame.h"
#include "Player.h"
#include "LeaderBoard.h"
using namespace std;
using namespace sf;

class GameBoy
{
private:
	GameBoyMenuHandler Menu;
	RenderWindow& window;
	Font font;
	SoundBufferHandler keyPressSound;
	SoundBufferHandler bgMusic;
	Texture NameScreen;
	Sprite NameScreenSprite;
	Game * currentGame;
	Player player;
	Leader leaderboard;
	
public:
	GameBoy(RenderWindow& window);
	void Start();
	void SwitchGame(string gameName);
	string inputName();
	~GameBoy();
};

