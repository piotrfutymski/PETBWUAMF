#pragma once

#include "Window/Window.h"
#include "Inupt/Input.h"
#include "Utility/Logger.h"
#include "Widgets/Widgets.h"
#include "GameObjects/GameObjects.h"
#include "Assets/AssetMeneger.h"
#include "EngineState.h"

#include "nlohmann/json.hpp"

namespace Didax
{
	class Board;

class Engine
{

public:

	using GameObjectsholder_t = std::vector< std::unique_ptr<GameObject>>;
	using UnitsHolder_t = std::vector<Unit *>;
	using OrdersHolder_t = std::vector<Order *>;

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

	void nextPhase();
	EngineState::TurnPhase getPhase()const;

	void endGame();

	void addUnit(const std::string & name, int pos);

	// Engine cycle

	void turnStart();
	void orderChoosed();
	void unitChoosed();
	void nextSpotChoosed();
	void setOrderToUnit();
	void turnEnd();

	//Asset interface

	template <typename T>
	T * getAsset(const std::string & name);

private:

	//assets

	AssetMeneger _assetMeneger;

	// game objects

	GameObjectsholder_t _gameObjects;

	Board * _bord = nullptr;

	UnitsHolder_t _playerUnits[2];

	OrdersHolder_t _playerOrders[2];

	// GUI root

	Canvas _root;

	// state

	EngineState _state;

	// events

	EventsHolder_t _events;

private:

	void initEvents();

	void createBoard();
	void changePhase(const EngineState::TurnPhase & p);

};

template<typename T>
inline T * Engine::getAsset(const std::string & name)
{
	return _assetMeneger.getAsset<T>(name);
}

}