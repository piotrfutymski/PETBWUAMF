#pragma once

#include "../Game/Game.h"
#include "GUIElements/GuiElements.h"
#include "Window/Window.h"
#include "Inupt/Input.h"
#include "nlohmann/json.hpp"
#include <mutex>

namespace Didax
{

class Engine
{

public:

	enum class EngineState {
		ChoosingOrder, ChoosingTarget, PlyaingGame
	};

	using GUIElemtntHolder_t = std::vector<std::unique_ptr<GUIElement>>;

	//constructor

	Engine();

	~Engine();

	//Application interface

	bool init(const nlohmann::json & settings, Game * g);

	void run();

	// Widget Interface

	InfoGUI* getInfoGUI();


private:

	GUIElemtntHolder_t _elements;
	BoardGUI * _board;
	InfoGUI * _info;
	std::vector<std::unique_ptr<UnitRepresentation>> _units;
	std::vector<OrderRepresentation *> _orders;

	size_t _choosedOrder{ (size_t)-1 };
	Move _move;

	EngineState _state{ EngineState::ChoosingOrder };

	Canvas _updater;

	Game * _game;

	sf::Clock _clock;

	Window _window;

private:

	void update();
	void render();
	void input();

	//
	void initGame();
	void startTurn();
	void reloadOrders();
	void reloadUnits();

	//
	void orderChoosed(size_t orderID);
	void prepareOrdersOnChoosed();
	void prepareBoardOnChoosed();
	//
	void targetChoosed(const sf::Vector2i & pos);



	//
	void playMove(const Move & m);

	void escEvent();

private:
	OrderRepresentation * findRepresentationWithOrder(size_t o);
	UnitRepresentation * findRepresentationWithUnit(size_t u);

public:

	//Events:

	void orderOnHoverIn(OrderRepresentation* o);
	void orderOnHoverOut(OrderRepresentation* o);
	void orderOnRelease(OrderRepresentation* o);

	void unitOnHoverIn(UnitRepresentation* u);
	void unitOnHoverOut(UnitRepresentation* u);
	void unitOnRelease(UnitRepresentation* u);

	void positionOnRelease(BoardGUI::PositionWidget&& o);

};

}