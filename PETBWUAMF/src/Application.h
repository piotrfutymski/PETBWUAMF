#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <functional>
#include <thread>
#include <mutex>

#include "Game/Game.h"
#include "Game/PrototypeInitializer.h"
#include "Assets/AssetMeneger.h"
#include "Utility/Reporter.h"
#include "CUI/ConsoleUI.h"
#include "GUI/Engine.h"

class Application
{
public:
	Application();

	void init(std::string settingFilePath);

	int run();

	void playGame()
	{
		while (!_game.isGameEnded())
		{
			_game.playTurn(this->getMoveFromConsole());
		}
	}

	Move getMoveFromConsole();

private:

	Game _game;

	Reporter _reporter;

	ConsoleUI _consoleUI;


	nlohmann::json _settings;

	Didax::Engine _engine;
};

