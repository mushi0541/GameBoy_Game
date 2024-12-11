#pragma once
#include <iostream>
#include <string>
using namespace std;

class Game
{
public:
    std::string name;           // Game name
    static int score;           // Static score shared across all instances

public:
    Game() : name("Game") {}
    Game(std::string gameName) : name(gameName) {}

    virtual void startGame() = 0;
    virtual void render() = 0;

    virtual ~Game() {}
};



