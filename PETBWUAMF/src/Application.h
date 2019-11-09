#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <functional>

#include "Game/Game.h"
#include"Assets/AssetMeneger.h"


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

	//Didax::Window _window;
	//Didax::Engine _engine;
	//float sec = 0;
	//int frames = 0;

	Game _game;

	nlohmann::json _settings;

	sf::Clock _clock;

};
