#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <functional>

#include "Game/Game.h"



class Application
{
public:
	Application();

	void init(std::string settingFilePath);

	int run();

	void input();

	void update();

	void render();


private:

	Didax::Window _window;

	nlohmann::json _settings;

	Game _game;

	Didax::Logger _logger;

	sf::Clock _clock;

};
