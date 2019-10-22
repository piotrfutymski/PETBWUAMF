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

	bool isWaitingForEnd();

	//Game interface

	void setEvent(const EngineEvents & t, const std::function<void(Engine*, float)> & func);

	void addUnit(const std::string & name, int player, int pos);
	void addOrder(const std::string & name, int player);

	void endGame();


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

	std::unique_ptr<MainGUI> _mainGui;

	// state

	EngineState _state;

	//players

	Player _players[2];

	// events

	EventsHolder_t _events;

	// esc func

	std::function<void()> _onEsc = nullptr;

private:

	// Engine cycle

	void startNextTurn();
	void waitForOrderChoose();
	void orderChoosed();
	void orderUnchoosed();

	void unitChoosed();
	void unitUnchoosed();


	void nextSpotChoosed();

	/*
	void setOrderToUnit();
	void turnEnd();*/

	//openning Engine

	void initObjects();
	void initEvents();
	void createBoard();
	void openMainGUI();

	//trun beginning

	int getPlayerOnTurnStart();
	void setUnitsAndOrdersOnTurnStart(int p);


	//esc functions

	void resetOrderChoose();
	void resetUnitChoose();

	// posted functions

	void showUnitDescription(Unit * u);
	void hideUnitDescription(Unit * u);
	void showOrderDescription(Order * o);
	void hideOrderDescription(Order * o);
	void orderChoosed(Order * o);

};

template<typename T>
inline T * Engine::getAsset(const std::string & name)
{
	return _assetMeneger.getAsset<T>(name);
}

}