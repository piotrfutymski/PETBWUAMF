#pragma once

#include "Window/Window.h"
#include "Inupt/Input.h"
#include "Utility/Logger.h"
#include "Widgets/Widgets.h"
#include "GameObjects/GameObjects.h"
#include "Assets/AssetMeneger.h"
#include "EngineState.h"
#include "Player.h"
#include "GUI/MainGUI.h"

#include "nlohmann/json.hpp"

namespace Didax
{
	class Board;

class Engine
{

public:

	using GameObjectsholder_t = std::vector< std::unique_ptr<GameObject>>;

	enum class EngineEvents {
		OnStart
	};

	using EventsHolder_t = std::map<EngineEvents, std::function<void(Engine *, float)>>;

	//constructor

	Engine();

	~Engine();

	//Application interface

	bool init(const std::function<bool(Engine * e)> _initLogicFunc, const nlohmann::json & settings);

	void startGame();

	void update(float deltaTime);

	void render(sf::RenderTarget & target, sf::RenderStates states = sf::RenderStates::Default);

	void input(const sf::Event & e);

	bool end();

	//Game interface

	void setEvent(const EngineEvents & t, const std::function<void(Engine*, float)> & func);

	void addUnit(const std::string & name, int player, int pos);
	void addOrder(const std::string & name, int player);

	void endGame();


	// Engine cycle

	void startNextTurn();
	void waitForOrderChoose();

	/*void orderChoosed();
	void unitChoosed();
	void nextSpotChoosed();
	void setOrderToUnit();
	void turnEnd();*/

	//Asset interface

	template <typename T>
	T * getAsset(const std::string & name);

private:

	//assets

	AssetMeneger _assetMeneger;

	// game objects

	GameObjectsholder_t _gameObjects;

	Board * _bord = nullptr;

	// GUI root

	Canvas _root;

	// Main GUI

	MainGUI _mainGui;

	// state

	EngineState _state;

	//players

	Player _players[2];

	// events

	EventsHolder_t _events;

private:

	//openning Engine

	void initEvents();
	void createBoard();

	//trun beginning

	int getPlayerOnTurnStart();
	void setUnitsAndOrdersOnTurnStart(int p);

	//

};

template<typename T>
inline T * Engine::getAsset(const std::string & name)
{
	return _assetMeneger.getAsset<T>(name);
}

}