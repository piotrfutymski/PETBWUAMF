#pragma once

#include "../Game/Game.h"
#include"GUIElements/GuiElements.h"
#include "Window/Window.h"
#include "Inupt/Input.h"
#include "nlohmann/json.hpp"
#include <mutex>

namespace Didax
{

class Engine
{

public:

	using GUIElemtntHolder_t = std::vector<std::unique_ptr<GUIElement>>;

	//constructor

	Engine();

	~Engine();

	//Application interface

	bool init(const nlohmann::json & settings, Game * g);

	void run();

	Move getMove();

	void setMoveRes(const MoveRes & moveRes);



private:

	GUIElemtntHolder_t _elements;
	BoardGUI * _board;

	Canvas _updater;

	Game * _game;

	sf::Clock _clock;

	Window _window;

private:

	void update();
	void render();
	void input();

};

}