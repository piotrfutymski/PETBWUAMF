#pragma once

#include "../Game/Game.h"
#include "Window/Window.h"
#include "Inupt/Input.h"
#include "nlohmann/json.hpp"
#include <mutex>

namespace Didax
{

class Engine
{

public:

	//constructor

	Engine();

	~Engine();

	//Application interface

	bool init(const nlohmann::json & settings, Game * g, std::mutex * gM);

	void run();

	Move getMove();

	void setMoveRes(const MoveRes & moveRes);



private:

	Game * _game;

	sf::Clock _clock;

	Window _window;

	std::mutex* gameMutex;

private:

	void update();
	void render();
	void input();

};

}