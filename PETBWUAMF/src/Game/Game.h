#pragma once
#include <memory>
#include <vector>
#include <algorithm> 
#include "../DidaxEngine/Engine.h"


using namespace Didax;

typedef unsigned long long clock_ticks;


class Game
{

public:

	Game();

	Game(const Game&) = delete;

	Game & operator = (const Game &) = delete;

	Game(Game&&) = delete;

	Game & operator = (Game &&) = delete;

	~Game() = default;

	///

	void init(const nlohmann::json & settingFile);

	void saveGame(const std::string & path);

	///

	void update(unsigned int deltaTime);

	void render(sf::RenderTarget & target, sf::RenderStates states = sf::RenderStates::Default);

	void input(const sf::Event & e);

private:

	clock_ticks _ticks{ 0u };
	Canvas * canv;
	Canvas * canv2;
};
