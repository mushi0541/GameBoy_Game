#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "SoundBufferHandler.h"
#include "LeaderBoard.h"

using namespace std;
using namespace sf;
class GameBoyMenuHandler : public Leader
{
protected:
    RenderWindow& window;
    SoundBufferHandler keyPressSound;
    Font font;
    Texture mainMenuTextures[5];
    Sprite mainMenuSprites[5];
    Texture leaderBoardTextures;
    Sprite leaderBoardSprite;
public:
    GameBoyMenuHandler(RenderWindow& gameWindow);
    void loadResources();
    int mainMenu();
    int handleMenuLoop();
};

