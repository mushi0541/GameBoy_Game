#include "GameBoy.h"

GameBoy::GameBoy(RenderWindow& window):window(window), Menu(window)
{
	font.loadFromFile("../Font2/arial.ttf");
	keyPressSound.loadFromFile("../Sound/Key.wav");
	bgMusic.loadFromFile("../Sound/bgMusic1.wav");
	currentGame = nullptr;
	NameScreen.loadFromFile("../GameBoy/NameScreen.jpg");
	NameScreenSprite.setTexture(NameScreen);
}


string GameBoy:: inputName() 
{
	NameScreenSprite.setPosition(0, 0);  
	Font font2;
	font2.loadFromFile("../Font2/Category.ttf");
	Text nameText;
	nameText.setFont(font2);
	nameText.setCharacterSize(50);
	nameText.setFillColor(Color::Black);
	nameText.setPosition(500, 655); 

	string playerName = "";
	bool typing = true;

	while (window.isOpen() && typing) 
	{
		Event event;

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::KeyPressed) {
				if (event.key.code >= Keyboard::A && event.key.code <= Keyboard::Z) 
				{
					keyPressSound.play();
					char letter = 'A' + (event.key.code - Keyboard::A);
					
					playerName += letter;
				}

				if (event.key.code == Keyboard::BackSpace && !playerName.empty()) {
					playerName.pop_back();
				}

				if (event.key.code == Keyboard::Enter) 
				{
					if(playerName.length()>1)
					typing = false; 
				}
			}
		}

		window.clear(Color::White);
		window.draw(NameScreenSprite);  
		nameText.setString(playerName + "_");  
		window.draw(nameText);  
		window.display();  
	}

	return playerName;  
}

void GameBoy::Start()
{
	player.name = inputName();
	keyPressSound.play();
	keyPressSound.setVolume(100);
	Event event;
	while(window.isOpen())
	{
		bgMusic.play();
		bgMusic.setLoop(true);
		bgMusic.setVolume(30);
		Game::score = 0;
		player.loadHighScores();

		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
				window.close();
		}
		window.clear();
		int selected = Menu.handleMenuLoop();
		
		if (selected == 0)
		{
			SwitchGame("Snake");
		}
		if(selected == 1)
		{
			SwitchGame("HangMan");
		}
		if(selected == 2)
		{
			SwitchGame("Wordle");
		}

		if(currentGame != nullptr)
		{
			bgMusic.stop();
			currentGame->startGame();
			cout<<Game::score;
		    player.updateHighScore(currentGame->score, currentGame->name);
			player.displayHighScores();
			leaderboard.updateLeaderboard(player);
		    bgMusic.play();
		}

	}
}


void GameBoy::SwitchGame(string gameName)
{
	if(currentGame != nullptr)
	{
		delete currentGame;
	}
	if(gameName == "Snake")
	{
		currentGame = new SnakeGame(window,player);
		currentGame->name = "Snake";
	}
	if(gameName == "HangMan")
	{
		currentGame = new HangMan(window,player);
		currentGame->name = "HangMan";
	}
	if(gameName == "Wordle")
	{
		currentGame = new WordleGame(window,player);
		currentGame->name = "Wordle";
	}
}

GameBoy::~GameBoy()
{
	if(currentGame != nullptr)
	{
		delete currentGame;
	}
}


int Game::score = 0;
int main()
{
	RenderWindow window(VideoMode(960, 960), "GameBoy");
	GameBoy gameBoy(window);
	gameBoy.Start();
	return 0;
}
