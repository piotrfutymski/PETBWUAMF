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

	static void orderOnHoverIn(OrderRepresentation * o, Engine * e);
	static void orderOnHoverOut(OrderRepresentation * o, Engine * e);
	static void orderOnRelease(OrderRepresentation * o, Engine * e);

	static void unitOnHoverIn(UnitRepresentation * o, Engine * e);
	static void unitOnHoverOut(UnitRepresentation * o, Engine * e);
	static void unitOnRelease(UnitRepresentation * o, Engine * e);

	static void positionOnHoverIn(BoardGUI::PositionWidget * o, Engine * e);
	static void positionOnHoverOut(BoardGUI::PositionWidget * o, Engine * e);
	static void positionOnRelease(BoardGUI::PositionWidget * o, Engine * e);

};

}